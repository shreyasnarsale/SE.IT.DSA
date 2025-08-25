//Problem Statement:- 
/* 
Represent a graph of your college campus using adjacency list /adjacency matrix. Nodes should 
represent the various departments/institutes and links should represent the distance between them. 
Find minimum spanning tree 
 a) Using Kruskal’s algorithm. 
 b) Using Prim’s algorithm. 
*/


//Using Kruskal’s algorithm
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int V;
    vector<pair<int, pair<int, int>>> edges; // weight, (u,v)

public:
    Graph(int V) : V(V) {}
    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u, v}});
    }

    int findSet(vector<int>& parent, int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = findSet(parent, parent[i]);
    }

    void unionSet(vector<int>& parent, int u, int v) {
        int uRep = findSet(parent, u);
        int vRep = findSet(parent, v);
        parent[uRep] = vRep;
    }

    void kruskal() {
        sort(edges.begin(), edges.end());
        vector<int> parent(V);
        for (int i = 0; i < V; i++) parent[i] = i;

        int totalWeight = 0;
        cout << "\nEdges in MST:\n";
        for (auto edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int w = edge.first;

            if (findSet(parent, u) != findSet(parent, v)) {
                cout << u << " - " << v << " : " << w << endl;
                totalWeight += w;
                unionSet(parent, u, v);
            }
        }
        cout << "Total weight of MST: " << totalWeight << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u >= V || v >= V || u < 0 || v < 0 || w <= 0) {
            cout << "Invalid input. Try again.\n";
            i--;
            continue;
        }
        g.addEdge(u, v, w);
    }

    g.kruskal();

    return 0;
}




//Using Prim’s algorithm

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class MST {
    int nodes;
    vector<vector<int>> G;

public:
    void get_data();
    void prim();
};

void MST::get_data() {
    int edges;
    cout << "Enter number of nodes: ";
    cin >> nodes;
    G.assign(nodes, vector<int>(nodes, 0));

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges in format: u v weight\n";
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u >= nodes || v >= nodes || u < 0 || v < 0 || w <= 0) {
            cout << "Invalid input. Try again.\n";
            i--;
            continue;
        }
        G[u][v] = w;
        G[v][u] = w;
    }
}

void MST::prim() {
    vector<int> key(nodes, numeric_limits<int>::max());
    vector<int> parent(nodes, -1);
    vector<bool> mstSet(nodes, false);

    key[0] = 0; // Start from node 0

    for (int count = 0; count < nodes - 1; count++) {
        int minKey = numeric_limits<int>::max(), u;

        for (int v = 0; v < nodes; v++)
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }

        mstSet[u] = true;

        for (int v = 0; v < nodes; v++)
            if (G[u][v] && !mstSet[v] && G[u][v] < key[v]) {
                key[v] = G[u][v];
                parent[v] = u;
            }
    }

    int totalWeight = 0;
    cout << "\nEdges in MST:\n";
    for (int i = 1; i < nodes; i++) {
        cout << parent[i] << " - " << i << " : " << G[i][parent[i]] << endl;
        totalWeight += G[i][parent[i]];
    }
    cout << "Total weight of MST: " << totalWeight << endl;
}

int main() {
    MST mst;
    mst.get_data();
    mst.prim();
    return 0;
}
