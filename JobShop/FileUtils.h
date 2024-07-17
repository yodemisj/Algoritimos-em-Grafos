#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

class FileUtils {
public:
    static void readFile(const string filePath, vector<unsigned>& times, vector<unsigned>& machines, int& nbJobs, int& nbMachines) {
        ifstream inputFile(filePath);
        string aux;

        if(!inputFile.is_open()) throw runtime_error("Erro ao abrir o arquivo!");

        inputFile>>nbJobs;
        inputFile>>nbMachines;

        inputFile>>aux;
        for (unsigned i = 0; i < nbJobs * nbMachines; i++) {
                unsigned num;
                inputFile>>num;
                times.push_back(num);
        }

        inputFile>>aux;
        for (unsigned i = 0; i < nbJobs * nbMachines; i++) {
                unsigned num;
                inputFile>>num;
                machines.push_back(num);
        }

    }

    static void generateCSV(const string& filePath, const vector<int>& indexes, const vector<int>& makeSpans, const vector<double>& executionTimes) {
        ofstream file(filePath);

        file << "Instance;makeSpan;Execution Time (s)\n";

        for (int i = 0; i < indexes.size(); ++i) {
            stringstream execTimeStream;
            execTimeStream << fixed << setprecision(7) << executionTimes[i];
            string execTimeStr = execTimeStream.str();
            replace(execTimeStr.begin(), execTimeStr.end(), '.', ',');
            file << indexes[i] << ";" << makeSpans[i] << ";" << execTimeStr << "\n";
        }

        file.close();
    }
};