#include<iostream>
#include <vector>
#include <complex>

using namespace std;
using std::vector;
using std::complex;


class Grid {
	public:
		int x;
		int y;
		int br;
		int tl;
		vector<vector<complex<double>>> fractal;
		vector<vector<complex<double>>> pixel;
		Grid(int x, int y) {
			this -> x = x;
			this -> y = y;
			this -> fractal.resize(x);
			for (int i = 0; i < x; i ++) {
				this -> fractal[i].resize(y);
				for (int j = 0; j < y; j++) {
					this -> fractal[i][j] = 0.;
				}
			}
			br = 0;
			tl = 0;
		}
		void print_grid() {
			cout << "Grid" << endl;
			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					cout << " " << fractal[i][j] << " ";
				}
				cout << endl;
			}
		}

};

int main(int argc, char * argv[]) {

	Grid grid = Grid(10, 10);
	grid.print_grid();
}
