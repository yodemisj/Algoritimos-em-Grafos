// #include <iostream>
// #include <random>
// #include <vector>
// #include <algorithm>
// #include <limits>
#include "Graph.h"

using namespace std; 

// const int INF = numeric_limits<int>::infinity();

void printVector(vector<int> v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

void crossoverOX(const vector<int> p1, const vector<int> p2, vector<int>& c1, vector<int>& c2) {
    int p1Size = p1.size();
    int p2Size = p2.size();

    if(p1Size != p2Size) {
        return; 
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, p1Size - 2);
    int i = dis(gen);
    int j = dis(gen);

    while (j <= i) {
        j = dis(gen);
    }

    cout << "i: " << i << " j: " << j << "\n";

    for(int k = i; k <= j; k++) {
        c1[k] = p1[k];
        c2[k] = p2[k];
    }
    
    int indexC1 = (j + 1) % p1Size; 
    int indexC2 = (j + 1) % p1Size; 

    for (int k = j + 1; k < p1Size + j + 1; k++) {
        int index = k % p1Size;

        auto itP1 = find(c2.begin(), c2.end(), p1[index]);
        auto itP2 = find(c1.begin(), c1.end(), p2[index]);

        if(itP1 == c2.end()) {
            c2[indexC2] = p1[index];
            indexC2++;
            indexC2 %= p1Size;
        }

        if(itP2 == c1.end()) {
            c1[indexC1] = p2[index];
            indexC1++;
            indexC1 %= p1Size;
        }
    }
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
    vector<int> trip;

    graph.splitProcedure(5, V, P, 10, INF);
    graph.extractSolution(5, P, trip);

    printVector(V);
    printVector(P);
    printVector(trip);
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