#pragma once

#include <array>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

const int N = 9;            // number of nodes per row/col
const int V = 81;           // 9 * 9 total vertices
const int BOX = 3;          // box size
const int MIN_BRANCH_SIZE = 2;
const int MAX_PALETTE_SIZE = 10;

namespace sudoku {

using Board = array<int, 81>;
using NeighbourTable = array<array<int, 20>, 81>;
using Palettes = array<array<int, 9>, 81>;

Board load_board(const string& path);

NeighbourTable build_adjacency_list();
array<int, 9> compute_palette(const Board&, const NeighbourTable&, int);
Palettes compute_all_palettes(const Board& board, const NeighbourTable& adj);

bool board_has_duplicate(const Board& board);
bool board_is_solved(const Board& board);

bool propagate_singles(Board& board, const NeighbourTable& adj);
bool solve_branch(Board& board, const NeighbourTable& adj);
bool apply_propagation(Board& board, const NeighbourTable& adj);
} // namespace sudoku