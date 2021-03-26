#include <main.h>

#define ROW 3
#define COL 3

/* Task 1
 * 1). Реализовать пузырьковую сортировку двумерного массива
 * например, массив:
 * 1,9,2
 * 5,7,6
 * 4,3,8
 *
 * должен на выходе стать:
 * 1,2,3
 * 4,5,6
 * 7,8,9
*/
int ar[ROW][COL] = 
	{{1, 9, 2},
	 {5, 7, 6},
	 {4, 3, 8}};

void swapInteger(int *a, int *b) {
	*a = *a ^ *b;
	*b = *b ^ *a;
	*a = *a ^ *b;
}

void bubbleSort(int *array, int size) {
	for (int i = 0; i < size; i++)
		for(int j = 0; j < size - 1; j++)
			if (array[j] > array[j + 1])
				swapInteger(&array[j], &array[j + 1]);
}

void printAr(int* array, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			printf("%d ", *(array + (ROW * i + j)));
		printf("\n");
	}
}

/* Task 2
 * Описать подробную блок-схему и написать алгоритм Трабба-Прадо-Кнута
 * 1 - запросить у пользователя 11 чисел и записать их в последовательность П
 * 2 - инвертировать последовательность П
 * 3 - для каждого элемента последовательности П произвести вычисление по формуле 
 * sqrt(fabs(Х)) + 5 * pow(Х, 3) и, если результат вычислений превышает 400,- проинформировать пользователя.
*/

double tpkFunction(double value) {
	return sqrt(fabs(value)) + 5 * pow(value, 3);
}

int main(int argc, char** args) {
	// Task 1
	printAr(*ar, ROW, COL);
	bubbleSort(*ar, sizeof(ar) / sizeof(int));
	printAr(*ar, ROW, COL);
	// Task 2
	double inputarr[11];
	double y = 0;
	printf("Enter 11 numbers:\n");
	for (int i = 0; i < 11; i++) {
		printf("%d: ", i);
		scanf("%lf", &inputarr[i]);
	}
	for (int i = 10; i >= 0; i--) {
		y = tpkFunction(inputarr[i]);
		(y > 400) ? printf("%d Too Large\n", i) : printf("%d %.16g\n", i, y);
	}
	return EXIT_SUCCESS;
}
