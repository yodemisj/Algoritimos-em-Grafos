#include <iostream>
#include <vector>
#include <cmath>
#include "graph.h"

using namespace std;

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

void findNeighbors(const vector<int>& puzzle, const int lineSize, vector<int>& neighbors) {
    int whiteSpaceIndex = searchEmptySpace(puzzle);
    if(whiteSpaceIndex < 0) return;

    int lineStartIndex = getlineStartIndex(whiteSpaceIndex, lineSize);
    int lineEndIndex = getRowByIndex(whiteSpaceIndex, lineSize) * lineSize - 1;

    // Up
    int currentIndex = whiteSpaceIndex - lineSize;
    if(!(currentIndex < 0)) neighbors.push_back(currentIndex);

    // Down
    currentIndex = whiteSpaceIndex + lineSize;
    if(!(currentIndex > (puzzle.size() - 1))) neighbors.push_back(currentIndex);

    // Left
    currentIndex = whiteSpaceIndex - 1;
    if(!(currentIndex < lineStartIndex)) neighbors.push_back(currentIndex);

    // Right
    currentIndex = whiteSpaceIndex + 1;
    if(!(currentIndex > lineEndIndex)) neighbors.push_back(currentIndex);

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

int calculateTotal(const vector<int>& puzzle, const int lineSize) {
    int total = 0;

    for(int i = 0; i < puzzle.size(); i++) {  
        if(puzzle[i] == 0) continue;
        total += calculateMovesToPosition(i, puzzle[i], lineSize);
    }
    return total;
}

int main() {
    vector<int> puzzle = {5, 6, 2, 7, 1, 8, 3, 4, 0};
    vector<int> neighbors;
    // 5 6 2
    // 7 1 8
    // 3 4 0


    cout << calculateTotal(puzzle, 3) << endl;

    return 0;
}