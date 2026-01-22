#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SUBJECTS 5
#define MAX 100

struct Student {
  char id[20];
  char name[50];
  int minor[SUBJECTS];
  int major[SUBJECTS];
  int subjectTotal[SUBJECTS];
  int total;
  float percentage;
  char grade[3];
  float cgpa;
};

int checkValidId(char id[]);
int checkDuplicateId(struct Student s[], int count, char id[]);
int checkValidName(char name[]);
int checkValidMarks(int mark);

void calculateResults(struct Student *s);
void assignGrade(struct Student *s);
void calculateCGPA(struct Student *s);

void displayAllStudents(struct Student students[], int count);
void displayStatistics(struct Student students[], int count);
void displayGradeDistribution(struct Student students[], int count);

int main() {
    struct Student students[MAX];
    int count = 0;

    FILE *fp = fopen("students_data.txt", "r");
    if (fp == NULL) {
        printf("Unable to open students_data.txt\n");
        return 1;
    }

    while (count < MAX) {
        struct Student temp;

        if (fscanf(fp, "%s %s", temp.id, temp.name) != 2)
            break;


        if (!checkValidId(temp.id)) {
            char skip[200];
            fgets(skip, sizeof(skip), fp);
            continue;
        }

        if (checkDuplicateId(students, count, temp.id)) {
            char skip[200];
            fgets(skip, sizeof(skip), fp);
            continue;
        }

        if (!checkValidName(temp.name)) {
            char skip[200];
            fgets(skip, sizeof(skip), fp);
            continue;
        }

        int valid = 1;
        for (int i = 0; i < SUBJECTS; i++) {
            if (fscanf(fp, "%d %d", &temp.minor[i], &temp.major[i]) != 2 ||
                !checkValidMarks(temp.minor[i]) ||
                !checkValidMarks(temp.major[i])) {
                valid = 0;
                break;
            }
            temp.subjectTotal[i] = temp.minor[i] + temp.major[i];
        }

        if (!valid) {
            char skip[200];
            fgets(skip, sizeof(skip), fp);
            continue;
        }

        calculateResults(&temp);
        assignGrade(&temp);
        calculateCGPA(&temp);

        students[count++] = temp;
    }

    fclose(fp);

    if (count == 0) {
        printf("No valid student records found.\n");
        return 0;
    }

    displayAllStudents(students, count);
    displayStatistics(students, count);
    displayGradeDistribution(students, count);

    return 0;
}

int checkValidId(char id[]) {
    for (int i = 0; id[i] != '\0'; i++) {
        if (!isalnum(id[i]))
            return 0;
    }
    return 1;
}

int checkDuplicateId(struct Student s[], int count, char id[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(s[i].id, id) == 0)
            return 1;
    }
    return 0;
}

int checkValidName(char name[]) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]))
            return 0;
    }
    return 1;
}

int checkValidMarks(int mark) {
    return (mark >= 0 && mark <= 100);
}


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

void displayAllStudents(struct Student s[], int n) {
    printf("\nID          Name        Total  %%age   Grade  CGPA\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10s  %-10s  %3d   %6.2f   %-3s   %.1f\n",
               s[i].id, s[i].name, s[i].total,
               s[i].percentage, s[i].grade, s[i].cgpa);
    }
}

void displayStatistics(struct Student s[], int n) {
    float sum = 0, max = s[0].percentage, min = s[0].percentage;

    for (int i = 0; i < n; i++) {
        sum += s[i].percentage;
        if (s[i].percentage > max) max = s[i].percentage;
        if (s[i].percentage < min) min = s[i].percentage;
    }
    printf("\nClass Average: %.2f\n", sum / n);
    printf("Highest %: %.2f\n", max);
    printf("Lowest %: %.2f\n", min);
}

void displayGradeDistribution(struct Student s[], int n) {
    int count[8] = {0};
    char *g[] = {"O","A+","A","B+","B","C","D","F"};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 8; j++)
            if (!strcmp(s[i].grade, g[j]))
                count[j]++;

    printf("\nGrade Distribution:\n");
    for (int i = 0; i < 8; i++)
        printf("%-2s : %d\n", g[i], count[i]);
}