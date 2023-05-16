#include<bits/stdc++.h>

using namespace std;
vector<vector<double>> multiple_matrix(vector<vector<double>> a, vector<double> b){
  vector<vector<double>> ans(a.size(), vector<double>(0));
  int num_row = a.size();
  int num_column = a[0].size();
  for(int row = 0; row < num_row; row++){
    double temp = 0;
    for(int col = 0; col < num_column; col++){
        temp+= a[row][col]*b[col];
    }
    ans[row].push_back(temp);
  }
  return ans;
}

vector<vector<double>> plus_matrix(vector<vector<double>> a, vector<vector<double>> b){
    vector<vector<double>> ans(a.size(), vector<double>(b.size()));
    for(int i = 0; i < a.size(); i++)
        for(int j = 0; j < b.size(); j++){
            ans[i][j] = a[i][j] + b[i][j];
        }
    return ans;
}

vector<vector<double>> multiple_matrix2(vector<vector<double>> a, vector<double> b){
  vector<vector<double>> ans(a.size(), vector<double>(0));
    for(int i = 0; i < a.size(); i++){
        int temp = a[i][0];
        for(int j = 0; j < b.size(); j++){
            ans[i].push_back(temp*b[j]);
        }
    }
    return ans;
}

vector<vector<double>> predict(vector<vector<double>> w, vector<double> bias, vector<double> train_x){
  vector<vector<double>> activation;
  activation = multiple_matrix(w,train_x);
  for(int i = 0; i < activation.size(); i++)
    activation[i][0] = activation[i][0] + bias[i];
    for(int i = 0; i < activation.size(); i++)
      if(activation[i][0] < 0) activation[i][0] = 0;
      else activation[i][0] = 1;
    return activation;
}


void preceptron(vector<vector<double>>& w, vector<double>& bias, const vector<double> train_x, const vector<double> train_y){
  vector<vector<double>> prepy = predict(w,bias,train_x);
  vector<vector<double>> temp(train_y.size(), vector<double>(0));
  for(int i = 0; i < train_y.size(); i++)
    temp[i].push_back(train_y[i] - prepy[i][0]);
  w = plus_matrix(w,multiple_matrix2(temp,train_x));//viet lai
  for(int i = 0; i < bias.size(); i++)
    bias[i] = bias[i] + temp[i][0];
}

int main(){
  vector<vector<double>> train_x {{1,1},{2,2},{8,1},{9,3},{2,7},{3,8},{8,8},{9,9}};
  vector<vector<double>> train_y {{0,0},{0,0},{0,1},{0,1},{1,0},{1,0},{1,1},{1,1}};
  vector<double> bias {0,0};
  vector<vector<double>> w {{0,0},{0,0}};
  int train_loop = 100;
  for(int train = 0; train < train_loop; train++)
    for(int i = 0; i < train_x.size(); i++){
      preceptron(w,bias,train_x[i],train_y[i]);
    }
  cout<<"Bias: "<<bias[0]<<" "<<bias[1]<<endl;
  cout<<"Weight: "<<w[0][0]<<" "<<w[0][1]<<"// "<<w[1][0]<<" "<<w[1][1]<<endl;
  vector<vector<double>> pre = predict(w,bias,{9,2});
  cout<<"Prediction: "<<pre[0][0]<<pre[1][0];
}
