#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "files.h"
#include "types.h"

FILE *pFile;

bool checkHeader(FILE* pFile) {
	char header[5] = { 0 };
	fread(header, sizeof *header, 4, pFile);
	if (strcmp(header, "ZalC") != 0) {
		printf("Header corrupt in data.bin\n");
		return 0;
	}
	return 1;
}
bool isEOF(FILE* pFile) {
	int c;
	c = fgetc(pFile);
	fseek(pFile, -1, SEEK_CUR);
	return c == EOF;
}
int loadFromFile(char* fileName, Student **s) {
	// student count
	int counter = 0;
	pFile = fopen(fileName, "rb");
	if (!pFile) {
		printf("Error opening %s: %s\n", fileName, strerror(errno));
	}
	else {
		// File loaded successfully
		if (checkHeader(pFile)) {
			// Header is correct
			int i;
			while(1) {
				fseek(pFile, 30 + 20 + 5 + 2, SEEK_CUR); // try to move to the next student
				if (!isEOF(pFile)) counter += 1;		 // are we there yet?
				else break;
			}
			sCreate(counter, s);
			// start from the beginning!
			fseek(pFile, 4, SEEK_SET);
			for (i = 0; i < counter; i++) {
				// load from file
				fread(s[i]->lastName, sizeof(char), 30, pFile);
				fread(s[i]->firstName, sizeof(char), 20, pFile);
				fread(s[i]->id, sizeof(int), 1, pFile);
				fread(s[i]->marks, sizeof(float), 5, pFile);
				fread(s[i]->avg, sizeof(float), 1, pFile);
			}
		}
		fclose(pFile);
		return counter;
	}
}