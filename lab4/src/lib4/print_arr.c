#include "lib4.h"

void print_arr(int *arr, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
}
