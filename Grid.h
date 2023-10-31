#ifndef __GRID_H__
#define __GRID_H__

#include <vector>

class Grid {
    private:
    int rows;
    int columns;
    public:
    std::vector<double> grid_line;
    std::vector<std::vector<double>> grid;
    Grid(int x, int y);
    double get_element(int i, int j);
    int get_rows();
    int get_columns();
    double get_min();
    double get_max();
    void print_grid(void);
    void next_step(void);
    void state_grid_after_time(int time);
    void swap(Grid grid);
};

#endif
