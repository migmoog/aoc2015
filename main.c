#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "days.h"

#define BUF_SIZE 1024
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: <day index>\n");
        return 1;
    }

    int day_index = atoi(argv[1]);


    size_t input_len = 0;
    char *input = NULL;
    char buffer[BUF_SIZE]; // reading from a buffer in chunks
    while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
        size_t len = strlen(buffer);
        char *input_med = (char *) realloc(input, input_len + len + 1);
        input = input_med;
        memcpy(input+input_len, buffer, len + 1);
        input_len += len;
    }

    if (input_len == 0) {
        printf("Nothing in this input to read.\n");
    }
    run_day(day_index, input);
    free(input);

    return 0;
}