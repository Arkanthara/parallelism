#include <iostream>
#include <vector>


using namespace std;
using std::vector;

vector<double> convert_to_1D(vector<vector<double>> grid, int size) {
	vector<double> grid_line(size * size, 0.);
	for (int i = 0; i < size; i ++) {
		for (int j = 0; j < size; j ++) {
			grid_line[i*size + j] = grid[i][j];
		}
	}
	return grid_line;
}

vector<vector<double>> convert_to_2D(vector<double> grid_line, vector<vector<double>> grid, int size) {
	int n = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			grid[i][j] = grid_line[n];
			n++;
		}
	}
	return grid;
}

vector<vector<double>> put_into_2D(vector<vector<double>> grid, vector<double> grid_line, int nb_columns, int rank, int size) {
	int n = 0;
	for (int i = rank*nb_columns; i < rank*nb_columns +  nb_columns; i++) {
		for (int j = 0; j < size; j++) {
			grid[i][j] = grid_line[n];
			n++;
		}
	}
	return grid;
}


void print_grid(vector<vector<double>> grid, int size) {
	for (int i = 0; i < size; i ++) {
		for (int j = 0; j < size; j ++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
}

vector<vector<double>> create_grid(int size) {
	vector<vector<double>> grid;
	grid.resize(size);
	for (int i = 0; i < size; i ++) {
		grid[i].resize(size);
		for (int j = 0; j < size; j ++) {
			if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
				grid[i][j] = 1.;
			else grid[i][j] = 0.;
		}
	}
	return grid;
}


