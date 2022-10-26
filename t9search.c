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
    char temp[CONTACT_SIZE];
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
        memset(temp, 0, CONTACT_SIZE);
        return 1;
    }

    memset(temp, 0, CONTACT_SIZE);
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

    /* Variables
     * 'c'          character obtained from getchar
     * 'contact'    contact composed of name and number [name, number]
     * 'name'       name form even lines
     * 'number'     number from odd lines
     * 'index'      index of a character in line
     * 'oddEven'    number that determines if a line is odd or even
     * 'found'      number of contacts matching query
     * */
    char c, contact[CONTACT_SIZE], name[LINE_SIZE], number[LINE_SIZE];
    int index = 0, oddEven = 0, found = 0;
    while ((c = getchar()) != EOF) {
        // Using 'oddEven' determines if character should be saved into 'name' or 'number'
        // and then using 'index' removes all characters past the line length limit
        // If the line limit is exceeded, '\n' will be copied as the last character, since natural line delimiter is cut off
        // All characters in name are changed to lowercase
        if (oddEven % 2 == 0){
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

        // If 'c' is equal to '\n', 'index' is reset to 0 and 'oddEven' is incremented
        if (c == '\n') {
            // When 'oddEven' returns odd number, both name and number were scanned and are now ready for further processing
            if (oddEven % 2 != 0){
                // If the first character in 'name' or 'number' is '\n', contact is ignored because either name or number is empty
                if (name[0] != '\n' && number[0] != '\n') {
                    // Removes '\n' from name and copies values from name and number into contact in format [name, number]
                    name[strcspn(name, "\n")] = 0;
                    strcpy(contact, name);
                    strcat(contact, ", ");
                    strcat(contact, number);

                    // Checks if the contact matches query from first argument and if no argument was entered prints all contacts
                    if (checkMatch(contact, argc > 1 ? argv[1] : "\0")) {
                        found++;
                        printf("%s", contact);
                    }
                }
                // Resets variables 'name' 'number' and 'contact'
                memset(name, 0, LINE_SIZE);
                memset(number, 0, LINE_SIZE);
                memset(contact, 0, CONTACT_SIZE);
            }
            index = 0;
            oddEven++;
        }
    }

    // If no contacts were found prints "Not found"
    if (found == 0) {
        printf("Not found\n");
    }

    return EXIT_SUCCESS;
}
