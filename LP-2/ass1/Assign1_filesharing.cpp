#include<bits/stdc++.h>
using namespace std;

class Graph {
    
    vector<vector<int>> graph = {
        {0,0,1,0,1},
        {0,0,0,0,0},
        {1,0,0,0,1},
        {0,0,0,0,1},
        {1,0,1,1,0}        
    };

    int n = 5;

    vector<bool> visited = {0,0,0,0,0};

    public:

    // using dfs for finding the failure detection 
    void dfs(int node, vector<bool> &visited){
        visited[node] = true;
        
        for(int v = 0; v<n; v++){
            if(graph[node][v] == 1 && !visited[v]){
                dfs(v, visited);
            }
        }
    }
    
    // file sharing using bfs
    vector<bool> bfsFileSharing(int s){
        vector<bool> visited(n, false);
        queue<int> q;

        visited[s] = true;
        q.push(s);

        while(!q.empty()){
            int u = q.front();
            q.pop();

            for(int v = 0; v < n ; v++){
                if(graph[u][v] == 1 && !visited[v]){
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return visited;
    }

    int bfsjumps(int src, int dest){
        vector<int> dist(n, -1);
        queue<int> q;

        dist[src] = 0;
        q.push(src);

        while(!q.empty()){
            int u = q.front();
            q.pop();

            if(u == dest) return dist[u];

            for(int v = 0; v<n; v++){
                if(graph[u][v] == 1 && dist[v] == -1){
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return -1;
    }

    vector<int> failedComputers(int src){
        vector<bool> visited(n, false);
        dfs(src , visited);

        vector<int> failed;
        for(int i=0; i<n; i++){
            if(!visited[i]){
                failed.push_back(i);
            }
        }
        return failed;
    }

};

int main(){
  
    
    Graph g;

    // scenario 1 : 1 file to be shared to target locationss 

    vector<bool> received = g.bfsFileSharing(0);
    cout<<"File received status: "<<endl;
    for(int i=0; i<received.size(); i ++){
        cout<<"Computer "<< i <<": "<< ( received[i] ? ("Received") : ("Not Received")) << endl;
    }


    // scenario 2 : Failure detection 
    vector<int> failed = g.failedComputers(0);
    cout<<"\n Failed computer: \n";
    for(int x: failed){
        cout<<x<<" ";
    }
    
    cout<<endl<<endl;

    // scenario 3 : Number of jumps

    cout<<"No. of jumps from 0 to 3: "<<
        g.bfsjumps(0, 3) <<endl;


    return 0;


}

