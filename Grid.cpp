#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using std::vector;
 
int get_index(int i, int j, int size) {
    return i*size + j;
}

// Function used to create a square grid, given as an 1D vector
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

// Function used to convert index of 1D grid to 2D grid
int * get_index(int n, int size) {
	int i = n % size;
	int j = n / size;
	int * result = new int[2];
	result[0] = i;
	result[1] = j;
	return result;
}


// Function that gives us the first column of a given grid, and a given size of column
vector<double> first_column(vector<double> grid, int size) {
	vector<double> result(size, 0.);
	for (int i = 0; i < size; i++) {
		result[i] = grid[i];
	}
	return result;
}

// Function that gives us the last column of a given grid, and a given size of column
vector<double> last_column(vector<double> grid, int size) {
	vector<double> result(size, 0.);
	int n = grid.size();
	for (int i = 1; i <= size; i++) {
		result[size - i] = grid[n - i];
	}
	return result;
}

// double get_min(vector<double>> grid) {
// 	double min = grid[0][0];
// 	for (int i = 0; i < grid.size(); i++) {
// 		for (int j = 0; j < grid[0].size(); j++) {
// 			if (grid[i][j] < min) {
// 				min = grid[i][j];
// 			}
// 		}
// 	}
// 	return min;
// }
// double get_max(vector<vector<double>> grid) {
// 	double max = grid[0][0];
// 	for (int i = 0; i < grid.size(); i++) {
// 		for (int j = 0; j < grid[0].size(); j++) {
// 			if (grid[i][j] > max) {
// 				max = grid[i][j];
// 			}
// 		}
// 	}
// 	return max;
// }

// This function compute the n eme element of a 1D given grid, with a size given
double compute_element(int n, vector<double> grid, int size) {

	// I convert n index to 2D index
 	auto tmp = get_index(n, size);
 	int i = n % size;
 	int j = n / size;

	// I verify that we must compute the given value
 	// if (i == size - 1 || j == size - 1 || i == 0 || j == 0) {
 	//	return grid[n];
 	// }
	if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
		return grid[n];
	}

	// I applie the given function
	auto hx = 1./size;
	auto hy = 1./size;
	
	auto C = 1.;
	
	auto dt = 0.25*hx*hx/C;
	
	auto diagx = -2.0 + hx*hx/(2*C*dt);
	auto diagy = -2.0 + hy*hy/(2*C*dt);
	auto weightx = C*dt/(hx*hx);
	auto weighty = C*dt/(hy*hy);
	
	 return weightx*(grid[i-1 + j*size] + grid[i+1 + j * size] + grid[i + j*size] * diagx) + weighty*(grid[i + (j-1) * size] + grid[i + (j+1) * size] + grid[i + j * size]*diagy);
}
				

// This function print our 1D vector as a 2D vector for a given size
void print_grid(vector<double> grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
		int index = get_index(i, j, size);
            cout << grid[index] << " ";
        }
        cout << endl;
    }
}
