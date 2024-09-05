#pragma once
#include "includes.h"

class Graph {
private: 
    map<vector<int>,vector<Board>> adj;
    vector<vector<int>> m;

public:

Graph(Board& board, int puzzleSize, int lineSize) {
    adj[board.first] = vector<Board>();
    initM(m, puzzleSize, lineSize);
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
    for(size_t i = 0; i < puzzle.size(); i++) {
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

    for(size_t i = 0; i < board.size(); i++) {  
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
        if(adj.count(copy.first) == 0) adj[copy.first] = vector<Board>();
        adj[board.first].push_back(copy);
    }
    // Down
    currentIndex = whiteSpaceIndex + lineSize;
    if(!(currentIndex > (board.first.size() - 1))){
        copy = board;
        copy.second = INT32_MAX;
        swap(copy.first[currentIndex], copy.first[whiteSpaceIndex]);
        if(adj.count(copy.first) == 0) adj[copy.first] = vector<Board>();
        adj[board.first].push_back(copy);
    } 

    // Left
    currentIndex = whiteSpaceIndex - 1;
    if(!(currentIndex < lineStartIndex)) {
        copy = board;
        copy.second = INT32_MAX;
        swap(copy.first[currentIndex], copy.first[whiteSpaceIndex]);
        if(adj.count(copy.first) == 0) adj[copy.first] = vector<Board>();
        adj[board.first].push_back(copy);
    } 

    // Right
    currentIndex = whiteSpaceIndex + 1;
    if(!(currentIndex > lineEndIndex)) {
        copy = board;
        copy.second = INT32_MAX;
        swap(copy.first[currentIndex], copy.first[whiteSpaceIndex]);
        if(adj.count(copy.first) == 0) adj[copy.first] = vector<Board>();
        adj[board.first].push_back(copy);
    } 
}

map<vector<int>, Board> a_star(Board start, Board goal, int lineSize) {
    auto compare = [](const Board& a, const Board& b) {
        // cout << a.second << " " << b.second << endl;
        // cout <<"a < b: "<< (a.second < b.second) << endl;
        return a.second > b.second;
    };
    map<vector<int>, int> dist;
    map<vector<int>, Board> pi;
    vector<Board> S;
    priority_queue<Board, vector<Board>, decltype(compare)> Q(compare);
    // priority_queue<pair<int, Board>> Q;
    dist[start.first] = 0;
    start.second = 0;
    Q.push(start);
    // Q.push(make_pair(start.second, start));

    int avaliatedStates = 0;

    while(!Q.empty()) {
        Board current = Q.top();
        // Board current = Q.top().second;
        Q.pop();
        S.push_back(current);
        avaliatedStates++;
        if (current.first == goal.first) {
            break;
        }

        addNeighbors(current,lineSize);

        for(Board& neighbor : adj[current.first]) {
            if(dist.count(neighbor.first) == 0) dist[neighbor.first] = INT32_MAX;

            if(dist[neighbor.first] > dist[current.first] + 1){
                dist[neighbor.first] = dist[current.first] + 1;
                neighbor.second = dist[neighbor.first] + heuristic(neighbor.first);
                pi[neighbor.first] = current;
                // Q.push(make_pair(-neighbor.second, neighbor));
                Q.push(neighbor);
            }
        }
    }

    cout << "Numero de estados avaliados: " << avaliatedStates << "\n";
    return pi;
}   

};