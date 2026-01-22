#include <stdio.h>
#include <string.h>
#include "display.h"

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
    printf("Highest %%: %.2f\n", max);
    printf("Lowest %%: %.2f\n", min);
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