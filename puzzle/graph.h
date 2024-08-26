#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

typedef pair<vector<int>, int> Board;
// typedef vector<int> Board;

class Graph {
private: 
    map<Board,vector<Board>> adj;
    vector<vector<int>> m;

public:

Graph(Board& board, int puzzleSize, int linesize) {
    adj[board] = vector<Board>();
    initM(m, 9, 3);
}

void initM(vector<vector<int>>& m, int puzzleSize, int lineSize) {
    m = vector<vector<int>>(puzzleSize, vector<int>(puzzleSize,0));
    for(int i = 1; i < puzzleSize; i++) {
        for(int j = 0; j < puzzleSize; j++) {
            m[i][j] = calculateMovesToPosition(i, j, lineSize);
        }
    }
}

int searchEmptySpace (const vector<int>& puzzle) {
    for(int i = 0; i < puzzle.size(); i++) {
        if(puzzle[i] == 0) return i;
    }

    return -1;
}

int getRowByIndex(const int index, const int lineSize) {
    return ceil((index + 1.0) / lineSize);
}

int getlineStartIndex(const int index, const int lineSize) {
    return (getRowByIndex(index, lineSize) - 1)  * lineSize;
}

int getColumnByIndex(const int index, const int lineSize) {
    return index - getlineStartIndex(index, lineSize);
}

int calculateMovesToPosition(const int position, const int destination, const int lineSize) {
    int currentLine = getRowByIndex(position, lineSize);
    int destinationLine = getRowByIndex(destination, lineSize);
    int verticalDistance = abs(currentLine - destinationLine);
    int currentColumn = getColumnByIndex(position, lineSize);
    int destinationColumn = getColumnByIndex(destination, lineSize);
    int horizontalDistance = abs(currentColumn - destinationColumn);

    return verticalDistance + horizontalDistance;
    
}

int heuristic(const vector<int>& board) {
    int total = 0;

    for(int i = 0; i < board.size(); i++) {  
        if(board[i] == 0) continue;
        total += m[board[i]][i];
    }
    return total;
}

void addNeighbors(const Board& board, const int lineSize) {
    int whiteSpaceIndex = searchEmptySpace(board.first);
    if(whiteSpaceIndex < 0) return;

    int lineStartIndex = getlineStartIndex(whiteSpaceIndex, lineSize);
    int lineEndIndex = getRowByIndex(whiteSpaceIndex, lineSize) * lineSize - 1;
    Board copy;

    // Up
    int currentIndex = whiteSpaceIndex - lineSize;
    if(!(currentIndex < 0)) {
        copy = board;
        copy.second = INT32_MAX;
        swap(copy.first[currentIndex], copy.first[whiteSpaceIndex]);
        if(adj.count(copy) == 0) adj[copy] = vector<Board>();
        adj[board].push_back(copy);
    }
    // Down
    currentIndex = whiteSpaceIndex + lineSize;
    if(!(currentIndex > (board.first.size() - 1))){
        copy = board;
        copy.second = INT32_MAX;
        swap(copy.first[currentIndex], copy.first[whiteSpaceIndex]);
        if(adj.count(copy) == 0) adj[copy] = vector<Board>();
        adj[board].push_back(copy);
    } 

    // Left
    currentIndex = whiteSpaceIndex - 1;
    if(!(currentIndex < lineStartIndex)) {
        copy = board;
        copy.second = INT32_MAX;
        swap(copy.first[currentIndex], copy.first[whiteSpaceIndex]);
        if(adj.count(copy) == 0) adj[copy] = vector<Board>();
        adj[board].push_back(copy);
    } 

    // Right
    currentIndex = whiteSpaceIndex + 1;
    if(!(currentIndex > lineEndIndex)) {
        copy = board;
        copy.second = INT32_MAX;
        swap(copy.first[currentIndex], copy.first[whiteSpaceIndex]);
        if(adj.count(copy) == 0) adj[copy] = vector<Board>();
        adj[board].push_back(copy);
    } 
}

void a_star(Board start, Board goal, int lineSize, bool stepByStep) {
    auto compare = [](const Board& a, const Board& b) {
        return a.second > b.second;
    };
    map<Board, int> dist;
    map<Board, Board> pi;
    vector<Board> S;
    priority_queue<Board, vector<Board>, decltype(compare)> Q(compare);
    dist[start] = 0;
    start.second = 0;
    Q.push(start);

    // int i = 0;
    while(!Q.empty()) {
        Board current = Q.top();
        Q.pop();
        S.push_back(current);
        // cout<<i++<<endl;

        // for(auto number : current.first) {
        //     cout << number << " ";
        // }
        // cout<<endl;
        // if(current.first == goal.first) {
        //     cout<<"achou"<<endl;
            
        //     break;
        // }

        // if (stepByStep) { 
        //     for (auto number : current.first) {
        //         cout << number << " ";
        //     }
        //     cout << endl;
        // }

        if (current.first == goal.first) {
            cout << "Solução encontrada!" << endl;
            // Exibir a sequência de passos se stepByStep for false
            if (!stepByStep) {
                vector<Board> path;
                for (Board at = current; at != start; at = pi[at]) {
                    path.push_back(at);
                }
                path.push_back(start);
                reverse(path.begin(), path.end());

                for (const auto& state : path) {
                    for (int num : state.first) {
                        cout << num << " ";
                    }
                    cout << endl;
                }
            }
            break;
        }


        addNeighbors(current,lineSize);

        for(Board& neighbor : adj[current]) {
            if(dist.count(neighbor) == 0) dist[neighbor] = INT32_MAX;

            if(dist[neighbor] > dist[current] + 1){
                dist[neighbor] = dist[current] + 1;
                neighbor.second = dist[neighbor] + heuristic(neighbor.first);
                pi[neighbor] = current;
                Q.push(neighbor);
            }
        }
    }
}   

};