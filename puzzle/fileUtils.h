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
};