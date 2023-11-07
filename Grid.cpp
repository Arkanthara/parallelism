#include <iostream>
//#include "Grid.h"
#include <vector>
#include <cmath>

using namespace std;
using std::vector;
 
int get_index(int i, int j, int size) {
    return i*size + j;
}
vector<double> create_grid(int size) {
	vector<double> grid(size*size, 0.);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
				int index = get_index(i, j, size);
				grid[index] = 1.;
			}
		}
	}
	return grid;
}


int * get_index(int n, int size) {
	int j = n % size;
	int i = (n - j - 1) % size;
	int * result = new int[2];
	result[0] = i;
	result[1] = j;
	return result;
}

double get_min(vector<vector<double>> grid) {
	double min = grid[0][0];
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] < min) {
				min = grid[i][j];
			}
		}
	}
	return min;
}
double get_max(vector<vector<double>> grid) {
	double max = grid[0][0];
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] > max) {
				max = grid[i][j];
			}
		}
	}
	return max;
}

// void next_step() {
//     double hx = 1./rows;
//     double hy = 1./columns;
//     double C = 1.e-6;
//     double dt = 1.;
//     
//     double diagx = -2.0 + hx*hx/(2*C*dt);
// 	double diagy = -2.0 + hy*hy/(2*C*dt);
//     double weightx = C*dt/(hx*hx);
//     double weighty = C*dt/(hy*hy);
// 	/* Perform an explicit update on the points within the domain.
// 	* Optimization : inner loop on columns index (second index) since
// 	* C++ is row major */
//     for (int i = 1; i < rows - 1; i++) {
//         for (int j = 1; j < columns - 1; j++) {
//             grid_2[i][j] = weightx*(grid_1[i-1][j] + grid_1[i+1][j] + grid_1[i][j]*diagx) + weighty*(grid_1[i][j-1] + grid_1[i][j+1] + grid_1[i][j]*diagy);
// 		}
//     }
//     swap(grid_2, grid_1);
// }

double compute_element(int n, vector<double> grid, int size) {
 	auto tmp = get_index(n, size);
 	int i = tmp[0];
 	int j = tmp[1];
 	if (i == size - 1 || j == size - 1 || i == 0 || j == 0) {
 		return 1.;
 	}
    	double hx = 1./size;
     	double hy = 1./size;
     	double C = 1.e-6;
     	double dt = 1.;
     	double diagx = -2.0 + hx*hx/(2*C*dt);
 	double diagy = -2.0 + hy*hy/(2*C*dt);
    	double weightx = C*dt/(hx*hx);
     	double weighty = C*dt/(hy*hy);
 	return weightx*(grid[get_index(i-1, j, size)] + grid[get_index(i+1, j, size)] + grid[get_index(i, j*diagx, size)]) + weighty*(grid[get_index(i, j-1, size)] + grid[get_index(i, j+1, size)] + grid[get_index(i, j*diagy, size)]);
}
				


void print_grid(vector<double> grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
		int index = get_index(i, j, size);
            cout << grid[index] << " ";
        }
        cout << endl;
    }
}

void print_line_grid(vector<double> grid) {
	for (int i = 0; i < grid.size(); i++) {
		cout << grid[i] << " ";
	}
	cout << endl;
}
