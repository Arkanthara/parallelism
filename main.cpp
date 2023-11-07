#include <iostream>
#include "Grid.h"
#include "write.h"

using namespace std;

int main(int argc, char * argv[]) {
    if (argc <  2) {
        cerr << "Error ! Usage: ./tp3 grid_dimension time" << endl;
    }
    Grid grid(atoi(argv[1]), atoi(argv[1]));
    // grid.next_step();
    // grid.swap(newgrid);
    // int n = grid.get_indice(atoi(argv[1]) - 1, atoi(argv[1]) - 1);
    // int * indices = grid.get_indices(n);
    // cout << "Indice " << n << " Indices " << indices[0] << indices[1] << endl;
    grid.parallelized_state_grid_after_time(1);
    // grid.state_grid_after_time(atoi(argv[2]));
    grid.print_grid();
    // write_to_bmp(grid, atoi(argv[2]));
}
