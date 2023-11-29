#ifndef __GRID_H__
#define __GRID_H__

#include <vector>


using namespace std;
using std::vector;



vector<double> convert_to_1D(vector<vector<double>> grid, int size);


vector<vector<double>> convert_to_2D(vector<double> grid_line, vector<vector<double>> grid, int size);


vector<vector<double>> put_into_2D(vector<vector<double>> grid, vector<double> grid_line, int nb_columns, int rank, int size);


void print_grid(vector<vector<double>> grid, int size);


vector<vector<double>> create_grid(int size);

#endif
