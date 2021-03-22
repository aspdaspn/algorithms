#include <main.h>

bool isPrime(int* value) {
	if (*value == 1)
		return false;
	int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	const int SIZE = sizeof(primes) / sizeof(int);
	
	for (int i = 0; i < SIZE; i++) {
		if (*value == primes[i])
			return true;
		if (!(*value % primes[i]))
			return false;
	}

	for (int i = 2; i < *value; i++)
		if (*value % i == 0)
			return false;
	return true;
}

int main(int argc, char** args) {
	char* input = malloc(11 * sizeof(char));
	int value;
	printf("Check if a number is a Prime\n");
	do {
		printf("Enter positive integer: ");
		fgets(input, 11 * sizeof(char), stdin);
		value = atoi(input);
	} while (value <= 0);
		printf("Your integer is %s\n", isPrime(&value) ? "a Prime" : "not a Prime");
	free(input);
	return SUCCESS;
}
