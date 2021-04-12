#include "main.h"

#define ARSIZE 10

int simpleHashSum(char* in) {
	int out = 0;
	int i = 0;
	while (in[i] != '\0') {
		out += (int) in[i];
		++i;
	}
	return out;
}

int collection[ARSIZE] = { 0 };

int* exchange(int* money, int size, int sum) {
	int k = 0;
	int subtotal = 0;

	while (subtotal != sum && k < ARSIZE) {
		for (int i = 0; i < size; ++i)
			if (money[i] <= sum - subtotal) {
				collection[k] = money[i];
				++k;
				subtotal += money[i];
				break;
			}
	}
	return collection;
}

int main(int argc, char** args) {
	// Task 01
	char* mystring = "Test String";
	printf("String: \"%s\" has Hash: %d\n", mystring, simpleHashSum(mystring));
	
	// Task 02
	int money[] = {50, 10, 5, 2, 1};
	int size = 5;
	int* collection = exchange(money, size, 98);
	int i = 0;
	int sum = 0;
	while (collection[i] != 0 && i < ARSIZE) {
		printf("%d ", collection[i]);
		sum += collection[i];
		++i;
	}
	printf("\nCollection sum: %d\n", sum);
	return EXIT_SUCCESS;
}
