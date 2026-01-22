#include <string.h>
#include <ctype.h>
#include "validation.h"

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

int checkValidMinor(int mark) {
    return (mark >= 0 && mark <= 40);
}

int checkValidMajor(int mark) {
    return (mark >= 0 && mark <= 60);
}
