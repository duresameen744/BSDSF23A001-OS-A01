// File: src/myfilefunctions.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/myfilefunctions.h"

// Count lines, words, chars
int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (!file) return -1;

    *lines = *words = *chars = 0;
    char c;
    int in_word = 0;

    while ((c = fgetc(file)) != EOF) {
        (*chars)++;
        if (c == '\n') (*lines)++;
        if (c == ' ' || c == '\n' || c == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            (*words)++;
        }
    }
    return 0;
}

// Search for string in file
int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (!fp || !search_str) return -1;

    size_t capacity = 10;
    size_t count = 0;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) return -1;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, search_str)) {
            if (count >= capacity) {
                capacity *= 2;
                result = realloc(result, capacity * sizeof(char*));
                if (!result) return -1;
            }
            result[count] = strdup(line);
            count++;
        }
    }
    *matches = result;
    return count;
}
