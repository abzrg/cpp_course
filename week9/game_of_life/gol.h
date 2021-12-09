#ifndef GOL_H
#define GOL_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

// Macros to set the size of the grid
// size of the initial seed: 26x51
#define GRID_ROW 26
#define GRID_COL 51

// -- Make my life easier
using Grid = std::vector<std::vector<bool>>;

// -- Forward declarations
Grid read_grid(const std::string &filename);
void print_grid(const Grid &g);
Grid game_of_life(const Grid &grid, const size_t N);
void write_grid(const std::string &filename, const Grid &grid);

#endif // GOL_H
