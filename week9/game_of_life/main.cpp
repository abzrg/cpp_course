//===----------------------------------------------------------------------===//
//
// Ali Bozorgzadeh
//
//   <aliiiib95@gmail.com>
//
// Description
//   A two dimensional cellular automaton, Game of life, written in C++.
//
//   A cell in the grid can have two states:
//    - 1(alive),
//    - 0(deade)
//
//   The rules are as follows:
//    1) A dead cell becomes alive if exactly 3 of its adjacent cells are
//    alive (as if by reproduction)
//    2) A living cell dies if fewer than 2 (as if by underpopulation) or
//    more than 3 (as if by overpopulation) of its adjacent cell are alive
//    3) In any other cases, the state of the cell remains the same
//
//===----------------------------------------------------------------------===//

#include "gol.h"

int main() {
    Grid grid;
    // Read the seed file
    try {
        grid = read_grid("initial_grid.txt");
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    // Write results
    try {
        write_grid("out_grid.txt", game_of_life(grid, 10));
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
