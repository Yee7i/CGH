#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

const int N = 64;

int quant = 0;

const double M_PI = 3.14159265358979323846;

string level_quant(int quant)
{
	return to_string(quant);
}

void quant_a(double input[N][N], int quant) 
{
	double max = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (input[i][j] > max)
			{
				max = input[i][j];
			}
		}
	}

	double step = max / quant;
	double step_real = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < quant; k++)
			{

				step_real = step * k;
				double step_next = step * (k + 1);

				if (input[i][j] >= step_real && input[i][j] <= step_next)
				{
				
					if (input[i][j] < step_next)
					{
						input[i][j] = step_real;
					}

				}
			}
		}
	}
}

void quant_p(double input[N][N], int quant) 
{

	double max = -10;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (input[i][j] > max)
			{
				max = input[i][j];
			}
		}
	}

	double step = max / quant;
	double step_real = 0;
	bool neg = false;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			if (input[i][j] < 0)
			{
				input[i][j] = input[i][j] - input[i][j] * 2;
				neg = true;
			}

			for (int k = 0; k < quant; k++)
			{

				step_real = step * k;
				double step_next = step * (k + 1);

				if (input[i][j] >= step_real && input[i][j] <= step_next)
				{

					if (input[i][j] >= step_real && input[i][j] <= step_next)
					{

						if (input[i][j] < step_next)
						{
							input[i][j] = step_real;
						}

					}
				}
			}

			if (neg == true)
			{
				input[i][j] = input[i][j] - 2 * input[i][j];
				neg = false;
			}
		}
	}
}