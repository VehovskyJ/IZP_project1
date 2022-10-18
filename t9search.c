#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char t9[10][5] = { "0",    "1",    "2abc",  "3def", "4ghi", "5jkl", "6mno", "7pqrs", "8tuv", "9wxyz" };

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

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        return 0;
    } else if (argc < 2) {
        // TODO: Print all contacts
    }

    // Checks if the first argument is a number
    if (!isNumber(argv[1])) {
        fprintf(stderr, "Search query is not a valid number\n");
        return 0;
    }

    char c, line[203], name[101], number[101];
    int index = 0, switcher = 0;
    while ((c = getchar()) != EOF) {
        // TODO: if number is not numbers ignore???
        if (switcher % 2 == 0){
            if (index < 101) {
                name[index++] = toLowerCase(c);
            } else {
                name[100] = '\n';
            }
        } else {
            if (index < 101) {
                number[index++] = c;
            } else {
                number[100] = '\n';
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
                strcpy(line, name);
                strcat(line, ", ");
                strcat(line, number);
                printf("%s", line);
                memset(name, 0, 101);
                memset(number, 0, 101);
                memset(line, 0, 101);
            }
            index = 0;
            switcher++;

        }
    }

    return 0;
}
