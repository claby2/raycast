#ifndef WALL_H
#define WALL_H

#include "position.h"

#define NUMBER_OF_WALLS 10

struct Wall {
    struct Position start;
    struct Position end;
};

// Return a wall with a random start and end position
const struct Wall get_random_wall(void);

void generate_walls(struct Wall *walls);

#endif
