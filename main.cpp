#include <iostream>
#include "Grid.h"

using namespace std;

int main() {
    Grid grid(100, 100);
    grid.print_grid();
    auto newgrid = grid.next_step();
    newgrid.print_grid();
    newgrid = grid.state_grid_after_time(100);
}
