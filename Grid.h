#ifndef __GRID_H__
#define __GRID_H__

class Grid {
    private:
    double ** grid;
    int rows;
    int columns;
    public:
    
    Grid(int x, int y);

    void print_grid();
};

#endif
