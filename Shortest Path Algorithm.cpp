//Problem Statement:- 
/* 
Represent a graph of city using adjacency matrix /adjacency list. Nodes should represent the various 
landmarks and links should represent the distance between them. Find the shortest path using 
Dijkstra's algorithm from single source to all destination. 
*/ 


#include <iostream>
#include <limits>
using namespace std;

#define MAX 20
#define INF 9999

class Graph {
private:
    int g[MAX][MAX];
    int n;
    char v[MAX];

public:
    Graph(int nodes) {
        n = nodes;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g[i][j] = 0;
    }

    void acceptVertices() {
        cout << "\nEnter Names of Landmarks:\n";
        for (int i = 0; i < n; i++) {
            cout << "Landmark [" << i + 1 << "]: ";
            cin >> v[i];
        }
    }

    void acceptEdges() {
        cout << "\nEnter Distance Between Landmarks:\n";
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                cout << "Distance between " << v[i] << " and " << v[j] << ": ";
                cin >> g[i][j];
                g[j][i] = g[i][j]; // symmetric for undirected graph
            }
        }
    }

    void displayMatrix() {
        cout << "\nAdjacency Matrix:\n\t";
        for (int i = 0; i < n; i++)
            cout << v[i] << "\t";
        cout << "\n";

        for (int i = 0; i < n; i++) {
            cout << v[i] << "\t";
            for (int j = 0; j < n; j++)
                cout << g[i][j] << "\t";
            cout << "\n";
        }
    }

    void dijkstra(char source) {
        int dist[MAX];
        bool visited[MAX] = {false};
        int prev[MAX]; // to store path

        int sIndex = -1;
        for (int i = 0; i < n; i++) {
            if (v[i] == source) {
                sIndex = i;
                break;
            }
        }

        if (sIndex == -1) {
            cout << "Source landmark not found!\n";
            return;
        }

        for (int i = 0; i < n; i++) {
            dist[i] = INF;
            prev[i] = -1;
        }
        dist[sIndex] = 0;

        for (int count = 0; count < n - 1; count++) {
            int u = -1;
            int minDist = INF;

            for (int i = 0; i < n; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }

            if (u == -1) break; // all remaining nodes are inaccessible

            visited[u] = true;

            for (int vIndex = 0; vIndex < n; vIndex++) {
                if (!visited[vIndex] && g[u][vIndex] != 0 && dist[u] + g[u][vIndex] < dist[vIndex]) {
                    dist[vIndex] = dist[u] + g[u][vIndex];
                    prev[vIndex] = u;
                }
            }
        }

        cout << "\nShortest distances from " << source << " to all landmarks:\n";
        for (int i = 0; i < n; i++) {
            cout << source << " -> " << v[i] << " = " << dist[i] << "\tPath: ";
            printPath(prev, sIndex, i);
            cout << "\n";
        }
    }

    void printPath(int prev[], int start, int end) {
        if (end == start) {
            cout << v[start];
        } else if (prev[end] == -1) {
            cout << "No path";
        } else {
            printPath(prev, start, prev[end]);
            cout << " -> " << v[end];
        }
    }
};

int main() {
    int n, choice;
    cout << "Enter number of landmarks: ";
    cin >> n;

    Graph g(n);

    do {
        cout << "\nGraph Menu:\n";
        cout << "1. Accept Names of Landmarks\n";
        cout << "2. Accept Distance Between Landmarks\n";
        cout << "3. Display Adjacency Matrix\n";
        cout << "4. Display Shortest Distances (Dijkstra)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        char src;
        switch (choice) {
            case 1: g.acceptVertices(); break;
            case 2: g.acceptEdges(); break;
            case 3: g.displayMatrix(); break;
            case 4:
                cout << "Enter Source Landmark: ";
                cin >> src;
                g.dijkstra(src);
                break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
