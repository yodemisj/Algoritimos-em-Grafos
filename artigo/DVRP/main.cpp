#include "Graph.h"

using namespace std; 

void printVector(vector<int> v) {
    for(size_t i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

void initializeGraph(Graph& graph) {
    // graph = Graph(5);

    graph.setLoadCost(1, 5);
    graph.setLoadCost(2, 4);
    graph.setLoadCost(3, 4);
    graph.setLoadCost(4, 2);
    graph.setLoadCost(5, 7);
    
    graph.addEdge(0, 1, 20);
    graph.addEdge(1, 0, 20);
    graph.addEdge(0, 2, 25);
    graph.addEdge(2, 0, 25);
    graph.addEdge(0, 3, 30);
    graph.addEdge(3, 0, 30);
    graph.addEdge(0, 4, 40);
    graph.addEdge(4, 0, 40);
    graph.addEdge(0, 5, 35);
    graph.addEdge(5, 0, 35);

    graph.addEdge(1, 2, 10);
    graph.addEdge(2, 3, 30);
    graph.addEdge(3, 4, 25);
    graph.addEdge(4, 5, 15);

    vector<int> V(6);
    vector<int> P(6);
    // vector<int> trip(6);
    vector<vector<int>> trip;

    graph.splitProcedure(P, 10, INF);
    graph.extractSolution(P, trip);
    // trip = graph.extractSolution(P, 5);

    // printVector(V);
    printVector(P);
    // printVector(trip);

    for (size_t i = 0; i < trip.size(); ++i) {
        cout << "Rota " << i + 1 << ": ";
        for (int customer : trip[i]) {
            cout << customer << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<int> p1 = {1, 3, 2, 6, 4, 5, 9, 7, 8};
    vector<int> p2 = {3, 7, 8, 1, 4, 9, 2, 5, 6};
    vector<int> c1(p1.size());
    vector<int> c2(p1.size());

    // crossoverOX(p1, p2, c1, c2);

    // printVector(c1);
    // printVector(c2);

    Graph graph(5);

    initializeGraph(graph);

    return 0;
}