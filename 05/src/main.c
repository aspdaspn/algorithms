#include <main.h>

void randomArray(int *array, const int len, const int border) {
	srand(time(NULL));
	for (int i = 0; i < len; ++i)	{
		*(array + i) = rand() % border;
	}
}

void printIntArray(int *array, const int size, const int offset) {
	char format[5];
	sprintf(format, "%%%dd", offset);

	for (int i = 0; i < size; ++i)
		printf(format, *(array + i));
	printf("\n");
}

void sortInsert(int *array, int length) {
	int temp, pos;
	for (int i = 1; i < length; i++) {
		temp = array[i];
		pos = i - 1;
		while (pos >= 0 && array[pos] > temp) {
			array[pos + 1] = array[pos];
			pos--;
		}
		array[pos + 1] = temp;
	}
}

void swapInteger(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void qs(int *array, int first, int last) {
	int i = first;
	int j = last;
	int x = array[(first + last) / 2];
	do {
		while (array[i] < x) i++;
		while (array[j] > x) j--;
		if (i <= j) {
			swapInteger(&array[i], &array[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (i < last) qs(array, i, last);
	if (first < j) qs(array, first, j);
}

int *median(int *a, int *b, int *c) {
	if ((*b < *a && *a < *c) || (*b > *a && *a > *c)) return a;
	else if ((*a < *b && *b < *c) || (*a > *b && *b > *c)) return b;
	return c;
}

void improvedQS(int *array, int first, int last) {
	if ((last - first) > 10) {
		int x = (first + last) / 2;
		swapInteger(&array[x], median(&array[first], &array[x], &array[last]));
		qs(array, first, last);
	} else 
		sortInsert(array, last + 1);
}

void evenBS(int *array, int length) {
	const int max = length;
	const int b = 10;

	int buckets[b][max + 1];

	for (int i = 0; i < b; ++i)
		buckets[i][max] = 0;

	for (int digit = 1; digit < 1000000000; digit *= 10) {
		for (int i = 0; i < max; ++i)	{
			int d = (array[i] / digit) % b;
			if (array[i] % 2 == 0)
				buckets[d][buckets[d][max]++] = array[i];
		}
		int idx = 0;
		for (int i = 0; i < b; ++i) {
			for (int j = 0; j < buckets[i][max];)
				if (array[idx] % 2 == 0) 
					array[idx++] = buckets[i][j++];
				else
					idx++;
			buckets[i][max] = 0;
		}
	}
}


int main(int argc, char** args) {
	/* Task 1
	 * Описать в коде улучшенный алгоритм быстрой сортировки - описана в видео "Быстрая Сортировка. Улучшения."
	 */
	const int SIZE = 20;
	const int randNum = 99;
	const int offset = 3;
	int array[SIZE];
	randomArray(array, SIZE, randNum);
	printIntArray(array, SIZE, offset);
	improvedQS(array, 0, SIZE - 1);
	printIntArray(array, SIZE, offset);

	/* Task 2
	 * Сортировать в массиве целых положительных чисел только чётные числа, нечётные оставив 
	 * на своих местах при помощи алгоритма блочной сортировки.
	 * Пример: массив [0 2 8 3 4 6 5 9 8 2 7 3] 
	 * превратить в массив [0 2 2 3 4 6 5 9 8 8 7 3]
	 */
	int arr[12] = {0, 2, 8, 3, 4, 6, 5, 9, 8, 2, 7, 3};
	int arrSZ = sizeof(arr) / sizeof(int);
	printIntArray(arr, arrSZ, offset);
	evenBS(arr, arrSZ);
	printIntArray(arr, arrSZ, offset);

	return EXIT_SUCCESS;
}
