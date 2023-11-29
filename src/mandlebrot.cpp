#include <iostream>
#include <vector>
#include <complex>


using namespace std;
using std::vector;
using std::complex;


void mandlebrot(int W, int H, int br_x, int tl_x, int br_y, int tl_y, int iter) {
	double x_scale = (br_x - tl_x) / W;
	double y_scale = (br_y - tl_y) / H;

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			//complex <double> z= 2.*x/W-1.5;
			complex <double> c(x * x_scale + tl_x, y * y_scale + tl_y);
			complex <double> z(0, 0);
			//complex <double> c = 2.*y/H-1;
			int n = 0;
			while (abs(z) < 2.0 && n < iter) {
				z = (z * z) + c;
				n++;
			}
			cout << (n == iter ? 'o':'.');
		}
		cout << endl;
	}
}

int main(int argc, char * argv[]) {
	mandlebrot(1000, 1000, 1000, 500, 1000, 500, 100);
	return 0;
}
