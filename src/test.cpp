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


vector<vector<double>> convert_to_2D(vector<double> grid_line, vector<vector<double>> grid, int size) {
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


	Window frac_br = Window(500, 500);
	Window frac_tl = Window(400, 400);

	int iterations = 25;
	vector<double> pFractal(78*22);
	vector<vector<double>> View;
	View.resize(1000);
	for (int i = 0; i < 1000; i++) {
		View[i].resize(1000);
		for (int j = 0; j < 1000; j++) {
			View[i][j] = 0;
		}
	}

	double x_scale = (frac_br.x - frac_tl.x) / 1000.;
	double y_scale = (frac_br.y - frac_tl.y) / 1000.;

	for (int y = 0; y < 78; y++) {
		for (int x = 0; x < 22; x++) {
			complex <double> c(x * x_scale + frac_tl .x, y * y_scale + frac_tl .y);
			complex <double> z(0, 0);
			int n = 0;
			while (abs(z) < 2.0 && n < iterations) {
				z = (z * z) + c;
				n++;
			}
			cout << (n == iterations ? '0':'.');
			pFractal[y * 78 + x] = (double)n/(double)iterations;
		}
		cout << endl;
	}
	// cout << "Min: " << *min_element(pFractal.begin(), pFractal.end()) << "Max: " << *max_element(pFractal.begin(), pFractal.end()) << endl;
	//View = convert_to_2D(pFractal, View, 1000);
	// write_to_bmp(iterations,View,1, *min_element(pFractal.begin(), pFractal.end()), *max_element(pFractal.begin(), pFractal.end()));
	//write_to_bmp(1000, View, 1, 0., 1.);

	return 0;
}
