#include <iostream>
#include "Grid.h"
#include "write.h"


using namespace std;

 
Grid::Grid(int x, int y) {
    rows = x;
    columns = y;
    grid = new double * [rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new double [columns];
        for (int j = 0; j < columns; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
                grid[i][j] = 1.0;
            }
            else {
                grid[i][j] = 0.0;
            }
        }
    }
}

int Grid::get_rows() {
    return rows;
}

int Grid::get_columns() {
    return columns;
}

double Grid::get_min() {
    double min = grid[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (grid[i][j] < min) {
                min = grid[i][j];
            }
        }
    }
    return min;
}

double Grid::get_max() {
    double max = grid[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (grid[i][j] > max) {
                max = grid[i][j];
            }
        }
    }
    return max;
}

Grid Grid::next_step() {
    double hx = 1./rows;
    double hy = 1./columns;
    double C = 1.;
    double dt = 1.;
    Grid newgrid(rows, columns);
    
    double diagx = -2.0 + hx*hx/(2*C*dt);
		double diagy = -2.0 + hy*hy/(2*C*dt);
    double weightx = C*dt/(hx*hx);
		double weighty = C*dt/(hy*hy);
		/* Perform an explicit update on the points within the domain.
		* Optimization : inner loop on columns index (second index) since
		* C++ is row major */
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < columns - 1; j++) {
            newgrid.grid[i][j] = weightx*(grid[i-1][j] + grid[i+1][j] + grid[i][j]*diagx) + weighty*(grid[i][j-1] + grid[i][j+1] + grid[i][j]*diagy);
				}
    }
    return newgrid;
}

void Grid::swap(Grid grid_2) {
    if (grid_2.rows != rows || grid_2.columns != columns) {
        cerr << "Error of shape between two grids in swap() !" << endl;
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            grid[i][j] = grid_2.grid[i][j];
        }
    }
}

Grid Grid::state_grid_after_time(int time) {
    write_to_bmp(*this, 0);
    for (int i = 0; i < time; i++) {
        auto newgrid = next_step();
        write_to_bmp(*this, i + 1);
        swap(newgrid);
    }
    return *this;
}


void Grid::print_grid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}  
