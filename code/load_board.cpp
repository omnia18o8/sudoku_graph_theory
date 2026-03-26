#include "sudoku.h"

namespace sudoku {
    
/**
 * Loads a Sudoku board from a txt file.
 * The file is expected to contain 81 integers (0–9), where 0 represents an empty cell.
 * Values are read row by row into a flat array.
 */

Board load_board(const string& path) {
    ifstream in(path);

    Board board{};

    for (int i = 0; i < V; ++i) {
        int value;
        in >> value;
        board[i] = value;
    }

    return board;
}

}