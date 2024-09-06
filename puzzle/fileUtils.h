#pragma once
#include "includes.h"

class FileUtils {
public:
    static void readInstances(const string& filePath, vector<Board>& puzzles) {
        ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            throw runtime_error("Erro ao abrir o arquivo!");
        }

        string aux;
        while (getline(inputFile, aux)) {
            vector<int> board;
            int num;

            for (istringstream iss(aux); iss >> num;) {
                board.push_back(num);
            }
            
            if (!board.empty()) {
                puzzles.push_back({board, INT32_MAX});
            }
        }
    }
    static void saveSolutionSteps(const string& filePath, const vector<Board>& solutionSteps, const int lineSize) {
        ofstream file(filePath);

        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo " << filePath << endl;
            return;
        }

        for (size_t i = 0; i < solutionSteps.size(); ++i) {
            file << "Step " << i + 1 << ":\n";

            const vector<int>& board = solutionSteps[i].first;

            for (int j = 0; j < lineSize; ++j) {
                for (int k = 0; k < lineSize; ++k) {
                    file << board[j * lineSize + k] << " ";
                }
                file << "\n";
            }

            // file << "Manhattan Distance + Distance: " << solutionSteps[i].second << "\n\n";
        }

        file.close();
    }
    static void saveAStarResultsToCSV(const string& filePath, const vector<int>& instanceNumbers, const vector<int>& evaluatedStates, const vector<int>& solutionSteps, const vector<double>& executionTimes) {
        ofstream file(filePath);

        // Escreve o cabeçalho do CSV
        file << "Numero da Instancia;Numero de Estados Avaliados;Passos na Solucao Otima;Tempo de Execucao (s)\n";

        // Para cada instância, escreve o número da instância, estados avaliados, passos da solução e tempo de execução
        for (int i = 0; i < instanceNumbers.size(); ++i) {
            stringstream execTimeStream;
            execTimeStream << fixed << setprecision(7) << executionTimes[i];  // Formata o tempo de execução com 7 casas decimais
            string execTimeStr = execTimeStream.str();
            replace(execTimeStr.begin(), execTimeStr.end(), '.', ',');  // Substitui o ponto decimal por vírgula (formato europeu)

            file << instanceNumbers[i] << ";" << evaluatedStates[i] << ";" << solutionSteps[i] << ";" << execTimeStr << "\n";
        }

        file.close();
    }


};