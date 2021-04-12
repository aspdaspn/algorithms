#include "main.h"

int simpleHashSum(char* in) {
	int out = 0;
	int i = 0;
	while (in[i] != '\0') {
		out += (int) in[i];
		++i;
	}
	return out;
}


int main(int argc, char** args) {
	// Task 01
	char* mystring = "Test String";
		printf("%d\n", simpleHashSum(mystring));
	return EXIT_SUCCESS;
}
