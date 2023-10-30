#include <iostream>
#include "Grid.h"


using namespace std;

 
Grid::Grid(int x, int y) {
    rows = x;
    columns = y;
    grid = new double * [rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new double [columns];
        for (int j = 0; j < columns; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
                grid[i][j] = 0.0;
            }
            else {
                grid[i][j] = 1.0;
            }
        }
    }
}

Grid::print_grid() {
    for (int i = 0; i < rows; i++) {
        cout << endl;
        for (int j = 0; j < columns; j++) {
            cout << grid[i][j] << " ";
        }
    }
}  
