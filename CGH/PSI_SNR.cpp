#include <stdio.h>
#include <math.h>
#include <complex>

#include "maindec.h"

double error_psi(double tab_Ampl[N][N], double tab_Ampl_object[N][N])
{

	double Psi;
	double Ampl_gmod;
	double Ampl_hmod;
	double R_Ampl_mod;

	Psi = 0.0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Ampl_gmod = tab_Ampl_object[i][j] * tab_Ampl_object[i][j];
			Ampl_hmod = tab_Ampl[i][j] * tab_Ampl[i][j];

			R_Ampl_mod = Ampl_gmod - Ampl_hmod;
			R_Ampl_mod = R_Ampl_mod * R_Ampl_mod;

			Psi += R_Ampl_mod;
		}
	}

	return Psi = (1.0 / N * N) * Psi;
}

double SNR(double tab_Ampl_object[N][N], double tab_Ampl[N][N], double tab_Phase_object[N][N], double tab_Phase[N][N])
{

	double D;
	double snr;
	double Ampl_gmod;
	double Ampl_hmod;
	double Sum_g = 0;
	double Sum_h = 0;
	double Mod_R_complex_gh, S_Mod_R_complex_gh;

	std::complex<double>  g_complex, h_complex, R_complex_gh;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Ampl_gmod = tab_Ampl_object[i][j] * tab_Ampl_object[i][j];
			Ampl_hmod = tab_Ampl[i][j] * tab_Ampl[i][j];

			Sum_g += Ampl_gmod;
			Sum_h += Ampl_hmod;
		}
	}

	D = sqrt(Sum_g / Sum_h);

	S_Mod_R_complex_gh = 0.0;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			g_complex = polar(tab_Ampl_object[i][j], tab_Phase_object[i][j]);
			h_complex = polar(tab_Ampl[i][j], tab_Phase_object[i][j]);

			R_complex_gh = g_complex - D * h_complex;
			Mod_R_complex_gh = norm(R_complex_gh);
			Mod_R_complex_gh = Mod_R_complex_gh * Mod_R_complex_gh;

			S_Mod_R_complex_gh += Mod_R_complex_gh;
		}
	}

	snr = Sum_g / S_Mod_R_complex_gh;

	return snr;
}