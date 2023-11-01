#ifndef __GRID_H__
#define __GRID_H__

#include <vector>

class Grid {
    public:
    int rows;
    int columns;
    std::vector<double> grid_line;
    std::vector<std::vector<double>> grid_1;
    std::vector<std::vector<double>> grid_2;
    Grid(int x, int y);
    int get_index(int i, int j);
    int * get_index(int n);
    double get_min();
    double get_max();
    void print_grid(void);
    void next_step(void);
    void state_grid_after_time(int time);
};

#endif
