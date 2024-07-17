#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;

class Digraph {
private:
    vector<vector<int>> adj;
    map<int,int> degrees;
    vector<int> weights;
public:
    Digraph () {}

    Digraph(int numVertices) {
        adj.resize(numVertices + 1);
        weights.resize(numVertices + 1, 0);
        degrees[0] = -1;
        for(int i = 1; i <= numVertices; i++) {
            degrees[i] = 0;
        }
    }
    
    ~Digraph() {
        adj.clear();
        degrees.clear();
        weights.clear();
    }
    
    void addEdge(int a, int b) {
        if(a < 0 || b < 0) {
            throw out_of_range("Indíce fora do intervalo!");
        }
        adj[a].push_back(b);
        addDegree(b);
    }

    void addWeight(int v, int weight){
        weights[v] = weight;
    }

    void printGraph() const {
        for (int i = 0; i < adj.size(); ++i) {
            cout << "Vertex " << i << ", ";
            cout << "Weight: " << weights[i]<< ":";
            for (int v : adj[i]) {
                cout << " " << v;
            }
            cout << endl;
        }
    }

    void printTopologicalOrder() const {
        Digraph copyDigraph = clone();
        vector<int> order = copyDigraph.topologicalOrder();
        cout<<"Topological order:"<<endl;
        for (int v : order) {
            cout << v << " ";
        }
        cout << endl;
    }

    int printLongestPath() {
        vector<int> vertices = findVerticesWithoutPredecessors();
        Digraph copyDigraph = clone();
        int longestPathSize = 0;

        for (int vertex : vertices) {
            copyDigraph.addEdge(0,vertex);
        }

        copyDigraph.degrees[0] = 0;

        stack<int> path = copyDigraph.findLongestPath(0);
        path.pop();

        cout << "Longest path:";
        while (path.size() > 0) {
            cout << " " << path.top();
            longestPathSize += weights[path.top()];
            path.pop();
            if (path.size() != 0) {
                cout << " ->";
            }
        }
        cout << endl;
        cout << "Longest path size: " << longestPathSize << endl;
        
        return longestPathSize;
    }

    void buildJobShopGraph(const vector<unsigned> machines,const vector<unsigned> times, const int nbMachines, const int nbJobs) {
        initializeGraphWithJobShopData(machines, times, nbMachines, nbJobs);
        addJobDependencies(machines, times, nbMachines, nbJobs);
    }

    int getIndexOfMaxPathElement() {
        stack<int> path = findLongestPath(0);
        path.pop();
        return path.top();
    }

    stack<int> findLongestPath(int start) {
        vector<int> order = topologicalOrder();

        // Inicializa Fonte Única
        vector<int> dist(adj.size(), INT8_MIN);
        vector<int> pi(adj.size(), -1);
        dist[start] = 0;    

        for(int u : order){
            if (dist[u] != INT8_MIN) {
                for(int v : adj[u]) {
                    relax(u, v, dist, pi);
                }
            }
        }

        int maxPathEnd = 0;
        for (int i = 1; i < adj.size(); ++i) {
            if (dist[i] > dist[maxPathEnd]) {
                maxPathEnd = i;
            }
        }

        stack<int> path;
        if (dist[maxPathEnd] == INT8_MIN) {
            cout << "No longest path found." << endl;
        } else {
            for (int v = maxPathEnd; v != -1; v = pi[v]) {
                path.push(v);
            }
        }

        return path;
    }

    Digraph clone() const {
        Digraph copy;
        copy.adj = adj;
        copy.degrees = degrees;
        copy.weights = weights;
        return copy;
    }

private:

    void addDegree(int v) {
        if (degrees.count(v)) {
            degrees[v] += 1;
        } else {
            degrees[v] = 1;
        }
    }

    void subDegree(int v) {
        degrees[v] -= 1;
    }

    void removeDegree(int v) {
        for(int node : adj[v]) {
            subDegree(node);
        }
        degrees.erase(v);
    }

    void initializeGraphWithJobShopData(const vector<unsigned> machines, const vector<unsigned> times, const int nbMachines, const int nbJobs) {
        for(int i = 0; i < nbMachines * nbJobs; i ++) {
            int job = i / nbMachines;
            int operation = i + 1;
            addWeight( operation, times[(machines[i] - 1) + job * nbMachines]);

            if(i != job * nbMachines) {
                addEdge(operation - 1, operation);
            }
        }
    }
    
    void addJobDependencies(const vector<unsigned> machines, const vector<unsigned> times, const int nbMachines, const int nbJobs) {
        vector<int> lastMachineOperation(nbMachines + 1, -1);
        for(int i = 0; i < nbJobs; i++){
            vector<vector<int>> dependencesPerMachine(nbMachines + 1);

            for(int j = 0; j < nbMachines ; j++) { 
                int operation =  (j * nbMachines) + i;
                dependencesPerMachine[machines[operation]].push_back(operation + 1);
            }

            
            for (int j = 1; j < dependencesPerMachine.size(); ++j) {
                int countCurrentMachineDependences = dependencesPerMachine[j].size(); 
                if(countCurrentMachineDependences == 0) continue;

                if(countCurrentMachineDependences == 1) {
                    if(lastMachineOperation[j] != -1) {
                        addEdge(lastMachineOperation[j], dependencesPerMachine[j][0]);
                    }
                    lastMachineOperation[j] = dependencesPerMachine[j][0];
                    continue;
                }
                
                while(!dependencesPerMachine[j].empty()) {
                    if(dependencesPerMachine[j].size() == 1) {
                        if(lastMachineOperation[j] != -1) {
                            addEdge(lastMachineOperation[j], dependencesPerMachine[j][0]);
                        }
                        lastMachineOperation[j] = dependencesPerMachine[j][0];
                        dependencesPerMachine[j].erase(dependencesPerMachine[j].begin());
                        continue;
                    }

                    Digraph copyDigraph = clone();
                    map<int,int> aux;
                    copyDigraph.degrees[0] = 0;
                    for (int k = 0; k < dependencesPerMachine[j].size(); k++) {
                        copyDigraph.degrees[dependencesPerMachine[j][k]] = 0;
                        copyDigraph.addEdge(0, dependencesPerMachine[j][k]);
                        aux[dependencesPerMachine[j][k]] = k;
                    } 
                    int chosenOperation = copyDigraph.getIndexOfMaxPathElement();
                    if(lastMachineOperation[j] != -1) {
                        addEdge(lastMachineOperation[j], dependencesPerMachine[j][aux[chosenOperation]]);
                    }
                    lastMachineOperation[j] = dependencesPerMachine[j][aux[chosenOperation]];
                    dependencesPerMachine[j].erase(dependencesPerMachine[j].begin() + aux[chosenOperation]);
                }
            }
        }
    }

    int findVertexWithoutPredecessors() {
        for(const auto& it : degrees) {
            if(it.second == 0) {
                return it.first;
            }
        }
        return -1;
    }

    vector<int> findVerticesWithoutPredecessors() {
        vector<int> vertices;
        for(const auto& it : degrees) {
            if(it.second == 0) {
                vertices.push_back(it.first);
            }
        }

        return vertices;
    }

    void topologicalOrderRec(vector<int>& t) {
        const int v = findVertexWithoutPredecessors();
        if(v == -1) return;

        t.push_back(v);
        removeDegree(v);
        topologicalOrderRec(t);
    }
    
    vector<int> topologicalOrder() {
        vector<int> t;
        // calculateDegrees();
        topologicalOrderRec(t);
        return t;
    }

    void initializeSingleSource(int start, vector<int>& dist, vector<int>& pi) {
        for(int i = 0; i < adj.size(); i++) {
            dist[i] = INT8_MIN;
            pi[i] = -1;
        }
        dist[start-1] = 0;
    }   

    void relax(int u, int v, vector<int>& dist, vector<int>& pi) {
        int weight = weights[v];
        if(dist[v] < dist[u] + weight){
            dist[v] = dist[u] + weight;
            pi[v] = u;
        }
    }

};

