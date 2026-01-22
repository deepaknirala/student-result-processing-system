#include <stdio.h>
#include "student.h"
#include "validation.h"
#include "calculation.h"
#include "display.h"

#define MAX 100

int main() {
    struct Student students[MAX];
    int count = 0;

    FILE *fp = fopen("students_data.txt", "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    while (count < MAX) {
        struct Student temp;

        if (fscanf(fp, "%s %s", temp.id, temp.name) != 2)
            break;

        if (!checkValidId(temp.id) ||
            checkDuplicateId(students, count, temp.id) ||
            !checkValidName(temp.name)) {
            continue;
        }

        int valid = 1;
        for (int i = 0; i < SUBJECTS; i++) {
            fscanf(fp, "%d %d", &temp.minor[i], &temp.major[i]);
            if (!checkValidMinor(temp.minor[i]) ||!checkValidMajor(temp.major[i])) {
            valid = 0;
            break;
        }

            temp.subjectTotal[i] = temp.minor[i] + temp.major[i];
        }

        if (!valid)
            continue;

        calculateResults(&temp);
        assignGrade(&temp);
        calculateCGPA(&temp);

        students[count++] = temp;
    }

    fclose(fp);

    displayAllStudents(students, count);
    displayStatistics(students, count);
    displayGradeDistribution(students, count);

    return 0;
}
