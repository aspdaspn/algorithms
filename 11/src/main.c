#include "main.h"

// Maximal length of the string to process
#define STRSIZE 80

// Number of characters in the Alphabet
#define ALPHABET 26

// ASCII Codes
#define UP_A 65
#define LOW_A 97
#define SPACE 32

// ASCII transformation, conditions
#define IS_UP(l) ((UP_A <= l) && (l < (UP_A + ALPHABET)))
#define IS_LOW(l) ((LOW_A <= l) && (l < (LOW_A + ALPHABET)))
#define IS_IN_RANGE(l) ((IS_UP(l)) || (IS_LOW(l)))
#define LOW_2_UP(l) (l - (LOW_A - UP_A))

char output[STRSIZE] = { 0 };

void clearString(char* in, int size) {
	for (int i = 0; i < size; ++i)
		output[i] = 0;
}

char* caesar(char* in, int key, bool encrypt) {
	if (key < 0)
		key = ALPHABET + key;

	if (!encrypt)
		key = ALPHABET - key;

	int i = 0;
	int o = 0;

	while (in[i] != '\0' && i < STRSIZE) {
		if (IS_IN_RANGE((int) in[i])) {
			if (IS_LOW((int) in[i])) 
				output[o] = LOW_2_UP((int) in[i]);
			else
				output[o] = in[i];
			output[o] = ((output[o] - UP_A) + key) % (ALPHABET) + UP_A;
			++o;
		}
		++i;
	}
	output[o] = '\0';
	return output;
}

char* shuffle(char* in, int key, bool encrypt) {
	if (key < 0)
		key = -key;
	
	int i = 0;
	int o = 0;
	int size = 0;
	int temp[STRSIZE] = { 0 };

	while (in[i] != '\0' && i < STRSIZE) {
		temp[i] = in[i];
		++i;
		++size;
	}

	if (size / key * key < size) {
		size = size / key * key + key;
		while (i < size) {
			temp[i] = SPACE;
			++i;
		}
	}
	
	for (int i = 0; i < size; ++i)
		output[i] = temp[i];
	++i;
	output[i] = '\0';
	printf("%d\n", size);
	return output;
}



int main(int argc, char** args) {
	// Task 1
	char cipher1[] = {'a','A','b','B',' ','-','.','1','y','Y','z','Z'};
	char* out1 = caesar(cipher1, 3, true);
	printf("%s\n", out1);
	char* decrypt1 = caesar(out1, 3, false);
	printf("%s\n", decrypt1);
	
	// Task 2
	char* cipher2 = "this is the secret message";
	char* decrypt2 = shuffle(cipher2, 4, true);
	printf("%s\n", decrypt2);
	return EXIT_SUCCESS;
}
