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

    char c, line[101];
    int index = 0;
    while ((c = getchar()) != EOF) {
        // TODO: join into one line
        // TODO: if number is not numbers ignore???
        if (index < 101) {
            line[index++] = toLowerCase(c);
        } else {
            line[100] = '\n';
        }

        if (c == '\n') {
            if (strlen(line) < 2) {
                strcpy(line, "[empty]\n");
            }
            printf("%s", line);
            index = 0;
            memset(line, 0, 101);
        }
    }

    return 0;
}
