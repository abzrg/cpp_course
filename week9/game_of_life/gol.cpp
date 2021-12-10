#include "gol.h"

// Reads A Grid (normally an initial seed) from file
Grid read_grid(const std::string &filename) {
    // Create an empty grid
    // TODO: find a way to not hard code No. of rows and No. of columns
    Grid grid(GRID_ROW, std::vector<bool>(GRID_COL, 0));

    // Open the seed file
    std::ifstream ifs;
    ifs.open(filename);

    // Check if you could open the file
    if (!ifs) throw std::runtime_error("Could not open the file.");

    // Fill the grid with initial grid
    int row = 0;
    for (std::string line; std::getline(ifs, line);) {
        int column = 0;
        for (char &c : line) {
            // Get the numerical value of the character
            // implicit cast: char -> bool
            grid[row][column] = c - '0';
            ++column;
        }
        ++row;
    }

    ifs.close();

    return grid;
}

// Prints the grid
void print_grid(const Grid &grid) {
    for (const auto &row : grid) {
        for (const auto &cell : row) std::cout << cell;
        std::cout << '\n';
    }
}

// Computes the Nth generation, supplying seed grid
Grid game_of_life(const Grid &grid, const size_t N) {
    Grid current = grid;
    Grid successor = grid;

    // These are used later on to check identifying cells at the corner
    size_t nRows = grid.size();
    size_t nCols = grid[0].size();

    // N generation of simulations
    for (size_t nGenerations = 0; nGenerations < N; ++nGenerations) {
        // loop over current cells (Ignore corner cells)
        for (size_t row = 1; row < nRows - 1; ++row) {
            for (size_t col = 1; col < nCols - 1; ++col) {
                // Count the neighbors
                size_t living_neighbors = 0;
                living_neighbors +=
                    current[row - 1][col + 1] + current[row][col + 1] +
                    current[row + 1][col + 1] + current[row - 1][col] + 0 +
                    current[row + 1][col] + current[row - 1][col - 1] +
                    current[row][col - 1] + current[row + 1][col - 1];

                if (current[row][col] == false) {  // If already dead
                    successor[row][col] = living_neighbors == 3;  // [1]
                } else {  // If already alive
                    successor[row][col] =
                        living_neighbors == 2 || living_neighbors == 3;  // [1]
                }
            }
        }

        // Consider successor as the current in the next generation
        current.swap(successor);
    }

    return successor;
}

// Writes a Grid to file
void write_grid(const std::string &filename, const Grid &grid) {
    std::ofstream ofs;
    ofs.open(filename);

    // Check if you could open the file
    if (!ofs) throw std::runtime_error("Could not open the file.");

    for (const auto &row : grid) {
        for (const auto &col : row) ofs << col;
        ofs << '\n';
    }

    ofs.close();
}

// References:
// [1]: The idea of this simplification comes from this video:
//      <https://www.youtube.com/watch?v=E7CxMHsYzSs>
