#include <stdio.h>
#include <stdlib.h>
#include "../header.h"

void free_2d_array (void **arr, int size) {
	int i = 0;
	for (i = 0; i < size; i++) {
		free(arr[i]);
	}
	free(arr);
}

void shake_sort_int(int *arr, int size) {
	int i = 0;
	int left = 0;
	int right = size - 1;
	int buf = 0;;
	while (left <= right) {
		for (i = right; i > left; --i) {
			if (*(arr + i - 1) > *(arr + i)) {
				
				buf = *(arr + i - 1);
				*(arr + i - 1) = *(arr + i);
				*(arr + i) = buf;
				
			}
		}
		++left;
		for (i = left; i < right; ++i) {
			if (*(arr + i) > *(arr + i + 1)) {
				
				buf = *(arr + i);
				*(arr + i) = *(arr + i + 1);
				*(arr + i + 1) = buf;
				
			}
		}
		--right;
	}
}

int pow_i(int a, unsigned int b) {
	int i = 0;
	int res = 1;
	for (i = 0; i < b; i++) {
		res *= a;
	}
	return res;
}