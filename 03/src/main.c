#include <main.h>

// 1. Реализовать функцию перевода из десятичной системы в двоичную, используя рекурсию.
int dec2Bin(int dec) {
	if (dec == 0)
		return 0;
	else
		return (dec % 2 + 10 * dec2Bin(dec / 2));
}

// 2. Реализовать функцию возведения числа a в степень b:
// рекурсивно;
long powRecurs(int a, int b) {
	if (b == 1)
		return a;
	else
		return (a * powRecurs(a, --b));
}

// 3. рекурсивно, используя свойство четности степени.
long quickPowRecurs(int a, int b) {
	if (b == 1)
		return a;
	if (b % 2)
		return (a * quickPowRecurs(a, --b));
	else {
		long t = quickPowRecurs(a, b / 2);
		return t * t;
	}
}

int main(int argc, char** args) {
	int dec = 137;
	printf("Decimal: %d, Binary: %d\n", dec, dec2Bin(dec));
	int base = 2;
	int exp = 10;
	printf("%d ^ %d = %ld\n", base, exp, powRecurs(base, exp));
	printf("%d ^ %d = %ld\n", base, exp, quickPowRecurs(base, exp));
	
	return SUCCESS;
}
