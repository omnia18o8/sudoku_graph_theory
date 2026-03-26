#include "sudoku.h"

namespace sudoku {

/**
 * The following ensures that a vertex has no colours in common with its neighbours 
 * (i.e. cells in the same row, column and in the same box)
 */
static bool unit_has_duplicate(const Board& board, const int unit[N]) {
    bool seen[N + 1] = {false}; // index 1..9

    for (int i = 0; i < N; ++i) {
        int colour = board[unit[i]];

        if (colour == 0) {
            continue; // ignore empty vertices
        }

        if (seen[colour]) {
            return true; // same colour appears twice → invalid
        }

        seen[colour] = true;
    }

    return false;
}


bool board_has_duplicate(const Board& board) {

    // check all row units
    for (int row = 0; row < N; ++row) {
        int unit[N];

        for (int col = 0; col < N; ++col) {
            unit[col] = row * N + col;
        }

        if (unit_has_duplicate(board, unit)) {
            return true;
        }
    }

    // check all column units
    for (int col = 0; col < N; ++col) {
        int unit[N];

        for (int row = 0; row < N; ++row) {
            unit[row] = row * N + col;
        }

        if (unit_has_duplicate(board, unit)) {
            return true;
        }
    }

    // check all box units
    for (int box_row = 0; box_row < BOX; ++box_row) {
        for (int box_col = 0; box_col < BOX; ++box_col) {
            int unit[N];
            int k = 0;

            for (int row = box_row * BOX; row < box_row * BOX + BOX; ++row) {
                for (int col = box_col * BOX; col < box_col * BOX + BOX; ++col) {
                    unit[k++] = row * N + col;
                }
            }

            if (unit_has_duplicate(board, unit)) {
                return true;
            }
        }
    }

    return false;
}

/**
 * A board is solved if:
 * - all vertices are assigned a colour
 * - no constraints are violated
 */
bool board_is_solved(const Board& board) {
    for (int u = 0; u < V; ++u) {
        if (board[u] == 0) {
            return false; // unassigned vertex
        }
    }

    return !board_has_duplicate(board);
}

} 