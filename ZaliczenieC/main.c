#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "types.h"

Student **studenci;

void dumpMemoryLeaks(void) {
	_CrtDumpMemoryLeaks();
}
int main() {
	int student_count = 0;
	studenci = calloc(2, 1);
	student_count = loadFromFile("data.bin", studenci);

	// show memory leaks before closing
	atexit(dumpMemoryLeaks);

	if (!studenci) {
		exit(EXIT_FAILURE);
	}
	else {
		int i;
		for (i = 0; i < student_count; i++) {
			sPrint(studenci[i]);
		}
		for (i = 0; i < student_count; i++) {
			sDestroy(studenci[i]);
		}
		exit(EXIT_SUCCESS);
	}
}