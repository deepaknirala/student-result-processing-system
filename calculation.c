#include <string.h>
#include "calculation.h"

void calculateResults(struct Student *s) {
    s->total = 0;
    for (int i = 0; i < SUBJECTS; i++)
        s->total += s->subjectTotal[i];

    s->percentage = s->total / (float)SUBJECTS;
}

void assignGrade(struct Student *s) {
    float p = s->percentage;

    if (p >= 90) strcpy(s->grade, "O");
    else if (p >= 85) strcpy(s->grade, "A+");
    else if (p >= 75) strcpy(s->grade, "A");
    else if (p >= 65) strcpy(s->grade, "B+");
    else if (p >= 60) strcpy(s->grade, "B");
    else if (p >= 55) strcpy(s->grade, "C");
    else if (p >= 50) strcpy(s->grade, "D");
    else strcpy(s->grade, "F");
}

void calculateCGPA(struct Student *s) {
    if (!strcmp(s->grade, "O")) s->cgpa = 10;
    else if (!strcmp(s->grade, "A+")) s->cgpa = 9;
    else if (!strcmp(s->grade, "A")) s->cgpa = 8;
    else if (!strcmp(s->grade, "B+")) s->cgpa = 7;
    else if (!strcmp(s->grade, "B")) s->cgpa = 6;
    else if (!strcmp(s->grade, "C")) s->cgpa = 5;
    else if (!strcmp(s->grade, "D")) s->cgpa = 4;
    else s->cgpa = 0;
}