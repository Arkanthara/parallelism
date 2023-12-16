#include <iostream>
#include <execution>
#include <algorithm>
#include <unistd.h>
#include <vector>
#include "writer.hpp"

using namespace std;
using std::vector;

// Inline is usefull to copy the function because if we have a foreach and a lambda function that call this function, this function is on stack, so to have the function defined on the device, the inline indicate that the function must be copied on the device...
int inline i2x(int index, int size) {
	return index / size;
}

int inline i2y(int index, int size) {
	return index % size;
}

int inline xy2i(int x, int y, int size) {
	return x * size + y;
}


int main(int argc, char * argv[]) {

	int max_iter = 100;
	int size = 128;
	int option;
	while((option = getopt(argc, argv, "s:i:")) != -1) {
		switch (option) {
			case 's':
				size = atoi(optarg);
				if (size == 0) {
					cerr << "Error" << endl;
				}
				break;
			case 'i':
				max_iter = atoi(optarg);
				if (max_iter == 0) {
					cerr << "Error" << endl;
				}
				break;
			case '?':
				cout << "Usage: " << endl;
				break;
		}
	}

	// If we don't put inline, the function is defined on stack, so we can't use it on gpus...
	

	auto create_grid = [](int size) {
		vector<double> grid;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
					grid.push_back(1.);
				else grid.push_back(0.);
			}
		}
		return grid;
	};

	auto print_grid = [](vector<double> grid, int size) {
		int index = 0;
		for (int i = 0; i < size; i ++) {
			for (int j = 0; j < size; j ++) {
				cout << grid[index] << " ";
				index ++;
			}
			cout << endl;
		}
	};

	vector<double> grid_2 (size * size, 0.);

	print_grid(create_grid(8), 8);

	int start = grid.data();

	auto hx = 1./size;
	auto hy = 1./size;
	
	auto C = 1.;
	
	auto dt = 0.25*hx*hx/C;
	
	auto diagx = -2.0 + hx*hx/(2*C*dt);
	auto diagy = -2.0 + hy*hy/(2*C*dt);
	auto weightx = C*dt/(hx*hx);
	auto weighty = C*dt/(hy*hy);

	//FILL
	for(int iT = 0; iT < max_iter;iT++)
	{
		for_each(std::execution::par, grid_2.begin(), grid_2.end(),
			[start = grid_2.data(), size, grid](double& item) {
				index = item - start;
				int x = i2x(index, size);
				int y = i2y(index, size);
				if (x == 0 || y == 0 || x == size - 1 || y == size - 1)
					item = grid[index];
				else
					item = weightx*(grid[xy2i(x-1, y, size)]
					+ grid[xy2i(x+1, y, size)]
					+ grid[xy2i(x, y, size)]*dxagx)
					+ wexghty*(grid[xy2i(x, y-1, size)]
					+ grid[xy2i(x, y+1, size)]
					+ grid[xy2i(x, y, size)]*dxagy)
			});
		swap(grid_2, grid);
		/*
		for (int i = 1; i < size - 1; i++)
			for (int j = 1; j < size-1; j++)
				U[i][j] = weightx*(U0[i-1][j] + U0[i+1][j] + U0[i][j]*diagx) + weighty*(U0[i][j-1] + U0[i][j+1] + U0[i][j]*diagy);
		swap(U,U0);
		*/
	}
	write_to_bmp(size, grid, max_iter, 0, 1);
}

