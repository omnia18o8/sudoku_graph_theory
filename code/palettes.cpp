#include "sudoku.h"

namespace sudoku {
/**
 * The first function finds all the possible colours allowed for a vertex. 
 * While the second computes palettes for all vertices.
 */

array<int, N> compute_palette(const Board& board,
                            const NeighbourTable& adj,
                            int u) {
    array<int, N> palette{};
    bool used[N + 1] = {false};
    int k = 0;

    if (board[u] != 0) { //if vertex has already been assigned a fix colour ->return
        palette[0] = board[u];
        return palette;
    }

    for (int v : adj[u]) { // mark colours already used by neighbouring vertices 
        int colour = board[v];
        if (colour != 0) used[colour] = true; //colour cannot be used 
        
    }

    for (int colour = 1; colour <= N; ++colour) { // collect all colours not used for a valid palette for u
        if (!used[colour]) palette[k++] = colour;
    
    }

    return palette;
}


Palettes compute_all_palettes(const Board& board, const NeighbourTable& adj) {
    Palettes palettes{};

    for (int u = 0; u < V; ++u) palettes[u] = compute_palette(board, adj, u);
    return palettes;
}
}