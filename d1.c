#include <stdio.h>
#include <assert.h>

// day one, santa jumping up and down floors
void d1(char *buffer) {
    int floor = 0;
    int basement_index = -1;
    for (int i = 0; buffer[i] != '\0'; i++) {
        char instruction = buffer[i];
        assert(instruction == '(' || instruction == ')'); // no bad inputs

        if (instruction == '(') floor++;
        else if (instruction == ')') floor--;
        if (basement_index < 0 && floor == -1) basement_index = i + 1;
    }
    printf("Day 1 part 1: %d\n", floor);
    printf("Day 1 part 2: %d\n", basement_index);
}