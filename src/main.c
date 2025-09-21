#include <stdio.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");
    char src[] = "Hello";
    char dest[50];

    printf("Length of '%s': %d\n", src, mystrlen(src));
    mystrcpy(dest, src);
    printf("Copied string: %s\n", dest);

    mystrcat(dest, " World");
    printf("Concatenated string: %s\n", dest);

    printf("\n--- Testing File Functions ---\n");
    FILE* f = fopen("test.txt", "r");
    if (f) {
        int lines, words, chars;
        if (wordCount(f, &lines, &words, &chars) == 0) {
            printf("Lines: %d, Words: %d, Chars: %d\n", lines, words, chars);
        }
        fclose(f);
    } else {
        printf("Could not open test.txt for testing.\n");
    }

    return 0;
}
