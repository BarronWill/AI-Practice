#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int mx = 10000;
const int sz = 8;
int parent[sz];
int minvalue(int dist[], bool mark[]){
    int index, min = mx;
    for(int i = 0; i < sz; i++){
        if(mark[i] == false && dist[i] < min)
            min = dist[i], index = i;
    }
    return index;
}

// To trace the road from the goal back to the root
void trace(int x, int goal){
    vector<int> str;
    str.push_back(goal);
    while(goal != x){
        goal = parent[goal];
        str.push_back(goal);
    }
    reverse(str.begin(), str.end());
    for(int i : str){
        cout<<(char)(i + 'A')<<" ";
    }
    cout<<"\n";

}

// Calculate h in the A star algorithm - illustrative example
int to_goal(int temp){
    return temp;
}

void output(int dist[]){
    for(int i = 0; i < sz; i++)
        cout<<i<<"\t\t"<<dist[i]<<"\n";
}

void execute_AT(int graph[sz][sz], int root, int final_vertex){
    int dist[sz];
    bool mark[sz];
    memset(dist, mx, sizeof(dist));
    memset(mark, false, sizeof(mark));
    dist[root] = 0;
    for(int i = 0; i < sz - 1; i++){
        int minvrt = minvalue(dist, mark);
        mark[minvrt] = true;
        if(minvrt == final_vertex){
            trace(root, final_vertex);
        }
        for(int j = 0; j < sz; j++){
            if(graph[minvrt][j] && mark[j] == false && graph[minvrt][j] + dist[minvrt] < dist[j]){
                dist[j] = graph[minvrt][j] + dist[minvrt];
                parent[j] = minvrt;
            }
        }
    }
    output(dist);
}

void execute_AT_prqueue(int graph[sz][sz], int root, int final_vertex){ // USING  PRIORITY QUEUE
    int dist[sz];
    bool mark[sz];
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> str;
    memset(dist, mx, sizeof(dist));
    memset(mark, false, sizeof(mark));
    dist[root] = 0;
    str.push(make_pair(dist[root], root));
    while(!str.empty()){
        int min_vertex = str.top().second;
        str.pop();
        if(mark[min_vertex] == true)    continue;
        mark[min_vertex] = true;
        if(min_vertex == final_vertex){
            trace(root, final_vertex);
        }
        for(int i = 0; i < sz; i++){
            if(mark[i] == false && graph[min_vertex][i] && graph[min_vertex][i] + dist[min_vertex] < dist[i]){
                dist[i] = dist[min_vertex] + graph[min_vertex][i];
                str.push(make_pair(dist[i], i));
                parent[i] = min_vertex;
            }
        }
    }
    output(dist);
}

void execute_AKT(int graph[sz][sz], int root, int final_vertex){
    bool mark[sz];
    int f[sz];
    int g[sz];
    int h[sz] = {};
    memset(f, mx, sizeof(f));
    memset(g, mx, sizeof(g));
    memset(mark, false, sizeof(mark));
    g[root] = 0;
    f[root] = g[root] + h[root];
    for(int count = 0; count < sz - 1; count++){
        int min_value = minvalue(f,mark);
        mark[min_value] = true;
        if(min_value == final_vertex){
            trace(root, final_vertex);
        }
        for(int i = 0; i < sz; i++){
            if(mark[i] == false && graph[min_value][i] && g[i] > graph[min_value][i] + g[min_value]){
                g[i] = graph[min_value][i] + g[min_value];
                parent[i] = min_value;
                f[i] = g[i] + h[i];
            }
        }
    }
    output(g);
}
void execute_AKT_prqueue(int graph[sz][sz], int root, int final_vertex){
    int g[sz];
    int h[sz] = {};
    bool mark[sz];
    memset(g, mx, sizeof(g));
    memset(h, mx, sizeof(h));
    memset(mark, false, sizeof(mark));
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> str;
    g[root] = 0;
    str.push(make_pair(root, g[sz] + h[sz]));
    while(!str.empty()){
        int min_value = str.top().first;
        str.pop();
        if(mark[min_value]) continue; 
        mark[min_value] = true;
        if(min_value == final_vertex){
            trace(root, final_vertex);
        }
        for(int i = 0; i < sz; i++){
            if(mark[i] == false && graph[min_value][i] && g[i] > graph[min_value][i] + g[min_value]){
                g[i] = graph[min_value][i] + g[min_value];
                parent[i] = min_value;
                str.push(make_pair(i, g[i] + h[i]));
            }
        }
    }
    output(g);
}

void execute_A_star(int graph[sz][sz], int root, int final_vertex){
    bool mark[sz];
    int f[sz];
    int g[sz];
    int h[sz] = {};
    memset(f, mx, sizeof(f));
    memset(g, mx, sizeof(g));
    memset(mark, false, sizeof(mark));
    g[root] = 0;
    f[root] = g[root] + h[root];
    for(int count = 0; count < sz - 1; count++){
        int min_value = minvalue(f,mark);
        mark[min_value] = true;
        if(min_value == final_vertex){
            trace(root, final_vertex);
        }
        for(int i = 0; i < sz; i++){
            if(mark[i] == false && graph[min_value][i] && g[i] > graph[min_value][i] + g[min_value]){
                g[i] = graph[min_value][i] + g[min_value];
                parent[i] = min_value;
                h[i] = to_goal(i);
                f[i] = g[i] + h[i];
            }
        }
    }
    output(g);
}

void execute_A_Star_prqueue(int graph[sz][sz], int root, int final_vertex){
    int g[sz];
    int h[sz] = {};
    bool mark[sz];
    memset(g, mx, sizeof(g));
    memset(h, mx, sizeof(h));
    memset(mark, false, sizeof(mark));
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> str;
    g[root] = 0;
    str.push(make_pair(root, g[sz] + h[sz]));
    while(!str.empty()){
        int min_value = str.top().first;
        str.pop();
        if(mark[min_value]) continue; 
        mark[min_value] = true;
        if(min_value == final_vertex){
            trace(root, final_vertex);
        }
        for(int i = 0; i < sz; i++){
            if(mark[i] == false && graph[min_value][i] && g[i] > graph[min_value][i] + g[min_value]){
                g[i] = graph[min_value][i] + g[min_value];
                parent[i] = min_value;
                h[i] = to_goal(i);
                str.push(make_pair(i, g[i] + h[i]));
            }
        }
    }
    output(g);
}

int main(){
    string name_file;   cin>>name_file;
    fstream file(name_file);
    if (file.is_open())
        cout << "Mo file thanh cong\n";
    else{
        cout << "Mo file that bai\n";
        return 1;
    }
    cout<<"\nTHE DISTANCE LIST\n";
    int graph[sz][sz];
    for(int i = 0; i < sz; i++)
        for(int j = 0; j < sz; j++)
            file >> graph[i][j];
    execute_A_Star_prqueue(graph, 0, 6);
}