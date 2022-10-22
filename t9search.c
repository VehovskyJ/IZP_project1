#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int LINE_SIZE = 101;
const int CONTACT_SIZE = 203;
const char dictionary[10][4] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

// Checks if string is a number
int isNumber(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

char toLowerCase(char x) {
    if (x >= 'A' && x <= 'Z') {
        x += 32;
    }
    return x;
}

char charToNum(char c) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < (int)strlen(dictionary[i]); ++j) {
            if (c == dictionary[i][j] && c != ' ') {
                return i + '0';
            }
        }
    }
    return c;
}

int checkMatch(char contact[], char query[]) {
    char temp[strlen(contact)];
    strcpy(temp, contact);

    if (strlen(query) == 0) {
        return 1;
    }

    for (int i = 0; i < (int)strlen(temp); ++i) {
        temp[i] = charToNum(temp[i]);
    }

    if (strstr(temp, query)) {
        memset(temp, 0, strlen(contact));
        return 1;
    }

    memset(temp, 0, strlen(contact));
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        return 0;
    }

    // Checks if the first argument is a number
    if (argc > 1 && !isNumber(argv[1])) {
        fprintf(stderr, "Search query is not a valid number\n");
        return 0;
    }

    char c, contact[CONTACT_SIZE], name[LINE_SIZE], number[LINE_SIZE];
    int index = 0, switcher = 0;
    while ((c = getchar()) != EOF) {
        if (switcher % 2 == 0){
            if (index < LINE_SIZE) {
                name[index++] = toLowerCase(c);
            } else {
                name[LINE_SIZE - 1] = '\n';
            }
        } else {
            if (index < LINE_SIZE) {
                number[index++] = c;
            } else {
                number[LINE_SIZE - 1] = '\n';
            }
        }

        if (c == '\n') {
            if (switcher % 2 != 0){
                if (strlen(name) < 2) {
                    strcpy(name, "[empty]\n");
                } else if (strlen(number) < 2) {
                    strcpy(number, "[empty]\n");
                }

                name[strcspn(name, "\n")] = 0;
                strcpy(contact, name);
                strcat(contact, ", ");
                strcat(contact, number);

                if (checkMatch(contact, argc > 1 ? argv[1] : "\0")) {
                    printf("%s", contact);
                }

                memset(name, 0, LINE_SIZE);
                memset(number, 0, LINE_SIZE);
                memset(contact, 0, CONTACT_SIZE);
            }
            index = 0;
            switcher++;
        }
    }

    return 0;
}

// TODO: Comments
// TODO: Return codes