#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
private: 
    vector<vector<int>> adj;
    vector<vector<int>> weights;
    vector<int> loadCost;

public:
    Graph(int n) {
        adj.resize(n + 1, vector<int>());
        loadCost.resize(n + 1, 0);
        weights.resize(n + 1, vector<int>(n + 1, -1));
    }

    ~Graph() {
        adj.clear();
        weights.clear();
    }

    void addEdge(const int u,const int v, const int weight) {
            adj[u].push_back(v);
            setWeigth(u, v, weight);
    }

    void setWeigth(const int u, const int v, const int weight) {
        weights[u][v] = weight;
    }

    void setLoadCost(const int u, const int cost) {
        loadCost[u] = cost;
    }

    void splitProcedure(int n, vector<int>& V, vector<int>& P, int W, int L) {
        V[0] = 0;

        for(int i = 1; i <= n; i++) {
            V[i] = INF;
        }

        for(int i = 1; i <= n; i++ ) {
            int load = 0;
            int cost = 0;

            int j = i;

            do {
                load += loadCost[j];
                // cout << load << endl;
                if (i == j) {
                    cost += weights[0][j] + weights[j][0];
                } else {
                    cost = cost - weights[j-1][0] + weights[j-1][j] + weights[j][0];
                }

                if(load <= W && cost <= L) {
                    if (V[i-1] + cost < V[j]) { // Relaxa
                        V[j] = V[i-1] + cost;
                        P[j] = i - 1;
                    }
                    j++;
                } else {
                    break;
                }

            } while (j <= n);
        }
    }

    void extractSolution(const int n, const vector<int>& P, vector<int>& trip) {
        trip.clear();
        
        int t = 0;
        int j = n; 
        int i;

        do {
            t += 1;
            i = P[j];
            for(int k = i + 1; k <= j; k++) { 
                trip.push_back(k);
            }
            j = i;
        } while (i > 0);
    }

};
