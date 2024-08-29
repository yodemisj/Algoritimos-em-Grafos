#include "includes.h"
#include "graph.h"
#include "fileUtils.h"

using namespace std;

vector<Board> puzzle_8_instances;
vector<Board> puzzle_15_instances;

double solvePuzzleAStar(Board board, Board goal, bool stepByStep, int puzzleSize, int lineSize) {
    Graph graph(board, puzzleSize, lineSize);
    map<vector<int>, Board> pi;
    vector<Board> solutionSteps;
    FileUtils fileUtils;

    auto start = std::chrono::high_resolution_clock::now();
    pi = graph.a_star(board, goal, lineSize);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double executionTime = elapsed.count();

    Board current = goal;

    while (current.first != board.first) {
        solutionSteps.push_back(current);
        current = pi[current.first]; 
    }

    solutionSteps.push_back(board);

    cout << "Passos na solução ótima: " << solutionSteps.size() << "\n";

    reverse(solutionSteps.begin(), solutionSteps.end());

    if(stepByStep) fileUtils.saveSolutionSteps("saida.out", solutionSteps, lineSize);

    return executionTime;
}

// double solvePuzzleIDAStar(Board board, Board goal, bool stepByStep, int puzzleSize, int lineSize) {
//     Graph graph(board, puzzleSize, lineSize);
//     map<vector<int>, Board> pi;
//     vector<Board> solutionSteps;
//     FileUtils fileUtils;

//     auto start = std::chrono::high_resolution_clock::now();
//     pi = graph.ida_star(board, goal, lineSize);
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> elapsed = end - start;
//     double executionTime = elapsed.count();

//     Board current = goal;

//     while (current.first != board.first) {
//         solutionSteps.push_back(current);
//         current = pi[current.first]; 
//     }

//     solutionSteps.push_back(board);

//     reverse(solutionSteps.begin(), solutionSteps.end());

//     if(stepByStep) fileUtils.saveSolutionSteps("saida.out", solutionSteps, lineSize);

//     return executionTime;
// }


void displayMenu() {
    cout << "===== MENU =====\n";
    cout << "1. Resolver 8-puzzle usando A*\n";
    cout << "2. Resolver 15-puzzle usando A*\n";
    // cout << "3. Resolver 8-puzzle usando IDA*\n";
    // cout << "4. Resolver 15-puzzle usando IDA*\n";
    cout << "3. Sair\n";
    cout << "================\n";
    cout << "Selecione uma opcao: ";
}

void displaySubMenu() {    
    cout << "Escolha uma das opcoes abaixo:\n";
    cout << "1. Executar instancia expecifica\n";
    cout << "2. Executar todas as instancias\n";
    cout << "3. Sair\n";
}

void stepByStepMenu(bool isAStar, bool is15Puzzle) {
    char choice;
    int option;
    bool stepByStep = false;
    size_t instanceNumber;
    double executionTime;

    displaySubMenu();
    cin >> option;

    vector<Board>& instances = is15Puzzle ? puzzle_15_instances : puzzle_8_instances;
    int puzzleSize = is15Puzzle ? 16 : 9;
    int lineSize = is15Puzzle ? 4 : 3;
    vector<int> goal(puzzleSize);

    for(int i = 0; i < puzzleSize; i++) {
        goal[i] = i;
        
    }
    
    Board goalBoard = {goal, INT32_MAX};

    switch (option) {
        case 1:
            cout << "Digite o Numero da instância(1 - " << instances.size() << ")" << ": ";
            cin >> instanceNumber;

            if (instanceNumber < 1 || instanceNumber > instances.size()) {
                cout << "Numero de instancia invalido!\n";
                return;
            }

            cout << "Deseja ver a solução passo a passo? (s/n): ";
            cin >> choice;

            stepByStep = (choice == 's' || choice == 'S');

            cout << "\n";
            if (isAStar) {
                cout << "Numero da instância: " << instanceNumber << "\n"; 
                executionTime = solvePuzzleAStar(instances[instanceNumber - 1], goalBoard, stepByStep, puzzleSize, lineSize);
                cout << "Tempo de execução: " << executionTime << " segundos\n";
            } 
            // else {
            //     // solvePuzzleIDAStar(stepByStep, is15Puzzle);
            //     executionTime = solvePuzzleIDAStar(instances[instanceNumber - 1], goalBoard, stepByStep, puzzleSize, lineSize);
            //     cout << "Tempo de execução: " << executionTime << " segundos\n";

            // }

            break;
        case 2:
            if (isAStar) {
                for(size_t i = 1; i <= instances.size(); i++) {
                    cout << "\n";
                    instanceNumber = i;
                    cout << "Numero da instância: " << instanceNumber << "\n"; 
                    executionTime = solvePuzzleAStar(instances[instanceNumber - 1], goalBoard, stepByStep, puzzleSize, lineSize);
                    cout << "Tempo de execução: " << executionTime << " segundos\n";
                }
            
            } 
            // else {
            //     executionTime = solvePuzzleIDAStar(instances[instanceNumber - 1], goalBoard, stepByStep, puzzleSize, lineSize);
            //     cout << "Tempo de execução: " << executionTime << " segundos\n";
            // }
            break;

        default:
            return;
    }
}

int main() {
    int option;
    FileUtils fileUtils;

    fileUtils.readInstances("./ins/8puzzle_instances.txt", puzzle_8_instances);
    fileUtils.readInstances("./ins/15puzzle_instances.txt", puzzle_15_instances);

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
            // case 3:
            //     stepByStepMenu(false, false);
            //     break;
            // case 4:
            //     stepByStepMenu(false, true);
            //     break;
            case 3:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida! Tente novamente.\n";
                break;
        }
        cout << "\n";
    } while (option != 3);

    return 0;
}