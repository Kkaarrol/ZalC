#pragma once
typedef struct Student {
	char	*lastName;
	char	*firstName;
	int		*id;
	float	*marks;
	float	*avg;
} Student;
void sCreate(int count, Student **students) {
	int i;
	for (i = 0; i < count; i++) {
		students[i] = calloc(count, sizeof(Student));
		students[i]->lastName = calloc(30, sizeof(char));
		students[i]->firstName = calloc(20, sizeof(char));
		students[i]->id = calloc(1, sizeof(int));
		students[i]->marks = calloc(5, sizeof(float));
		students[i]->avg = calloc(1, sizeof(float));
	}
}
void sDestroy(Student *s) {
	free(s->id);			s->id = NULL;
	free(s->firstName);		s->firstName = NULL;
	free(s->lastName);		s->lastName = NULL;
	free(s->marks);			s->marks = NULL;
	free(s->avg);			s->avg = NULL;
	free(s);				s = NULL;
}
void sPrint(Student *s) {
	int i;
	printf("%d - %s %s\n\nGrades:\n", *s->id, s->firstName, s->lastName);
	for (i = 0; i < 5; i++) {
		printf("%.1f\n", s->marks[i]);
	}
	printf("\nAverage: %.2f\n\n", *s->avg);
}