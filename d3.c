#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
} Point;

struct Entry
{
    Point key; // location on the map
    int value; // visits from santa
};

typedef struct
{
    struct Entry *entries;
    int capacity;
    int size;
} Map;

Map *map_new()
{
    Map *out = malloc(sizeof(Map));
    out->capacity = 4;
    out->size = 0;
    out->entries = malloc(sizeof(struct Entry) * out->capacity);

    return out;
}

int *map_get(Map *m, Point key)
{
    for (int i = 0; i < m->size; i++)
    {
        Point p = m->entries[i].key;
        if (p.x == key.x && p.y == key.y)
            return &m->entries[i].value;
    }

    return NULL;
}

// add this point to the map if it doesnt exist
// otherwise just add to the existing point
void map_put(Map *m, Point key)
{
    int *value = map_get(m, key);
    if (value != NULL)
    {
        (*value)++;
        return;
    }

    m->size++;

    if (m->size == m->capacity)
    {
        m->capacity *= 2;
        struct Entry *new_entries = realloc(m->entries, sizeof(struct Entry) * m->capacity);
        m->entries = new_entries;
    }

    m->entries[m->size - 1] = (struct Entry){
        key,
        1};
}

// fuck them kids man
void map_destroy(Map *m)
{
    free(m->entries);
    free(m);
}

void d3(char *input)
{
    Point santa = {0, 0}; // the fat bastard
    Map *neighborhood = map_new();
    map_put(neighborhood, santa);

    // part 2 stuff
    Map *p2 = map_new();
    Point redmen[2] = {santa, santa}; // yay pass by value!
    int ri = 0;
    map_put(p2, redmen[ri]);
    for (int i = 0; input[i] != '\0'; i++)
    {
        switch (input[i])
        {
        case '<':
            santa.x--;
            redmen[ri].x--;
            break;
        case '>':
            santa.x++;
            redmen[ri].x++;
            break;
        case '^':
            santa.y--;
            redmen[ri].y--;
            break;
        case 'v':
        case 'V':
            santa.y++;
            redmen[ri].y++;
            break;
        default:
            printf("Day 3 has invalid character: %c\n", input[i]);
            return;
        }

        map_put(neighborhood, santa);
        map_put(p2, redmen[ri]);

        ri = (ri + 1) % 2; // yay modulo looping!!!!!!!
    }

    printf("Day 3 part 1: %d\n", neighborhood->size);
    printf("Day 3 part 2: %d\n", p2->size);

    map_destroy(neighborhood);
    map_destroy(p2);
}