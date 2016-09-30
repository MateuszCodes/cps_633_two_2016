#define INPUT_BUFFER_SIZE 256
#include <stdio.h>
#include <string.h>
#include "Hill.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
			printf("File Error\n");
			return 1;
	}a
	FILE *f = fopen(argv[1], "r+");
	printf("%s\n", argv[1]);
	if (f == NULL) {
			printf("File Error\n");
			return 1;
	}
	
	char inbuffer[INPUT_BUFFER_SIZE]; //this is not secure
	fgets(inbuffer, INPUT_BUFFER_SIZE, stdin);
	







//	fprintf(f, "wew");
//	fclose(f);

	return 0;
}

