#include <iostream>
//#include "Grid.h"
#include "write.h"


using namespace std;

 
std::vector<std::vector<double>> create_grid(int x, int y) {
    rows = x;
    columns = y;
    grid_1.resize(rows);
    grid_2.resize(rows);
    grid_line.resize(rows * columns);
    for (int i = 0; i < rows; i++) {
        grid_1[i].resize(columns);
        grid_2[i].resize(rows);
        for (int j = 0; j < columns; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
                grid_1[i][j] = 1.;
                grid_2[i][j] = 1.;
		grid_line[get_index(i, j)] = 1.;
            }
            else {
                grid_1[i][j] = 0.;
                grid_2[i][j] = 0.;
		grid_line[get_index(i, j)] = 0.;
            }
        }
    }
}

int Grid::get_index(int i, int j) {
    return i*columns + j;
}

int * Grid::get_index(int n) {
    int j = n % columns;
    int i = (n - j - 1) % rows;
    int * result = new int[2];
    result[0] = i;
    result[1] = j;
    return result;
}

double Grid::get_min() {
    double min = grid_1[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (grid_1[i][j] < min) {
                min = grid_1[i][j];
            }
        }
    }
    return min;
}

double Grid::get_max() {
    double max = grid_1[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (grid_1[i][j] > max) {
                max = grid_1[i][j];
            }
        }
    }
    return max;
}

void Grid::next_step() {
    double hx = 1./rows;
    double hy = 1./columns;
    double C = 1.e-6;
    double dt = 1.;
    
    double diagx = -2.0 + hx*hx/(2*C*dt);
	double diagy = -2.0 + hy*hy/(2*C*dt);
    double weightx = C*dt/(hx*hx);
    double weighty = C*dt/(hy*hy);
	/* Perform an explicit update on the points within the domain.
	* Optimization : inner loop on columns index (second index) since
	* C++ is row major */
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < columns - 1; j++) {
            grid_2[i][j] = weightx*(grid_1[i-1][j] + grid_1[i+1][j] + grid_1[i][j]*diagx) + weighty*(grid_1[i][j-1] + grid_1[i][j+1] + grid_1[i][j]*diagy);
		}
    }
    swap(grid_2, grid_1);
}

double Grid::calculate_element(int n) {
	auto tmp = get_index(n);
	int i = tmp[0];
	int j = tmp[1];
	if (i == rows || j == columns) {
		return 1.;
	}
   	double hx = 1./rows;
    	double hy = 1./columns;
    	double C = 1.e-6;
    	double dt = 1.;
    	double diagx = -2.0 + hx*hx/(2*C*dt);
	double diagy = -2.0 + hy*hy/(2*C*dt);
   	double weightx = C*dt/(hx*hx);
    	double weighty = C*dt/(hy*hy);
	return weightx*(grid_1[i-1][j] + grid_1[i+1][j] + grid_1[i][j]*diagx) + weighty*(grid_1[i][j-1] + grid_1[i][j+1] + grid_1[i][j]*diagy);
}

void Grid::state_grid_after_time(int time) {
    for (int i = 0; i < time; i++) {
        next_step();
    }
}


void Grid::print_grid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << grid_1[i][j] << " ";
        }
        cout << endl;
    }
}

void Grid::print_line_grid() {
	for (int i = 0; i < rows * columns; i++) {
		cout << grid_line[i] << " ";
	}
	cout << endl;
}
