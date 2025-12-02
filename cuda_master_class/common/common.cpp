#include "common.h"
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <cmath>

void initialize(int * input, const int array_size,
	INIT_PARAM PARAM, int x)
{
	if (PARAM == INIT_ONE)
	{
		for (int i = 0; i < array_size; i++)
		{
			input[i] = 1;
		}
	}
	else if (PARAM == INIT_ONE_TO_TEN)
	{
		for (int i = 0; i < array_size; i++)
		{
			input[i] = i % 10;
		}
	}
	else if (PARAM == INIT_RANDOM)
	{
		// 使用高精度时间 + 地址作为种子，确保每次都不同
		srand((unsigned)(time(NULL) * 1000 + (size_t)input));
		for (int i = 0; i < array_size; i++)
		{
			input[i] = (int)(rand() & 0xFF);
		}
	}
	else if (PARAM == INIT_FOR_SPARSE_METRICS)
	{
		srand(time(NULL));
		int value;
		for (int i = 0; i < array_size; i++)
		{
			value = rand() % 25;
			if (value < 5)
			{
				input[i] = value;
			}
			else
			{
				input[i] = 0;
			}
		}
	}
	else if (PARAM == INIT_0_TO_X)
	{
		srand(time(NULL));
		int value;
		for (int i = 0; i < array_size; i++)
		{
			input[i] = (int)(rand() & 0xFF);
		}
	}
}


//cpu reduction
int reduction_cpu(int * input, const int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += input[i];
	}
	return sum;
}

void compare_results(int gpu_result, int cpu_result)
{
	printf("GPU result : %d , CPU result : %d \n",
		gpu_result, cpu_result);

	if (gpu_result == cpu_result)
	{
		printf("GPU and CPU results are same \n");
		return;
	}

	printf("GPU and CPU results are different \n");
}

void compare_results(float* a, float* b, int size) {
	for(int i=0; i<size; i++) {
		if(fabs(a[i] - b[i]) > 1e-6) {
			printf("Arrays are different \n");
			return;
		}
	}
	printf("Arrays are the same \n");
}

void sum_array_cpu(float* a, float* b, float* c, int size) {
	for(int i=0; i<size; i++) {
		c[i] = a[i] + b[i];
	}
}