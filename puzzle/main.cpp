#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    vector<vector<int>> m(9, vector<int>(9,0));
    vector<int> board = {5, 6, 2, 7, 1, 8, 3, 4, 0};
    vector<int> goal = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> start = {1, 0, 2, 3, 4, 5, 6, 7, 8};
    Board b1 = {board,INT32_MAX};
    Board b2 = {goal,INT32_MAX};
    Graph graph(b1, 9, 3);

    graph.a_star(b1, b2,3);

    return 0;
}