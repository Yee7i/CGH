#include <iostream>
#include <complex>

using namespace std;

const int N = 64;
const int p = 6;
const int N1 = N / 2;

void ft(double sign, std::complex<double> tab_SQ[N][N])
{
	const double M_PI = 3.14159265358979323846;

	std::complex<double> numImaginary(0.0, 1.0);

	int tab_bb[N / 2] = { 0 };
	int tab_index[N] = { 0 };

	int l1 = 0;
	int l2 = N / 2;
	int l3 = l2 / 2;
	int l4 = l2 + l3;

	bool f1 = true;

	for (int i = 0; i < N1; i += 4)
	{
		tab_bb[i] = l1;
		tab_bb[i + 1] = l2;
		tab_bb[i + 2] = l3;
		tab_bb[i + 3] = l4;

		if (i < N1 / 2) 
		{
			if (f1 == true)
			{
				l1 += N / 8;
				l2 += N / 8;
				l3 += N / 8;
				l4 += N / 8;
				f1 = false;
			}
			else
			{
				l1 -= N / 16;
				l2 -= N / 16;
				l3 -= N / 16;
				l4 -= N / 16;
				f1 = true;
			}
		}

		else
		{
			int loop2 = 0;

			for (int j = i; j < N1; j++)
			{
				tab_bb[j] = tab_bb[loop2] + 2;
				loop2++;
				i++;
			}
		}
	}

	int loop1 = 0;

	for (int i = 0; i < N1; i++)
	{
		tab_index[i] = tab_bb[i];
	}

	for (int i = N / 2; i < N; i++)
	{
		tab_index[i] = tab_bb[loop1] + 1;

		loop1++;
	}

	int j;
	int tab_P[p + 1];
	int tab_Q[p + 1];

	for (j = 0; j <= p; ++j)
	{
		tab_P[j] = pow(2, j);
	}

	int ni;
	ni = p;

	for (j = 0; j <= p; ++j)
	{
		tab_Q[j] = tab_P[ni];
		ni = --ni;
	}

	int j_;
	int k, k_;
	int kk;
	int m, m_, mm, mm_;
	int b, b_, a, a_;
	int bb;
	int rr, rr_, pp, pp_, qq, qq_, ss, ss_;
	int fac1, fac2;

	std::complex<double> tab_SP[N][N];
	std::complex<double> tab_u1[2][N / 2];
	std::complex<double> tab_v1[2][2];

	for (m = 1; m <= p; ++m)
	{

		m_ = m;
		mm = m - 1;
		mm_ = m_ - 1;

		for (b = 0; b <= tab_P[mm] - 1; ++b)
		{
			bb = b - N / 2;

			for (k = 0; k <= 1; ++k)
			{
				kk = k - N / 2;
				tab_u1[k][b] = exp(sign*numImaginary*polar(2.0, 0.0)*polar(M_PI, 0.0)*polar((double)kk, 0.0)*polar((double)bb, 0.0) / (double)tab_P[m]);
			}
		}

		for (k = 0; k <= 1; ++k)
		{
			for (j = 0; j <= 1; ++j)
			{
				tab_v1[k][j] = exp(-numImaginary * polar(M_PI, 0.0)* polar((double)k, 0.0) * polar((double)j, 0.0));
			}
		}

		for (j = 0; j < N; ++j)
		{
			for (j_ = 0; j_ < N; ++j_)
			{
				tab_SP[j][j_] = (0, 0);
			}
		}

		for (b = 0; b <= tab_P[mm] - 1; ++b)
		{
			for (b_ = 0; b_ <= tab_P[mm_] - 1; ++b_)
			{
				for (a = 0; a <= tab_Q[m] - 1; ++a)
				{
					for (a_ = 0; a_ <= tab_Q[m_] - 1; ++a_)
					{
						for (j = 0; j <= 1; ++j)
						{
							rr = j * tab_Q[m];
							pp = tab_bb[b] + rr + a;

							for (j_ = 0; j_ <= 1; ++j_)
							{
								rr_ = j_ * tab_Q[m_];
								pp_ = tab_bb[b_] + rr_ + a_;

								for (k = 0; k <= 1; ++k)
								{
									ss = k * tab_Q[m];
									qq = tab_bb[b] + ss + a;

									for (k_ = 0; k_ <= 1; ++k_)
									{
										ss_ = k_ * tab_Q[m_];
										qq_ = tab_bb[b_] + ss_ + a_;
										tab_SP[pp][pp_] += tab_v1[k][j] * tab_u1[k][b] * tab_v1[k_][j_] * tab_u1[k_][b_] * tab_SQ[qq][qq_];
									}
								}
							}
						}
					}
				}
			}
		}

		for (j = 0; j < N; ++j)
		{
			for (j_ = 0; j_ < N; ++j_)
			{
				tab_SQ[j][j_] = tab_SP[j][j_];
			}
		}
	}

	for (j = 0; j < N; ++j)
	{
		fac1 = tab_index[j];

		for (j_ = 0; j_ < N; ++j_)
		{
			fac2 = tab_index[j_];
			tab_SQ[j][j_] = tab_SP[fac1][fac2];
		}
	}

	for (j = 0; j < N; ++j)
	{
		for (j_ = 0; j_ < N; ++j_)
		{
			tab_SQ[j][j_] /= N;
		}
	}
}