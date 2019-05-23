#include <complex>

#ifndef maindec
#define maindec

const int N = 64;
const int p = 6;

void ft(double sign, std::complex<double> tab_SQ[N][N]);
void quant_a(double input[N][N], int quant);
void quant_p(double input[N][N], int quant);
std::string level_quant(int quant);
std::string open();

double error_psi(double tab_Ampl[N][N], double tab_Ampl_object[N][N]);
double SNR(double tab_Ampl_object[N][N], double tab_Ampl[N][N], double tab_Phase_object[N][N], double tab_Phase[N][N]);

bool returnfilled(int i, int j);

struct output_options
{
	std::string path_input;
	std::string quant_val;
	bool quant_b;
	bool chart_b;
	bool cutout_b;
	bool color_b;
	bool flag_in;
	bool flag_exit;
};

output_options gui();

using namespace std;

#endif
