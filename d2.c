#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/param.h>

typedef struct
{
    int l;
    int w;
    int h;
} Dim; // dimensions of a box

int surface_area(Dim d)
{
    int lw = d.l * d.w, 
        wh = d.w * d.h, 
        lh = d.l * d.h;
    int box = 2 * lw + 2 * wh + 2 * lh;
    
    return box + MIN(MIN(lw, wh), lh);
}

int compar(const void *a, const void *b) {
    return *((int *)(a)) - *((int *)(b));
}

int ribbon_feet(Dim d) {
    int sides[3] = {d.l, d.w, d.h};
    qsort(sides, 3, sizeof(int), compar);

    return 2 * sides[0] + 2 * sides[1] + (d.l * d.w * d.h);
}

int is_end_dim(Dim d)
{
    return d.h < 0 && d.l < 0 && d.w < 0;
}

/**
 * input: string to parse into dim
 * start: beginning of the string for us to read
 * end: index of the newline or \0 so we know where to stop
 */
Dim parse_dim(char *input, int start, int end)
{
    char minibuf[3];
    int minibuf_index = 0;
    int l, w, h;
    int *properties[3] = {&l, &w, &h};
    int prop_index = 0;

    for (int i = start; i <= end; i++)
    {
        char current = input[i];
        if (current == 'x' || current == '\n' || current == '\0') // valid ending characters
        {
            minibuf[minibuf_index+1] = '\0';
            minibuf_index = 0;
            *properties[prop_index++] = atoi(minibuf); // this will piss someone off lol

            // clear minibuf into all null terminators
            for (int i = 0; i < 3; i++) {
                minibuf[i] = '\0';
            }
            continue;
        }

        minibuf[minibuf_index++] = current;
    }

    assert(prop_index == 3);

    return (Dim) {l,w,h};
}

Dim *parse_dimensions(char *input)
{
    size_t capacity = 4;
    size_t dims_count = 0;
    Dim *result = malloc(sizeof(Dim) * capacity);
    int start = 0, end;
    int finished_parse = 0; // set true when we find the null terminator
    for (int i = 0; !finished_parse; i++)
    {
        finished_parse = input[i] == '\0';
        if (input[i] == '\n' || finished_parse) {
            end = i;

            if (dims_count == capacity) {
                capacity *= 2;
                Dim *new_result = realloc(result, sizeof(Dim) * capacity);
                result = new_result;
            }
            result[dims_count++] = parse_dim(input, start, end);
            start = end + 1;
        }
    }

    result[dims_count] = (Dim){-1, -1, -1}; // fake end dimensions to mark end of array

    return result;
}

void d2(char *input)
{
    Dim *dim_list = parse_dimensions(input);

    int total = 0;
    int total2 = 0;
    for (int i = 0; !is_end_dim(dim_list[i]); i++) {
        total += surface_area(dim_list[i]);
        total2 += ribbon_feet(dim_list[i]);
    }

    free(dim_list);

    printf("Day 2 part 1: %d\n", total);
    printf("Day 2 part 2: %d\n", total2);
}