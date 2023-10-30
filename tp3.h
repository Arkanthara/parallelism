#ifndef __TP3_H__
#define __TP3_H__

struct Grid {
				double ** grid;
				int rows;
				int columns;
};
Grid create_grid(int row, int columns);
void print_grid(Grid grid);

#endif
