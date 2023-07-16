/* #include<bits/stdc++.h>

using namespace std;

const int V = 9;
int mx = 10000;

int minvalue(int dist[], bool mark[]){
    int min = mx, min_index;
    for(int i=0;i<V;i++)
        if(mark[i]==false&&dist[i]<=min)
            min = dist[i], min_index=i;
    return min_index;
}

void dijkstra(int graph[V][V], int pr_vertex){
    int dist[V];    // the distance from the source
    bool mark[V];
    memset(dist,mx,sizeof(dist)); // set the value mx to all the elements in the dist array
    memset(mark,false,sizeof(mark)); // the all the elements of mark[] as false
    dist[pr_vertex]=0;
    for(int i=0;i<V;i++){
        int min = minvalue(dist,mark);
        mark[min] = true;
        for(int j=0;j<V;j++){
            if(!mark[j]&&graph[min][j]&&graph[min][j]+dist[min]<dist[j])
                dist[j]=graph[min][j]+dist[min];
        }
    }
    for(int i=0;i<V;i++){
        cout<<i<<"\t\t"<<dist[i]<<"\n";
    }
}

int main(){
    int graph[V][V]={ { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                    { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                    { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                    { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                    { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                    { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                    { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                    { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                    { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    dijkstra(graph,0);
}



//* Do not use marco as the second argument to initialize all the elements as any value represented by marco

 */


// version using priority_queue

#include<bits/stdc++.h>

using namespace std;

const int V = 9;
const int mx = 10000;

void dijkstra(int graph[V][V], int pr_vertex){
    int dist[V];
    bool mark[V];
    cout<<sizeof(dist)<<endl;
    memset(dist,mx,sizeof(dist));
    memset(mark,false,sizeof(mark));
    
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> str;
    dist[pr_vertex] = 0;
    str.push(make_pair(dist[pr_vertex], pr_vertex));
    while(!str.empty()){
        int u = str.top().second;
        str.pop();
        if(mark[u]) continue;
        mark[u] = true;
        for(int i=0;i<V;i++){
            if(!mark[i]&&graph[u][i]&&graph[u][i]+dist[u]<dist[i]){
                dist[i] = graph[u][i]+dist[u];
                str.push(make_pair(dist[i], i));
            }
        }
    }
    for(int i=0;i<V;i++){
        cout<<i<<"\t\t"<<dist[i]<<"\n";
    }
}

int main(){
    ifstream df("file.txt");
    int graph[V][V];
    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            df>>graph[i][j];
    dijkstra(graph,0); 
    
}