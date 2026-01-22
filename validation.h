#ifndef VALIDATION_H
#define VALIDATION_H

#include "student.h"

int checkValidId(char id[]);
int checkDuplicateId(struct Student s[], int count, char id[]);
int checkValidName(char name[]);
int checkValidMinor(int mark);
int checkValidMajor(int mark);

#endif
