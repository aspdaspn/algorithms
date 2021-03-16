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

// 4. Реализовать нахождение количества маршрутов шахматного короля с препятствиями. (1 - препятствие, 0 - свободно)
#define ROW 8
#define COL 8

const int board[ROW][COL] = 
	{{0, 0, 1, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0},
	 {1, 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0},
	 {0, 0, 0, 0, 0, 1, 0, 0},
	 {0, 0, 0, 0, 0, 0, 0, 0}};

int routes(int x, int y) {
	if (x == 0 && y == 0)
		return 0;
	else if ((x == 0 && y == 1) || (x == 1 && y == 0))
		return (1 && !board[y][x]);
	else if (x == 0 && y > 1)
		return (board[y][x] ? 0 : routes(x, y - 1));
	else if (x > 1 && y == 0)
		return (board[y][x] ? 0 : routes(x - 1, y));
	else
		return (board[y][x] ? 0 : (routes(x, y - 1) + routes(x - 1, y)));
}

int main(int argc, char** args) {
	int dec = 137;
	printf("Decimal: %d, Binary: %d\n", dec, dec2Bin(dec));
	
	int base = 2;
	int exp = 10;
	printf("%d ^ %d = %ld\n", base, exp, powRecurs(base, exp));
	printf("%d ^ %d = %ld\n", base, exp, quickPowRecurs(base, exp));
	
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++)
			printf("%5d", routes(x, y));
		printf("\n");
	}
	return SUCCESS;
}
