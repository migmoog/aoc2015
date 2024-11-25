#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int has_at_least_3_vowels(const char *s) {
    int a = 0, e = 0, i = 0, o = 0, u = 0;
    for (int j = 0; s[j] != '\0'; j++) {
        switch (s[j]) {
        case 'a': a++; break;
        case 'e': e++; break;
        case 'i': i++; break;
        case 'o': o++; break;
        case 'u': u++; break;
        }

        if ((a+e+i+o+u) >= 3)
            return 1;
    }

    return (a+e+i+o+u) >= 3;
}

int has_dual_chars(const char *s)
{
    for (int i = 0; 'a' + i <= 'z'; i++)
    {
        char dual[3] = {'a' + i, 'a' + i, '\0'};
        if (strstr(s, dual) != NULL)
            return 1;
    }

    return 0;
}

int no_naughty_combo(const char *s)
{
    static const char *naughties[4] = {"ab", "cd", "pq", "xy"};
    for (int i = 0; i < 4; i++)
    {
        if (strstr(s, naughties[i]) != NULL)
            return 0;
    }

    return 1;
}

int is_nice(const char *s)
{
    return no_naughty_combo(s) && has_dual_chars(s) && has_at_least_3_vowels(s);
}

void d5(char *input)
{
    int part1 = 0;
    int start = 0;
    int end = 0;
    const size_t len = strlen(input);
    for (int i = 0; i <= len; i++) {
        if (input[i] == '\n' || input[i] == '\0') {
            end = i;
            char *s = strndup(input+start, end-start);
            part1 += is_nice(s);
            free(s);
            start = end+1;
        }
    }

    printf("Day 5 part 1: %d\n", part1);
}