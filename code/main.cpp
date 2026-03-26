#include "sudoku.h"

using namespace sudoku;

static void print_board(const Board& board) {
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            int v = board[r * 9 + c];
            cout << (v == 0 ? ". " : to_string(v) + " ");

            if ((c + 1) % 3 == 0 && c < 8) {
                cout << "| ";
            }
        }

        cout << "\n";

        if ((r + 1) % 3 == 0 && r < 8) {
            cout << "------+-------+------\n";
        }
    }
}

int main() {
    Board board = load_board("../arto_inkala.txt");
    NeighbourTable adj = build_adjacency_list();

    if (!board_has_duplicate(board)) {
        apply_propagation(board, adj);
    }

    print_board(board);
    return 0;
}