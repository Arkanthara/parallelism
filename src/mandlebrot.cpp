#include <iostream>
#include <vector>
#include <complex>


using namespace std;
using std::vector;
using std::complex;


void mandlebrot(int W, int H, int br_x, int tl_x, int br_y, int tl_y, int iter) {
	//double x_scale = (br_x - tl_x)/W * .05;
	//double y_scale = (br_y - tl_y)/H * .05;
	double x_scale = (br_x - tl_x)/W * 1./(W);
	double y_scale = (br_y - tl_y)/H * 1./(H);

	for (int y = tl_y; y < br_y; y++) {
		for (int x = tl_x; x < br_x; x++) {
			//complex <double> z, c = {2.*x/W-1.5, 2.*y/H-1};
			//complex <double> c(x * x_scale + tl_x, y * y_scale + tl_y);
			//complex <double> z(0, 0);
			complex <double> z, c = {x*x_scale + tl_x - 10*1./W, y * y_scale + tl_y - 10*1./H };
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
	// mandlebrot(1000, 1000, 1000, 500, 1000, 500, 100);
	// mandlebrot(70, 30, 70, 0, 30, 0, 1000);
	mandlebrot(100, 30, 100, 0, 30, 0, 1000);
	return 0;
}
