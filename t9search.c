#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int LINE_SIZE = 101;      // Max length of name and number
const int CONTACT_SIZE = 203;   // Max length of one line [name, number]
const char dictionary[10][4] = {"+", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}; // T9 dictionary

// isNumber checks if string 'str' is a number. Returns true or false
int isNumber(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// toLowerCase converts character 'x' to lowercase
char toLowerCase(char x) {
    return (x >= 'A' && x <= 'Z') ? x += 32 : x;
}

// charToNum converts character 'c' into a corresponding number from t9 dictionary
char charToNum(char c) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (c == dictionary[i][j] && c != ' ') {
                return i + '0';
            }
        }
    }
    return c;
}

// checkMatch checks if contact 'contact' matches search query 'query'. Returns true or false
int checkMatch(char contact[], char query[]) {
    // Creates temporary variable and stores value of 'contact' in it
    char temp[strlen(contact)];
    strcpy(temp, contact);

    // If no query was provided prints out all contacts
    if (strlen(query) == 0) {
        return 1;
    }

    // Converts contact 'temp' into numbers
    for (int i = 0; i < (int)strlen(temp); ++i) {
        temp[i] = charToNum(temp[i]);
    }

    // Checks for match and returns true if match is found
    if (strstr(temp, query)) {
        memset(temp, 0, strlen(contact));
        return 1;
    }

    memset(temp, 0, strlen(contact));
    return 0;
}

int main(int argc, char *argv[]) {
    // Verifies correctness of arguments
    // Checks for too many arguments and if search query is a number
    if (argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        return EXIT_FAILURE;
    } else if (argc > 1 && !isNumber(argv[1])) {
        fprintf(stderr, "Search query is not a valid number\n");
        return EXIT_FAILURE;
    }

    char c, contact[CONTACT_SIZE], name[LINE_SIZE], number[LINE_SIZE];
    memset(name, 0, LINE_SIZE);
    memset(number, 0, LINE_SIZE);
    memset(contact, 0, CONTACT_SIZE);
    int index = 0, switcher = 0, found = 0;
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
                if (name[0] != '\n' && number[0] != '\n') {
                    name[strcspn(name, "\n")] = 0;
                    strcat(contact, name);
                    strcat(contact, ", ");
                    strcat(contact, number);

                    if (checkMatch(contact, argc > 1 ? argv[1] : "\0")) {
                        found++;
                        printf("%s", contact);
                    }
                }
                memset(name, 0, LINE_SIZE);
                memset(number, 0, LINE_SIZE);
                memset(contact, 0, CONTACT_SIZE);
            }
            index = 0;
            switcher++;
        }
    }

    // If no contacts were found prints "Not found"
    if (found == 0) {
        printf("Not found\n");
    }

    return EXIT_SUCCESS;
}
