#ifndef __GRID_H__
#define __GRID_H__

#include <vector>

using namespace std;
using std::vector;
vector<double> create_grid(int size);

void print_grid(vector<double> grid, int size);

double compute_element(int n, vector<double> grid, int size);
#endif
