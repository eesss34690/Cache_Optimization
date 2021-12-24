// Complex Struct & Some Basic func

# include <stdio.h>
# include <stdlib.h>
# include <cmath>
# include <iostream>
# include <ctime>
# include <fstream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

# define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611793105118548074462379962749567351885752724891227938183011949129833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132000568127145263560827785771342757789609173637178721468440901224953430146549585371050792279689258923542019956112129021960864034418159813629774771309960518707211349999998372978049951059731732816096318595024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303598253490428755468731159562863882353787593751957781857780532171226806613 
using namespace std;

typedef struct Complex
{
	double re;
	double im;
	Complex() {
		re = 0;
		im = 0;
	};
	Complex(double a,double b) {
		re = a;
		im = b;
	};
} complex;


complex* initialize(vector<double> real, vector<double> img);
vector<double> back_real(complex* ans, int N);
vector<double> back_img(complex* ans, int N);
complex* append_seq(complex seq_1[], complex seq_2[], int N);
complex* reorder_seq(complex input_seq[], int N);
complex* Calc_WN(int N);
void printing (complex* val, int N);
int reverse_bit(int value, int N);

//initialize
complex* initialize(vector<double> real, vector<double> img)
{
	complex* seq = new complex[real.size()];
	for (int i = 0; i< real.size(); i++)
	{
		seq[i].re = real[i];
		seq[i].im = img[i];
	}
	return seq;
}

vector<double> back_real(complex* ans, int N)
{
	vector<double> real(N);
	for (int i = 0; i< N; i++)
	{
		real[i] = ans[i].re;
	}
	return real;
}

vector<double> back_img(complex* ans, int N)
{
	vector<double> real(N);
	for (int i = 0; i< N; i++)
	{
		real[i] = ans[i].im;
	}
	return real;
}


// Multiplier
complex ComplexMul(complex c1, complex c2)
{
	complex r;
	
	r.re = c1.re*c2.re - c1.im*c2.im;
	r.im = c1.re*c2.im + c1.im*c2.re;

	return r;
}

// Adder
complex ComplexAdd(complex c1, complex c2)
{
	complex r;
	
	r.re = c1.re + c2.re;
	r.im = c1.im + c2.im;
	
	return r;
}

// -c
complex ReverseComplex(complex c)
{
	c.re = -c.re;
	c.im = -c.im;
	
	return c;
}

// [seq_1], [seq_2] --> [seq_1,seq_2]
complex* append_seq(complex seq_1[], complex seq_2[], int N) {
	complex* total_seq = new complex[N*2];
	for (int i = 0; i < N; i++) {
		total_seq[i] = seq_1[i];
	}
	for (int i = N; i < 2*N; i++) {
		total_seq[i] = seq_2[i-N];
	}
	return total_seq;
}

// Reorder the input_seq to an order
complex* reorder_seq(complex input_seq[], int N) {
	complex* reordered_seq = new complex[N];
	for (int i = 0; i < N; ++i)
	{
		int k = reverse_bit(i, log2(N));
		reordered_seq[k] = input_seq[i];
	}
	return reordered_seq;
}

// Reverse Bit
int reverse_bit(int value, int N) {
	int ret = 0;
	int i = 0;
	while (i < N) {
		ret <<= 1;
		ret |= (value>>i) & 1;
		i++;
	}
	return ret;
}

// Calc WN[], with N = input_N
complex* Calc_WN(int N) {
	complex* WN = new complex[N];

	complex WN_unit; WN_unit.re = cos(2*PI/N); WN_unit.im = -sin(2*PI/N);
	WN[0].re=1; WN[0].im=0;

	for (int i = 1; i < N; ++i)
	{
		WN[i] = ComplexMul(WN[i-1], WN_unit);
	}

	return WN;
}

void printing(complex* val, int N)
{
	ofstream myfile;
	myfile.open ("performance.txt", ios::out | ios::app);
	for (int i = 0; i < N; ++i) {
		myfile << "\tX[" << i << "] = " << val[i].re << " + j*" << val[i].im << endl;
	}
}
