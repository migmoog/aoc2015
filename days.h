#ifndef DAYS_H
#define DAYS_H

void d1(char *buffer);
void d2(char *input);
void d3(char *input);
void d4(char *input);
void d5(char *input);

void (*day_functions[])(char *) = {NULL, d1, d2, d3, d4, d5};
void run_day(int day_index, char *buffer) {
    day_functions[day_index](buffer);
}

#endif