#include <iostream>
#include <vector>
#include <complex>
#include "writer.h"
#include <algorithm>

using namespace std;
using std::vector;
using std::complex;

class Window {
	public:
		int x;
		int y;
		Window(int w, int z) {
			x = w;
			y = z;
		}
};

void print_grid(vector<vector<int>> grid, int size) {
        for (int i = 0; i < size; i ++) {
                for (int j = 0; j < size; j ++)
                        cout << grid[i][j] << " ";
                cout << endl;
        }
}


vector<vector<int>> convert_to_2D(vector<int> grid_line, vector<vector<int>> grid, int size) {
        int n = 0;
        for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                        grid[i][j] = grid_line[n];
                        n++;
                }
        }
        return grid;
}


int main(int argc, char * argv[]) {


	Window frac_br = Window(1000, 1000);
	Window frac_tl = Window(0, 0);
	Window pix_tl = Window(0, 0);
	Window pix_br = Window(1000, 1000);

	int iterations = 1e2;
	vector<int> pFractal(1000000);
	vector<vector<int>> View;
	View.resize(1000);
	for (int i = 0; i < 1000; i++) {
		View[i].resize(1000);
		for (int j = 0; j < 1000; j++) {
			View[i][j] = 0;
		}
	}

	double x_scale = (frac_br.x - frac_tl.x) / 1000.;
	double y_scale = (frac_br.y - frac_tl.y) / 1000.;

	for (int y = 0; y < 1000; y++) {
		for (int x = 0; x < 1000; x++) {
			complex <double> c(x * x_scale + frac_tl .x, y * y_scale + frac_tl .y);
			complex <double> z(0, 0);
			int n = 0;
			while (abs(z) < 2.0 && n < iterations) {
				z = (z * z) + c;
				n++;
			}
			pFractal[y * 1000 + x] = n;
		}
	}
	cout << "Min: " << *min_element(pFractal.begin(), pFractal.end()) << "Max: " << *max_element(pFractal.begin(), pFractal.end()) << endl;
	View = convert_to_2D(pFractal, View, 1000);
	write_to_bmp(iterations,View,1, *min_element(pFractal.begin(), pFractal.end()), *max_element(pFractal.begin(), pFractal.end()));

	return 0;
}
