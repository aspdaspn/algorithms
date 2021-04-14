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
	// Preparing the key to be positive
	if (key < 0)
		key = ALPHABET + key;

	// Preparing the key for the decryption
	if (!encrypt)
		key = ALPHABET - key;

	int i = 0;
	int o = 0;

	// Populating the output string with UP-case letters if required
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

	// adding a string terminator for a good
	output[o] = '\0';
	return output;
}

char* shuffle(char* in, int key, bool encrypt) {
	if (key < 0)
		key = -key;
	
	// indexes
	int i = 0;
	int o = 0;
	
	// indicates the starting point for next pass
	int s = 0;
	
	// stores the size of an input
	int size = 0;

	// stores the step variable for encryption routine
	int step = 0;
	
	// a temporary array. We need it because input string can have a wrong size
	int temp[STRSIZE] = { 0 };

	// finding the size of the input string and populating the temp array
	while (in[i] != '\0' && i < STRSIZE) {
		temp[i] = in[i];
		++i;
		++size;
	}

	// If the input size / key is not an integer, increase the input size by adding 
	// spaces at the end of the input
	if (size / key * key < size) {
		size = size / key * key + key;
		while (i < size) {
			temp[i] = SPACE;
			++i;
		}
	}
	
	// Add string termination to the end of the temp array. It is for security.
	temp[i] = '\0';
	
	/* 
	 * Finding the step for encryption of for decryption
	 * -----------
	 * <---step-->
	 * -----------
	 * |1|2|3|4|5| k
	 * |2| | | | | 
	 * |3| | | | | e
	 * |4| | | | | y
	 * -----------
	 */
	if (encrypt)
		step = size / key;
	else
		step = key;

	// Reseting starting index
	i = 0;

	// Populating the output array
	while (o < size) {
		output[o++] = temp[i];
		s++;
		while (i < size - step) {
			i = i + step;
			output[o++] = temp[i];
		}
		i = s;
	}

	// adding a string terminator for a good
	output[o] = '\0';
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
	char* out2 = shuffle(cipher2, 4, true);
	printf("%s\n", out2);
	char* decrypt2 = shuffle(out2, 4, false);
	printf("%s\n", decrypt2);
	char* out3 = "t cshtrsiheasetg   eism s";
	char* decrypt3 = shuffle(out3, 4, false);
	printf("%s\n", decrypt3);
	return EXIT_SUCCESS;
}
