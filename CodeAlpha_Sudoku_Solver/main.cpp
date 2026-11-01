// Task 3: Sudoku Solver using a 2D array and recursive backtracking.
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
const int SIZE = 9;

bool canPlace(const int grid[SIZE][SIZE], int row, int col, int number) {
    for (int i = 0; i < SIZE; ++i)
        if (grid[row][i] == number || grid[i][col] == number) return false;
    int startRow = row / 3 * 3, startCol = col / 3 * 3;
    for (int r = startRow; r < startRow + 3; ++r)
        for (int c = startCol; c < startCol + 3; ++c)
            if (grid[r][c] == number) return false;
    return true;
}
bool validClues(int grid[SIZE][SIZE]) {
    for (int r = 0; r < SIZE; ++r)
        for (int c = 0; c < SIZE; ++c) {
            int number = grid[r][c];
            if (number == 0) continue;
            grid[r][c] = 0;
            bool valid = canPlace(grid, r, c, number);
            grid[r][c] = number;
            if (!valid) return false;
        }
    return true;
}
bool solve(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; ++row)
        for (int col = 0; col < SIZE; ++col) {
            if (grid[row][col] != 0) continue;
            for (int number = 1; number <= 9; ++number) {
                if (!canPlace(grid, row, col, number)) continue;
                grid[row][col] = number;
                if (solve(grid)) return true;
                grid[row][col] = 0; // Undo this guess and try the next number.
            }
            return false;
        }
    return true;
}
void printGrid(const int grid[SIZE][SIZE]) {
    for (int r = 0; r < SIZE; ++r) {
        if (r % 3 == 0) cout << "+-------+-------+-------+\n";
        for (int c = 0; c < SIZE; ++c) {
            if (c % 3 == 0) cout << "| ";
            cout << grid[r][c] << ' ';
        }
        cout << "|\n";
    }
    cout << "+-------+-------+-------+\n";
}
int main() {
    int grid[SIZE][SIZE] = {};
    cout << "SUDOKU SOLVER\nEnter 9 rows, each containing 9 integers (0 means empty).\n";
    for (int r = 0; r < SIZE; ++r) {
        while (true) {
            cout << "Row " << r + 1 << ": ";
            string line;
            if (!getline(cin, line)) { cerr << "Input ended.\n"; return 1; }
            istringstream input(line);
            bool valid = true;
            for (int c = 0; c < SIZE; ++c)
                if (!(input >> grid[r][c]) || grid[r][c] < 0 || grid[r][c] > 9) { valid = false; break; }
            if (valid && (input >> ws).eof()) break;
            cout << "Invalid row. Enter exactly 9 integers from 0 to 9.\n";
        }
    }
    if (!validClues(grid)) { cout << "Invalid puzzle: clues break Sudoku rules.\n"; return 1; }
    if (solve(grid)) { cout << "\nSOLUTION\n"; printGrid(grid); }
    else { cout << "No solution exists for this puzzle.\n"; return 1; }
}
