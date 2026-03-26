#include "sudoku.h"

namespace sudoku {

/**
 * Counts how many colours are in a palette.
 * Empty slots are stored as 0.
 */
static int palette_size(const array<int, N>& palette) {
    int count = 0;

    for (int colour : palette) {
        if (colour != 0) {
            count++;
        }
    }

    return count;
}


static bool palettes_are_valid(const Board& board, const Palettes& palettes) {
    for (int u = 0; u < V; ++u) {
        if (board[u] == 0 && palette_size(palettes[u]) == 0) {
            return false; //Returns false if any empty vertex has no legal colours left.
        }
    }

    return true;
}


bool propagate_singles(Board& board, const NeighbourTable& adj) { //Fills every vertex whose palette contains exactly one colour.
    while (true) {
        if (board_has_duplicate(board)) {
            return false;
        }

        Palettes palettes = compute_all_palettes(board, adj);
        if (!palettes_are_valid(board, palettes)) {
            return false;
        }

        bool changed = false;

        for (int u = 0; u < V; ++u) {
            if (board[u] == 0 && palette_size(palettes[u]) == 1) {
                board[u] = palettes[u][0];
                changed = true;
            }
        }

        if (!changed) {
            return true;
        }
    }
}


static int choose_branch_vertex(const Board& board, const Palettes& palettes) { //Finds the unsolved vertex with the smallest palette of size 2 or more.
    int chosen = -1;
    int best_size = MAX_PALETTE_SIZE;

    for (int u = 0; u < V; ++u) {
        if (board[u] != 0) {
            continue;
        }

        int size = palette_size(palettes[u]);

        if (size >= MIN_BRANCH_SIZE && size < best_size) {
            best_size = size;
            chosen = u;
        }
    }

    return chosen; //Returns -1 if no such vertex exists.
}


static bool try_colour(Board& board, //Tries one colour at one vertex and continues solving recursively.
                    const NeighbourTable& adj,
                    int u,
                    int colour) {
    Board next_board = board;
    next_board[u] = colour;

    if (solve_branch(next_board, adj)) {
        board = next_board;
        return true;
    }

    return false;
}


bool solve_branch(Board& board, const NeighbourTable& adj) {
    if (!propagate_singles(board, adj)) {
        return false;
    }

    if (board_is_solved(board)) {
        return true;
    }

    Palettes palettes = compute_all_palettes(board, adj);
    if (!palettes_are_valid(board, palettes)) {
        return false;
    }

    int u = choose_branch_vertex(board, palettes);
    if (u == -1) {
        return false;
    }

    for (int colour : palettes[u]) {
        if (colour != 0 && try_colour(board, adj, u, colour)) {
            return true;
        }
    }

    return false;
}


bool apply_propagation(Board& board, const NeighbourTable& adj) {
    Board before = board;

    if (!solve_branch(board, adj)) {
        return false;
    }

    return board != before;
}

} 