#include <iostream>

using namespace std;

struct Grid {
	double ** grid;
	int rows;
	int columns;
};

Grid create_grid(int rows, int columns) {
	Grid grid;
	grid.columns = columns;
	grid.rows = rows;
	grid.grid = new double * [rows];
	for (int i = 0; i < rows; i++) {
		grid.grid[i] = new double [columns];
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1) {
				grid.grid[i][j] = 0.0;
			}
			else if (j == 0 || j == columns - 1) {
				grid.grid[i][j] = 0.0;
			}
			else {
				grid.grid[i][j] = 1.0;
			}
		}
	}
	return grid;
}

void print_grid(Grid grid) {
		for (int i = 0; i < grid.rows; i++) {
			cout << endl;
		for (int j = 0; j < grid.columns; j++) {
			cout << grid.grid[i][j] << " ";	
		}
	}
	cout << endl;
}

/*
int calculate_evolution_in_time(void) {
				diagx = -2.0 + hx*hx/(2*C*dt);
				diagy = -2.0 + hy*hy/(2*C*dt);
				weightx = C*dt/(hx*hx);
				weighty = C*dt/(hy*hy);
				/* Perform an explicit update on the points within the domain.
				 * Optimization : inner loop on columns index (second index) since
				 * C++ is row major */
/*
				for (i=1;i<size_x;i++) {
								for (j=1;j<size_y;j++) {
												U[i][j] = weightx*(U0[i-1][j] + U0[i+1][j] + U0[i][j]*diagx) + weighty*(U0[i][j-1] + U0[i][j+1] + U0[i][j]*diagy);
								}
				}
}
*/
