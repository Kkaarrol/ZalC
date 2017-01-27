#pragma once
typedef enum sortDirection { SORT_ASC, SORT_DESC } sortDirection;
typedef struct Student {
	char	*lastName;
	char	*firstName;
	int		*id;
	float	*grades;
	float	*avg;
} Student;
void sCreate(int count, Student** students) {
	int i;
	for (i = 0; i < count; i++) {
		students[i] = calloc(count, sizeof(Student));
		students[i]->lastName = calloc(30, sizeof(char));
		students[i]->firstName = calloc(20, sizeof(char));
		students[i]->id = calloc(1, sizeof(int));
		students[i]->grades = calloc(5, sizeof(float));
		students[i]->avg = calloc(1, sizeof(float));
	}
}
void sAdd(int* count, Student** students) {
	// dirty little hack
	int c = *count;
	students[c] = calloc(*count, sizeof(Student));
	students[c]->lastName = calloc(30, sizeof(char));
	students[c]->firstName = calloc(20, sizeof(char));
	students[c]->id = calloc(1, sizeof(int));
	students[c]->grades = calloc(5, sizeof(float));
	students[c]->avg = calloc(1, sizeof(float));
	*count += 1;
}
void sDestroy(Student* s) {
	free(s->id);			s->id = NULL;
	free(s->firstName);		s->firstName = NULL;
	free(s->lastName);		s->lastName = NULL;
	free(s->grades);		s->grades = NULL;
	free(s->avg);			s->avg = NULL;
	free(s);				s = NULL;
}
void sRemove(int id, Student** students, int* student_count) {
	sDestroy(students[id]);
	*(student_count)--;
}
void sPrint(Student* s) {
	int i;
	printf("%d - %s %s\n\nGrades:\n", *s->id, s->firstName, s->lastName);
	for (i = 0; i < 5; i++) {
		printf("%.1f\n", s->grades[i]);
	}
	printf("\nAverage: %.2f\n\n", *s->avg);
}
void sSort(int count, Student** students, sortDirection dir) {
	// Sorts a table of Students
	// by the average with the given direction

	// it would also probably make sense
	// to finally learn bubble sort
	// instead of googling all the time

	// temp variables for swapping
	int		t_id;
	char	t_lastName[30];
	char	t_firstName[20];
	double	t_grades[5];
	double	t_avg;

	// Bubble sort
	int i, j, k = 0;
	for (i = 0; i < (count - 1); i++) {
		for (j = 0; j < (count - (i + 1)); j++) {
			if (students[i]->avg > students[i + 1]->avg) {
				// swap a[j] and a[j+1]
				// no fucking idea if this works

				// save students[i] to a temporary set of variables
				t_id = *(students[i]->id);
				strcpy(t_lastName, students[i]->lastName);
				strcpy(t_firstName, students[i]->firstName);
				for (k = 0; k < 5; k++) {
					t_grades[k] = students[i]->grades[k];
				}
				t_avg = *(students[i]->avg);

				// students[i] = students[i + 1]
				*(students[i]->id) = *(students[i + 1]->id);
				strcpy(students[i]->lastName, students[i + 1]->lastName);
				strcpy(students[i]->firstName, students[i + 1]->firstName);
				for (k = 0; k < 5; k++) {
					*(students[i]->grades[k]) = *(students[i + 1]->grades[k]);
				}
				*(students[i]->avg) = *(students[i + 1]->avg);

				// student[i + 1] = temp
				*(students[i + 1]->id) = t_id;
				strcpy(students[i + 1]->lastName, t_lastName);
				strcpy(students[i + 1]->firstName, t_firstName);
				for (k = 0; k < 5; k++) {
					students[i + 1]->grades[k] = t_grades[k];
				}
				*(students[i + 1]->avg) = t_avg;
			}
		}
	}
}
Student sUpdateAverage(Student s) {
	int i = 0;
	*(s.avg) = 0;
	for (i = 0; i < 5; i++) {
		*(s.avg) += s.grades[i];
	}
	*(s.avg) /= 5;
	return s;
}