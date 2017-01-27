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
void cleanup(int student_count) {
	int i = 0;
	for (i = 0; i < student_count; i++) {
		sDestroy(studenci[i]);
	}
}
void display(int student_count) {
	int i = 0;
	for (i = 0; i < student_count; i++) {
		sPrint(studenci[i]);
	}
}
void updateAverages(int student_count) {
	int i = 0;
	for (i = 0; i < student_count; i++) {
		*studenci[i] = sUpdateAverage(*studenci[i]);
	}
}
void addFromFile(char* fileName) {

}
void removeFromFile(char* fileName) {

}
void menu(int* count, Student** studenci) {
	// @param count - student count

	// random declarations
	int i = 0;						// generic loop counter
	char option = '\0';				// char - selected menu option
	int option_id = 0;				// ID of student to display
	int option_num = 0;				// number of max/min for high scores

	while (option != 'Z' && option != 'z') {
		// this is nasty
		system("cls");

		// reset option
		fflush(NULL);
		option = '\0';

		// print menu
		system("cls");
		printf("1. [D]odaj studenta\n");
		printf("2. Wyswiet[L] studenta\n");
		printf("3. [W]ydruk studentow\n");
		printf("4. [N]ajlepsi studenci\n");
		printf("5. [P]opraw dane\n");
		printf("6. [Q/Z]akoncz program\n");

		printf("\nWybierz opcje: ");
		scanf("%c", &option);

		switch (option) {
			case 'D': case 'd': {
				// shit happens and you can't declare here
				system("cls");
				int c = *count;
				sAdd(count, studenci);
				printf("Nazwisko: ");
				scanf("%s", studenci[c]->lastName);
				printf("Imie: ");
				scanf("%s", studenci[c]->firstName);
				*(studenci[c]->id) = c + 1;
				i = 0;
				for (i = 0; i < 5; i++) {
					printf("Podaj ocene nr %d: ", i);
					scanf("%f", &(studenci[c]->grades[i]));
				}
				sUpdateAverage(*studenci[c]);
				//sPrint(studenci[count]);
				system("cls");
				break;
			}
			case 'W': case 'w': {
				system("cls");
				display(*count);
				// ... even nastier!
				system("pause");
				break;
			}
			case 'L': case 'l': {
				// reset
				option_id = *count;
				fflush(NULL);
				printf("Podaj numer: ");
				scanf("%d", &option_id);
				if (option_id > *count || option_id < 1)
				while (option_id > *count || option_id < 1) {
					printf("Numer nie istnieje, podaj poprawny numer: ");
					scanf("%d", &option_id);
				}
				system("cls");
				sPrint(studenci[option_id - 1]);
				system("pause");
				break;
			}
			case 'N': case 'n': {
				//system("cls");
				//printf("Podaj liczbe studentow: ");
				//scanf("%d", &option_num);
				system("cls");

				int c = *count;

				// create a new table of students
				// then sort it and remove
				// appropriate number of students
				// from it

				Student** s_high = calloc(c, 1);			// for whatever reason, this works
				sCreate(c, s_high);							// allocate memory
				for (i = 0; i < c; i++) {
					// copy the data
					sSet(s_high[i],
						*(studenci[i]->id),
						studenci[i]->lastName,
						studenci[i]->firstName,
						studenci[i]->grades,
						*(studenci[i]->avg)
					);
				}
				sSort(c, s_high, SORT_DESC);
				//printf("After: \n");
				for (i = 0; i < c; i++) {
					sPrint(s_high[i]);
				}
				system("pause");
				break;
			}
			case 'Z': case 'z': case 'Q': case 'q': {
				break;
			}
			default: {
				break;
			}
		}
	}
}
int main() {
	// show memory leaks before closing
	atexit(dumpMemoryLeaks);

	int* student_count = malloc(sizeof(int));
	*student_count = 0;

	studenci = calloc(2, 1);
	*student_count = loadFromFile("data.bin", studenci);

	if (!studenci) {
		exit(EXIT_FAILURE);
	}
	else {
		menu(student_count, studenci);
		//display(student_count);
		//updateAverages(student_count);
		//display(student_count);
		cleanup(*student_count);
		exit(EXIT_SUCCESS);
	}
}