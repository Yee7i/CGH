#include <complex>

#ifndef FT_H
#define FT_H

using namespace std;

const int M = 64;
const int q = 6;

void ft(double sign, complex<double> tab_SQ[M][M] );
void kwant_a(double input[M][M], int kwant);
void kwant_f(double input[M][M], int kwant);
string stopien_kwant(int kwant);

double error_psi(double tab_Ampl[M][M], double tab_Ampl_obiekt[M][M]);
double SNR(double tab_Ampl_obiekt[M][M], double tab_Ampl[M][M], double tab_Faza_obiekt[M][M], double tab_Faza[M][M]);

#endif