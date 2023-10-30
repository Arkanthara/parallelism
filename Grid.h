#ifndef __GRID_H__
#define __GRID_H__

class Grid {
    private:
    int rows;
    int columns;
    public:
    double ** grid;
    Grid(int x, int y);
    int get_rows();
    int get_columns();
    double get_min();
    double get_max();
    void print_grid(void);
    Grid next_step(void);
    Grid state_grid_after_time(int time);
    void swap(Grid grid);
};

#endif
