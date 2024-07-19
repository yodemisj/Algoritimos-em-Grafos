#include <iostream>
#include "DAG.h"
#include "FileUtils.h"
#include <vector>
#include <string>
#include <chrono>
#include <tuple>

// Numero de vertices do Grafo Estático
#define N 15
#define JOB_SHOP_INSTANCES 10

using namespace std;

void fixedGraphInstance() {
    Digraph fixedGraph(N);
    
    for(int i = 1; i <= N; i++){
        fixedGraph.addWeight(i, i);
    }

    fixedGraph.addEdge(4, 3);
    fixedGraph.addEdge(4, 1);
    fixedGraph.addEdge(3, 5);
    fixedGraph.addEdge(5, 15);
    fixedGraph.addEdge(15, 6);
    fixedGraph.addEdge(15, 9);
    fixedGraph.addEdge(10, 1);
    fixedGraph.addEdge(10, 3);
    fixedGraph.addEdge(1, 2);
    fixedGraph.addEdge(1, 11);
    fixedGraph.addEdge(11, 14);
    fixedGraph.addEdge(11, 15);
    fixedGraph.addEdge(14, 13);
    fixedGraph.addEdge(14, 5);
    fixedGraph.addEdge(13, 6);
    fixedGraph.addEdge(7, 10);
    fixedGraph.addEdge(7, 8);
    fixedGraph.addEdge(8, 2);
    fixedGraph.addEdge(8, 14);
    fixedGraph.addEdge(2, 12);
    fixedGraph.addEdge(12, 9);
    fixedGraph.addEdge(12, 13);

    fixedGraph.printTopologicalOrder();

    fixedGraph.printLongestPath();
}

tuple<int, int, double> jobShopInstance(const int instance) {
    FileUtils fileUtils;
    vector<unsigned> times;
    vector<unsigned> machines;
    int nbJobs, nbMachines, makeSpan;
    string filePath = "./ins/" + to_string(instance) + ".in";

    fileUtils.readFile(filePath, times, machines, nbJobs, nbMachines);

    Digraph jobShop(nbJobs*nbMachines);

    auto start = std::chrono::high_resolution_clock::now();
    jobShop.buildJobShopGraph(machines, times, nbMachines, nbJobs);
    auto end = std::chrono::high_resolution_clock::now();
    makeSpan = jobShop.printLongestPath();
    std::chrono::duration<double> duration = end - start;

    cout << endl;
    jobShop.printTopologicalOrder();
    cout<<endl;

    double executionTime = duration.count();

    tuple<int, int, double> result = make_tuple(instance, makeSpan, executionTime);

    cout << "Instancia " << instance << ": makeSpan = " << makeSpan << ", Tempo de Execucao = " << executionTime << "s" << endl;
    cout<<endl;

    return result;
}

void jobShopInstances() {
    FileUtils fileUtils;
    vector<int> indexes;
    vector<int> makeSpans;
    vector<double> executionTimes;

    for(int i = 1; i <= JOB_SHOP_INSTANCES; i++) {
        tuple<int, int, double> result = jobShopInstance(i);
        indexes.push_back(get<0>(result));
        makeSpans.push_back(get<1>(result));
        executionTimes.push_back(get<2>(result));
    }

    fileUtils.generateCSV("./out/Saida.csv", indexes, makeSpans, executionTimes);
}

void showMenu() {
    cout << "Escolha uma das opcoes abaixo:\n";
    cout << "1. Grafo Fixo\n";
    cout << "2. Instancias do Job Shop\n";
    cout << "3. Sair\n";
    cout << "Digite a opcao desejada: ";
}

void showSubMenu() {    
    cout << "Escolha uma das opcoes abaixo:\n";
    cout << "1. Executar instancia expecifica\n";
    cout << "2. Executar todas as instancias\n";
    cout << "3. Sair\n";
}

int main() {
    int chosen;
    while (true) {
        showMenu();
        cin >> chosen;

        switch (chosen) {
            case 1:
                try {
                    cout<<endl;
                    fixedGraphInstance();
                    cout<<endl;
                } catch (const out_of_range& e) {   
                    cout << "Excecao Capturada: " << e.what()<<endl;
                    return -1;
                }
                break;
            case 2:
                cout << endl;
                showSubMenu();
                int option, instance;
                cin >> option;
                switch (option) {
                case 1:
                    cout << "Digite o numero da instancia ( 1 a 10 ):" << endl;
                    cin >> instance;
                    try {
                        cout << endl;
                        jobShopInstance(instance);
                    } catch(const runtime_error& e) {
                        cout << "Excecao Capturada: " << e.what()<<endl;
                        return -1;
                    }
                    break;
                case 2:
                    try {
                        cout << endl;
                        jobShopInstances();
                        cout << endl;
                    } catch(const runtime_error& e) {
                        cout << "Excecao Capturada: " << e.what()<<endl;
                        return -1;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 3:
                cout << "Saindo...\n";
                return 0;
            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    }

    return 0;
}