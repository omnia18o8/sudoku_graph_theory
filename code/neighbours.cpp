#include "sudoku.h"

namespace sudoku {
/**
 * The following organises the cells/vertices into an adjacency representation,
 * to figure out the neighbours and the numbers/colours allowed in each vertices palette.
 */

static void add_edge(int v, 
                    bool visited[], 
                    int adj_list[], 
                    int& degree) {
    // Adds a vertex to adjacency list if not already present (ensures each edge is stored once).
    if (!visited[v]) {
        adj_list[degree] = v;
        degree++;
        visited[v] = true;
    }
}

/**
 * Builds adjacency list for Sudoku graph.
 * Why adjacency list and not matrix?
 * - Edge exists if two cells share row, column, or box
 * - Thus vertex has ~20 neighbours (sparse graph)
 * - Faster iteration than full adjacency matrix (81x81), although a matrix would allow for faster access
 */
NeighbourTable build_adjacency_list() {
    NeighbourTable adj{};

    for (int u = 0; u < V; ++u) {
        bool visited[V] = {false};
        int degree = 0;

        int row = u / N;
        int col = u % N;

        visited[u] = true;

        // row edges
        for (int c = 0; c < N; ++c) {
            int v = row * N + c;
            add_edge(v, visited, adj[u].data(), degree);
        }

        // column edges
        for (int r = 0; r < N; ++r) {
            int v = r * N + col;
            add_edge(v, visited, adj[u].data(), degree);
        }

        // box edges
        int br = (row / BOX) * BOX;
        int bc = (col / BOX) * BOX;

        for (int r = br; r < br + BOX; ++r) {
            for (int c = bc; c < bc + BOX; ++c) {
                int v = r * N + c;
                add_edge(v, visited, adj[u].data(), degree);
            }
        }
    }

    return adj;
}
} 