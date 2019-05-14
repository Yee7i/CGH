#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;

const int N = 64;

int kwant = 2;

const double M_PI = 3.14159265358979323846;

int podaj_stopien()
{
	cout << "Podaj stopien kwantowania: ";
	cin >> kwant;

	return kwant;
}

string stopien_kwant()
{
	return to_string(kwant);
}

void kwant_a(double input[N][N]) 
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

	double step = max / kwant;
	double step_real = 0;

	cout << "Max: " << max << endl;

	for (int i = 0; i < kwant; i++)
	{
		cout << step * i << " ";
	}

	cout << "Step: " << step << " Max: " << max << endl << endl;

/*	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < kwant; k++)
			{

				step_real = step * k;
				double step_next = step * (k + 1);

				if (input[i][j] >= step_real && input[i][j] <= step_next)
				{
					double step_med = (step_real + step_next) / 2;

					if (input[i][j] < step_med)
					{
						input[i][j] = step_real;
					}

					if (input[i][j] > step_med)
					{
						input[i][j] = step_next;
					}

					if (input[i][j] == step_med)
					{
						input[i][j] = step_med;
					}
				}
			}
		}
	}*/

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < kwant; k++)
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

void kwant_f(double input[N][N]) 
{

	double max = M_PI;

	double step = max / kwant;
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

			for (int k = 0; k < kwant; k++)
			{

				step_real = step * k;
				double step_next = step * (k + 1);

				if (input[i][j] >= step_real && input[i][j] <= step_next)
				{
					double step_med = (step_real + step_next) / 2;

					if (input[i][j] < step_med)
					{
						input[i][j] = step_real;
					}

					if (input[i][j] > step_med)
					{
						input[i][j] = step_next;
					}

					if (input[i][j] == step_med)
					{
						input[i][j] = step_med;
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