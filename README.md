# 🧩 Graph-Based Sudoku Solver

I have an obsession with Sudoku. I’ve been playing it for years, to the point where most puzzles don’t really challenge me anymore. Eventually, I got bored and started looking for something harder. That’s when I came across Arto Inkala’s Sudoku puzzles.

Arto Inkala is a Finnish mathematician known for constructing extremely difficult Sudoku puzzles. Some of his puzzles have been described as “the world’s hardest,” and they’re designed to challenge even experienced solvers. Naturally, I had to try one. And yeah… it completely destroyed me. Below is a display of why the puzzle is absolutely diabolical.


![Sudoku Solution](https://preview.redd.it/is-suposed-to-be-the-hardest-sudoku-ver-and-i-have-no-idea-v0-j54b1xunf2241.jpg?width=1080&crop=smart&auto=webp&s=0db0b5babfa526eb429825b299dcae5b6bb46348)

During one of my dissertation modules, I worked with graph colouring. After thinking about Sudoku long enough, I realised the rules are basically the same problem in disguise. In Sudoku, a number can’t repeat in a row, column, or box. In graph colouring, a vertex can’t share a colour with its neighbours. Same rule, different context.

So I decided to model Sudoku as a graph problem. That’s where this project came from.

Each cell is a **vertex**, and edges connect cells that share a row, column, or box. Each row, column, and box forms a **clique of size 9**, which means the chromatic number is 9 (which means we need 9 colours). Solving the puzzle becomes a graph colouring problem.


## 🧠 Core Idea

Instead of hardcoding Sudoku techniques, the solver enforces constraints:

- A cell cannot share a colour with its neighbours  
- Rows, columns, and boxes act as constraint groups (cliques)  
- A solution is simply a valid colouring of the graph  

This keeps the logic clean and general.

![Sudoku Solution](https://www.researchgate.net/profile/Ruben-Campoy/publication/311668725/figure/fig9/AS:439849451823105@1481879689246/b-Graph-coloring-of-Sudoku.png)

## 🏗️ Structure

The code is split into small, focused files:

- `load_board.cpp` → reads the puzzle  
- `neighbours.cpp` → builds the graph and computes palettes  
- `rules.cpp` → checks if constraints are violated  
- `propagation.cpp` → handles solving logic and recursion  
- `main.cpp` → runs everything  

Each file has one responsibility, which makes the code easier to read and debug.


## 🔢 Data Representation

The board is stored as a flat array of size 81. It’s simple and efficient.

The graph is stored as an **adjacency list**. Each cell has exactly 20 neighbours, so the graph is sparse. Using a matrix would waste space (`O(n²)`), while an adjacency list is compact and faster for iteration.

Each cell also has a **palette**, which stores the colours (numbers) that are still allowed.


## 🎨 Palettes (Candidates)

For each cell, we compute its palette by:

1. Looking at all neighbouring cells  
2. Marking which colours are already used  
3. Keeping the remaining valid colours  

This is the foundation of the solver.


## 🚨 Rule Checking

The solver constantly checks if the board is still valid.

Each row, column, and box is treated as a unit. If any unit contains duplicate values, the board is invalid and that branch is abandoned.


## 🔁 Propagation

Before guessing, the solver applies **constraint propagation**.

If a cell has only one possible colour, it must take that value.  
This process repeats until no more forced moves exist. This reduces the search space significantly.


## 🌳 Search (Backtracking)

If propagation is not enough, the solver uses recursion.

It selects the cell with the smallest palette (most constrained), then:

- tries each possible colour  
- propagates constraints  
- continues recursively  

If a contradiction occurs, it backtracks and tries another option.


## 🧠 Conclusion

This is essentially a **Constraint Satisfaction Problem (CSP)** solver.

Rather than relying on specific Sudoku tricks, it enforces rules and explores possibilities systematically. It’s closer to how a human approaches very difficult puzzles: try something logical, follow it through, and backtrack if it breaks.

The difference is that this does it much faster and without getting tired.

This approach worked well even on Inkala’s puzzle, which doesn’t give many easy reductions early on. Most cells start with large palettes, so the solver relies heavily on choosing the most constrained cell and exploring carefully. 

I’ve also tested the solver using puzzles from the [GrantM Sudoku Puzzle Bank](https://github.com/grantm/sudoku-exchange-puzzle-bank/blob/master/diabolical.txt). From what I’ve seen, it handles puzzles rated 9.0+ (diabolical difficulty) without issues.

The solver is designed for puzzles with a **single valid solution**, which is typical for well-constructed Sudoku. While it will run on any valid grid, it will only return one solution, even if multiple solutions exist.


**P.S.** If you're wondering, here’s the solution to Arto Inkala's diabolical Sudoku puzzle:

```text
8 1 2 | 7 5 3 | 6 4 9
9 4 3 | 6 8 2 | 1 7 5
6 7 5 | 4 9 1 | 2 8 3
------+-------+------
1 5 4 | 2 3 7 | 8 9 6
3 6 9 | 8 4 5 | 7 2 1
2 8 7 | 1 6 9 | 5 3 4
------+-------+------
5 2 1 | 9 7 4 | 3 6 8
4 3 8 | 5 2 6 | 9 1 7
7 9 6 | 3 1 8 | 4 5 2
