#include <iostream>
#include <chrono>
#include "graph.h"

using namespace std;

double puzzleInstance(Board board, Board goal, bool stepByStep) {
    Graph graph(board, 9, 3);
    auto start = std::chrono::high_resolution_clock::now();
    graph.a_star(board, goal, 3, stepByStep);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double executionTime = duration.count();

    return executionTime;
}


void displayMenu() {
    std::cout << "===== MENU =====\n";
    std::cout << "1. Resolver 8-puzzle usando A*\n";
    std::cout << "2. Resolver 15-puzzle usando A*\n";
    std::cout << "3. Resolver 8-puzzle usando IDA*\n";
    std::cout << "4. Resolver 15-puzzle usando IDA*\n";
    std::cout << "5. Sair\n";
    std::cout << "================\n";
    std::cout << "Selecione uma opcao: ";
}

void stepByStepMenu(bool isAStar, bool is15Puzzle) {
    char choice;
    cout << "Deseja ver a solução passo a passo? (s/n): ";
    cin >> choice;

    // vector<vector<int>> m(9, vector<int>(9,0));
    vector<int> board = {5, 6, 2, 7, 1, 8, 3, 4, 0};
    vector<int> goal = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> start = {1, 0, 2, 3, 4, 5, 6, 7, 8};
    Board b1 = {board,INT32_MAX};
    Board b2 = {goal,INT32_MAX};


    bool stepByStep = (choice == 's' || choice == 'S');
    // auto start = std::chrono::high_resolution_clock::now();

    if (isAStar) {
        // solvePuzzleAStar(stepByStep, is15Puzzle);
        puzzleInstance(b1, b2, stepByStep);
    } else {
        // solvePuzzleIDAStar(stepByStep, is15Puzzle);
    }

    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = end - start;
    // std::cout << "Tempo de execução: " << elapsed.count() << " segundos\n";
}

int main() {
    // vector<vector<int>> m(9, vector<int>(9,0));
    // vector<int> board = {5, 6, 2, 7, 1, 8, 3, 4, 0};
    // vector<int> goal = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    // vector<int> start = {1, 0, 2, 3, 4, 5, 6, 7, 8};
    // Board b1 = {board,INT32_MAX};
    // Board b2 = {goal,INT32_MAX};
    // Graph graph(b1, 9, 3);

    // cout << "Tempo de execução: " << puzzleInstance(b1, b2) << endl;

    int option;

    do {
        displayMenu();
        cin >> option;

        switch (option) {
            case 1:
                stepByStepMenu(true, false);
                break;
            case 2:
                stepByStepMenu(true, true);
                break;
            case 3:
                stepByStepMenu(false, false);
                break;
            case 4:
                stepByStepMenu(false, true);
                break;
            case 5:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida! Tente novamente.\n";
        }
        cout << "\n";
    } while (option != 5);

    return 0;
}