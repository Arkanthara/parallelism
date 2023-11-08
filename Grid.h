#ifndef __GRID_H__
#define __GRID_H__

#include <vector>

using namespace std;
using std::vector;

// Allow us to create a grid
vector<double> create_grid(int size);

// Print our 1D vector as if it was a 2D vector with shape size * size
void print_grid(vector<double> grid, int size);

// Applies heat equation on the n eme element of our grid...
// We indicate to fhe function that the size of our imaginary 2D grid is size, so we can
// access to elements in our grid like if the grid was a 2D grid
double compute_element(int n, vector<double> grid, int size);

// Return the first column of a vector given, which represent part of grid with shape size*size
vector<double> first_column(vector<double> grid, int size);
// Return the last column of a vector given, which represent part of grid with shape size*size
vector<double> last_column(vector<double> grid, int size);
#endif
