#define BUFFER_SIZE 256
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Hill.h"

int passwordPrompt(char* password);
int usernamePrompt(char* password);
int checkCharacters(const char* buffer);

int main(int argc, char *argv[]) {
	if (argc == 1) {
			printf("File Error: No filename entered\n");
			return 1;
	}
	FILE *hashfile = fopen(argv[1], "r+");
	if (hashfile == NULL) {
			printf("File Error: File does not exist\n");
			return 1;
	}
	
	// **alot of ugly C string operations**  //this is not secure
	char linebuffer[BUFFER_SIZE];
	char userbuffer[BUFFER_SIZE];
	char passbuffer[BUFFER_SIZE];
	int notfound = -1, charpointer;

	printf("Using hashtable: %s\n", argv[1]);
	while(usernamePrompt(userbuffer));
	// hash file will be *username* *hash*, space delimited
	// then i guess we try and locate the line with the entered username
	while (fgets(linebuffer, BUFFER_SIZE, hashfile)) { //add case for empty file, empty line, etc
		charpointer = -1;
		while (linebuffer[++charpointer] != ' ');
		notfound = memcmp(linebuffer, userbuffer, charpointer);
		if (!notfound) break;
	}

	if (!notfound) {
		printf("Found\n");	
	} else {
		printf("Not found - creating new user '%s'\n", userbuffer);
		while(passwordPrompt(passbuffer));
		printf("New pass: %s\n", passbuffer);
		//hash it
		E(passbuffer+0,passbuffer+0);
		E(passbuffer+4,passbuffer+4);
		E(passbuffer+8,passbuffer+8);
		//write it
		fprintf(hashfile, "%s %s\n", userbuffer,passbuffer);
	}

	fclose(hashfile);
	return 0;
}

//*************FUNCTIONS**************************
int checkCharacters(const char* buffer) { //0 if ok //check if a string is only numbers and letters
	size_t len = strlen(buffer);
	for (int i=0; i<len; i++) {
			if (!((buffer[i] > 47 && buffer[i] <91) || (buffer[i] > 96 && buffer[i] < 123))) {
				return 1;
			}
	}
	return 0;
}

int passwordPrompt(char* password) { //0 is successful
	printf("Please enter password: "); //get password from user
	fgets(password, BUFFER_SIZE, stdin);
	password[strcspn(password, "\n")] = 0;
	size_t len = strlen(password);
	if (len >= 4 && len <= 12) { //check if password is valid
			if (checkCharacters(password)) {
				printf("Password must be only letters and numbers\n");
				return 1;
			}
	} else {
		printf("Password must be between 4 and 12 characters, inclusive\n");
		return 1;
	}
	for (int i=len; i<12; i++) { //null pads any remaining out of 12 characters
		password[i] = 0;
	}
	return 0;
}

int usernamePrompt(char* username) {
	printf("Please enter username: "); //get username from user
	fgets(username, BUFFER_SIZE, stdin);
	username[strcspn(username, "\n")] = 0;
	size_t len = strlen(username);
	if (!(len >= 4 && len <= 32)) { //check if its valid
		printf("Username must be between 4 and 32 characters, inclusive\n");
		return 1;
	}
	return 0;
}

