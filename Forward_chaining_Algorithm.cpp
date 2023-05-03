#include<iostream>
#include<vector>
#include<unordered_set>
#include<fstream>
#include<string.h>

using namespace std;

vector<pair<string, char>> lawlist;
const int initnum = 500;
int numlaw;
bool flag[26], mark[initnum];
string goal;

vector<int> Loc(){
    vector<int> sat;
    for(int i = 0; i < numlaw; i++){
        if(mark[i]) continue;
        bool check = true;

        if(!mark[i])
            for(char ch : lawlist[i].first)
                if(flag[ch - 'a'] == false){
                    check = false;
                    break;
                }
        if(check == true){
            sat.push_back(i);
        }
    }
    return sat; 
}

void execute_forward_chaining(){
    vector<int> sat = Loc();
    while(!sat.empty()){
        int pos = sat.front();
        flag[lawlist[pos].second - 'a'] = true;
        mark[pos] = true;
        sat = Loc();
    }
    bool check = true;
    for(auto g : goal)
        if(flag[g - 'a'] == false)
            check = false;
    if(check)   cout<<"Thanh cong";
    else cout<<"Khong thanh cong";
}

main(){
    string file_name;   cin>>file_name;
    ifstream file(file_name);
    if(file.is_open())  cout<<"Open file successfully!\n";
    else{
         cout<<"404!";
         return 1;
    }
    string gt;
    char kl;
    memset(mark, false, sizeof(mark));
    memset(flag, false, sizeof(flag));
    file>>numlaw;
    for(int i = 0; i < numlaw; i++){
        file>>gt>>kl;
        lawlist.push_back(make_pair(gt,kl));
    }
    file>>gt;
    for(auto ch : gt)   flag[ch-'a'] = true;
    file>>goal; 
    execute_forward_chaining();
    file.close();
}
