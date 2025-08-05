#include<iostream>
#include<unordered_map>
#include<list>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>

using namespace std;
template <typename T>


class graphs {
public:
    unordered_map<T, list<T>> abj; // For unweighted graph
    unordered_map<T, list<pair<T, int>>> adjlist; // For weighted graph

    // Add edge for unweighted graph
    void addedge(T u, T v, bool direction) {
        // direction = 0 -> undirected
        // direction = 1 -> directed
        abj[u].push_back(v);

        if (direction == 0) {
            abj[v].push_back(u);
        }
    }

    // Add edge for weighted graph
    void addedge(T u, T v, int weight) {
        pair<T, int> p = make_pair(v, weight);
        adjlist[u].push_back(p);
    }

    // Print weighted adjacency list
    void print_adjlist() {
        for (auto i : adjlist) {
            cout << i.first << " -> ";
            for (auto j : i.second) {
                cout << "(" << j.first << "," << j.second << ") ";
            }
            cout << endl;
        }
    }

    // Print unweighted adjacency list
    void printadj() {
        for (auto i : abj) {
            cout << i.first << " -> ";
            for (auto j : i.second) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};

void bfs(unordered_map<int, list<int>>& adjlist, unordered_map<int, bool>& visited, int start, vector<int>& component) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int frontnode = q.front();
        q.pop();
        component.push_back(frontnode);

        for (auto neighbor : adjlist[frontnode]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

vector<vector<int>> BFS(int vertices, vector<pair<int, int>> edges) {
    unordered_map<int, list<int>> adjlist;
    unordered_map<int, bool> visited;

    // Build adjacency list
    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    vector<vector<int>> components;

    // BFS for each unvisited node
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            vector<int> component;
            bfs(adjlist, visited, i, component);
            components.push_back(component);
        }
    }

    return components;
}

void dfs(unordered_map<int,list<int>> &adjlist,unordered_map<int,bool> &visited,int i,vector<int> &ans) {
    ans.push_back(i);
    visited[i]=true;

    for( auto j: adjlist[i]) {
        if(!visited[j]) {
            dfs(adjlist,visited,j,ans);
        }
    }
} 

vector<vector<int>> DFS(int v,int e,vector<pair<int,int>> edges) {
    unordered_map<int,list<int>> adjlist;
    unordered_map<int,bool> visited;

    for(int i=0;i<edges.size();i++) {
        int u=edges[i].first;
        int v=edges[i].second;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }
    vector<vector<int>> components;

    for(int i=0;i<v;i++) {
        if(!visited[i]) {
            vector<int> comps;
            dfs(adjlist,visited,i,comps);
            components.push_back(comps);
        }
    }
    return components;
}

void printComponents(const vector<vector<int>> &components) {
    cout << "Connected Components:\n";
    for (const auto &comp : components) {
        for (int node : comp) {
            cout << node << " ";
        }
        cout << endl;
    }
}

bool iscyclicBFS(int i,unordered_map<int,list<int>> &adjlist,unordered_map<int,bool> &visited) {
    queue<pair<int,int>> q;
    q.push({i,-1});
    visited[i]=true;

    while(!q.empty()) {
        int node=q.front().first;
        int parent=q.front().second;

        q.pop();
        for(auto neighbour:adjlist[node]) {
            if(!visited[neighbour]) {
                visited[neighbour]=true;
                q.push({neighbour,node});
            } else if(neighbour!= parent) {
                return true;
            }
        }
    }
    return false;
}

bool detectcycle(int v,vector<pair<int,int>> &edges) {
    unordered_map<int,list<int>> adjlist;
    unordered_map<int,bool> visited;

    for(int i=0;i<edges.size();i++) {
        int u=edges[i].first;
        int v=edges[i].second;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    for(int i=0;i<v;i++) {
        if(!visited[i]) {
            if(iscyclicBFS(i,adjlist,visited)) {
                return true;
            }
        }

    }
    return true;
}

//in directed cycle detection



bool dfs(int node, vector<int> adj[], vector<bool>& visited, vector<bool>& recStack) {
        visited[node] = true;
        recStack[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, adj, visited, recStack))
                    return true;
            } else if (recStack[neighbor]) {
                // Found node in current recursion stack → cycle
                return true;
            }
        }

        recStack[node] = false; // Backtrack
        return false;
    }
bool isCyclic(int V, vector<int> adj[]) {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, adj, visited, recStack))
                    return true;
            }
        }
        return false;
}

//cycle detection using bfs(kahn algo)
bool cycle_detectionin_bfs(vector<vector<int>> &edges,int v,int e) {
    unordered_map<int,list<int>> adj;
    for(int i=0;i<e;i++) {
        int u=edges[i][0];
        int v=edges[i][1];
        adj[u].push_back(v);
    }

    unordered_map<int, int> indegree;
    for(auto i:adj) {
        for(auto j:i.second) {
            indegree[j]++;
        }
    }
    queue<int> q;
    for(auto &it: indegree) {
        if(it.second == 0) {
            q.push(it.first);
        }
    }

    //do bfs
    int cnt=0;
    while(!q.empty()) {
        int front=q.front();
        q.pop();

        cnt++;

        for(auto neighbour :adj[front]) {
            indegree[neighbour]--;
            if(indegree[neighbour]==0) {
                q.push(neighbour);
            }
        }
    }
    if(cnt==v) return false;//if count of elemnts in q is equal to no of vertex then there is no cycle
    return true;
}


//topological sort

void toposort(int node,unordered_map<int,bool> &visited,stack<int> &s,unordered_map<int,list<int>> &adj) {
    visited[node]=true;

    for(auto neighbour:adj[node]) {
        if(!visited[neighbour]) {
            toposort(neighbour,visited,s,adj);
        }
    }
    s.push(node);
}

vector<int> topologicalsort(vector<vector<int>> edges,int v,int e) {
    unordered_map<int,list<int>> adj;
    for(int i=0;i<e;i++) {
        int u=edges[i][0];
        int v=edges[i][1];

        adj[u].push_back(v);

    }

    unordered_map<int,bool> visited;
    stack<int> s;
    for(int i=0;i<v;i++) {
        if(!visited[i]) {
            toposort(i,visited,s,adj);
        }
    }
    vector<int> ans;
    while(!s.empty()) {
        ans.push_back(s.top()); 
        s.pop(); 
    }

    return ans;
}

//kahn's algorithum>...

vector<int> kahnalgo(vector<vector<int>> &edges,int v,int e) {
    unordered_map<int,list<int>> adj;
    for(int i=0;i<e;i++) {
        int u=edges[i][0];
        int v=edges[i][1];
        adj[u].push_back(v);
    }

    unordered_map<int, int> indegree;
    for(auto i:adj) {
        for(auto j:i.second) {
            indegree[j]++;
        }
    }
    queue<int> q;
    for(auto &it: indegree) {
        if(it.second == 0) {
            q.push(it.first);
        }
    }

    //do bfs
    vector<int> ans;
    while(!q.empty()) {
        int front=q.front();
        q.pop();

        ans.push_back(front);

        for(auto neighbour :adj[front]) {
            indegree[neighbour]--;
            if(indegree[neighbour]==0) {
                q.push(neighbour);
            }
        }
    }
    return ans;
}

//shortest pathh

vector<int> shortestpath(vector<pair<int,int>> edges,int n,int m ,int s,int t) {
    unordered_map<int,list<int>> adj;
    for(int i=0;i<edges.size();i++) {
        int u=edges[i].first;
        int v=edges[i].second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //bfs
    unordered_map<int,bool> visited;
    unordered_map<int,int> parent;
    queue<int> q;
    q.push(s);
    parent[s]=-1;

    visited[s]=true;

    while(!q.empty()) {
        int front=q.front();
        q.pop();
        for(auto i:adj[front]) {
            if(!visited[i]) {
                visited[i]=true;
                parent[i]=front;
                q.push(i);
            }
        }
    }

    //prep shortest path 
    vector<int> ans;
    int crntnode=t;
    ans.push_back(t);

    while(crntnode!=-1) {
        crntnode=parent[crntnode];
        ans.push_back(crntnode);
    }
    reverse(ans.begin(),ans.end());
    return ans;

}

//shortest path in directed acyclic path
 

int main() {

    // int n;
    // cout<<"enter the no of edges "<<endl;
    // cin>>n;
    // int m;
    // cout<<"enter the no of nodes"<<endl;
    // cin>>m;

    // // graphs<int> g;

    // // for(int i=0;i<n;i++) {
    // //     int u,v;
    // //     cin>>u>>v;
    // //     g.addedge(u,v,0);
    // // }

    // // g.printadj();
    // vector<pair<int,int>> a;
    // for(int i=0;i<n;i++) {
    //     int u,v;
    //     cin>>u>>v;
    //     a.push_back({u,v});
    // }
    // printComponents(DFS(m,n,a));

    graphs<int> g;
    g.addedge(0,1,5);
    g.addedge(0,2,3);
    g.addedge(1,2,2);
    g.addedge(1,3,6);
    g.addedge(2,3,7);
    g.addedge(2,4,4);
    g.addedge(2,5,2);
    g.addedge(3,4,-1);
    g.addedge(4,5,-2);
    g.print_adjlist();
    return 0;
}