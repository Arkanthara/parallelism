#include <iostream>
#include "Grid.h"
#include "write.h"

using namespace std;

int main(int argc, char * argv[]) {
    if (argc != 3) {
        cerr << "Error ! Usage: ./tp3 grid_dimension time" << endl;
    }
    Grid grid(atoi(argv[1]), atoi(argv[1]));
    // grid.next_step();
    // grid.swap(newgrid);
    grid.state_grid_after_time(atoi(argv[2]));
    write_to_bmp(grid, atoi(argv[2]));
}
