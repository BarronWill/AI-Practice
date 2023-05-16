#include<bits/stdc++.h>

using namespace std;

int predict(vector<double> w, vector<double> x, double bias){
    double activation = 0;
    for(int i = 0; i < w.size(); i++){
        activation+= w[i]*x[i];
    }
    activation+= bias;
    return activation >= 0 ? 1 : -1;
}

void perceptron(vector<double>& w, double& bias, const vector<double> x, const double y){
    int prepy = predict(w,x,bias);
    for(int i = 0; i < w.size(); i++){
        w[i]+= (y - prepy)*x[i];
    }
    bias+= y - prepy;
}

int main(){
    vector<vector<double>> trainx { {1, 1}, {2, 2}, {8, 1}, {9, 1}, {2, 7}, {3, 8}, {9, 9} };
    vector<double> trainy { -1, -1, 1, 1, -1, -1, 1};
    vector<double> w {0.0, 0.0};
    double bias = 0.0;
    int train_loop = 100;
    for(int train = 0; train < train_loop; train++)
        for(int i = 0; i < trainx.size(); i++){
            perceptron(w,bias,trainx[i],trainy[i]);
        }
    cout<<"Weight: "<<w[0]<<" "<<w[1]<<endl;
    cout<<"Bias: "<<bias<<endl;
    cout<<"Prediction: "<<predict(w,{9,2},bias);
}