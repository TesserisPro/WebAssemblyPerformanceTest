#include "pch.h"

// Necessary, because emscripten don`t want load to all dependecies that contain windows.h.
// But that dependencies is necessary for C++ project so that an error about NO TARGET PLATFORM does not appear
#if __EMSCRIPTEN__
#else
#include <windows.h>
#endif

#include <iostream>
#include <math.h>
#include <time.h>
#include <cstdint>

using namespace std;

const double kRandMinValue = 0.0001;
const double kRandMaxValue = 100000;

extern "C" double GetRandomNumber(double min_value = kRandMinValue, double max_value = kRandMaxValue)
{
	double rand_value = (double)rand() / RAND_MAX;
	return min_value + rand_value * (max_value - min_value);
}

extern "C" double DifficultCalculations()
{
	const int kRowsCount = 10000;
	const int kColumnsCount = 6000;
	
	double result = 0;
	double divider = pow(133, 13);


	// Allocate memory

	double *first_array = new double[kRowsCount];

	double **second_array = new double *[kRowsCount];
	for (int i = 0; i < kRowsCount; ++i)
		second_array[i] = new double[kColumnsCount];

	double **third_array = new double *[kRowsCount];
	for (int i = 0; i < kRowsCount; ++i)
		third_array[i] = new double[kColumnsCount];

	double **result_array = new double *[kRowsCount];
	for (int i = 0; i < kRowsCount; ++i)
		result_array[i] = new double[kColumnsCount];


	for (int i = 0; i < kRowsCount; i++)
	{
		first_array[i] = rand() % 1000 + pow(GetRandomNumber(), GetRandomNumber(1, 6)) + pow(GetRandomNumber(), GetRandomNumber(1, 6));
	}

	for (int i = 0; i < kRowsCount; i++)
	{
		for (int j = 0; j < kColumnsCount; j++)
		{
			second_array[i][j] = rand() % 10000 + pow(GetRandomNumber(), GetRandomNumber(1, 6)) + pow(GetRandomNumber(), GetRandomNumber(1, 6));
			third_array[i][j] = rand() % 10000 + pow(GetRandomNumber(), GetRandomNumber(1, 6)) + pow(GetRandomNumber(), GetRandomNumber(1, 6));
		}
	}

	for (int i = 0; i < kRowsCount; i++)
	{
		for (int j = 0; j < kColumnsCount; j++)
		{
			result_array[i][j] = first_array[i] + second_array[i][j] - third_array[i][j];
		}
	}

	for (int i = 0; i < kRowsCount; i++)
	{
		for (int j = 0; j < kColumnsCount; j++)
		{
			result_array[i][j] += second_array[i][j] * third_array[i][j] * GetRandomNumber(1, 2);
		}
	}

	first_array[0] = 1;
	for (int i = 1; i < kColumnsCount; i++)
	{
		first_array[i] = cos(GetRandomNumber(1, 20) * i) * sin(i * GetRandomNumber(1, 20)) * log(GetRandomNumber(1, 20) * pow(i, 3));
	}

	for (int i = 0; i < kRowsCount; i++)
	{
		for (int j = 0; j < kColumnsCount; j++)
		{
			result += (first_array[i] + result_array[i][j]) / divider;
		}
	}

	for (int i = 0; i < kRowsCount; i++)
	{
		for (int j = 0; j < kColumnsCount; j++)
		{
			result -= result_array[i][j] * GetRandomNumber(0.001, 1);
		}
	}


	// Release memory

	delete[] first_array;

	for (int i = 0; i < kRowsCount; ++i)
	{
		delete[] second_array[i];
	}
	delete[] second_array;

	for (int i = 0; i < kRowsCount; ++i)
	{
		delete[] third_array[i];
	}
	delete[] third_array;

	for (int i = 0; i < kRowsCount; ++i)
	{
		delete[] result_array[i];
	}
	delete[] result_array;


	return result;
}

int main()
{
	unsigned long long start_time = clock();
	cout << "Result: " << DifficultCalculations() << endl;
	unsigned long long end_time = clock();

	double time_diff = (double)(end_time - start_time) / 1000;
	cout << "Time difference is " << time_diff << " seconds" << endl;

	return 0;
}
