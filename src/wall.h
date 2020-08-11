#ifndef WALL_H
#define WALL_H

#include "position.h"

#define number_of_walls 10

struct Wall {
    struct Position start;
    struct Position end;
};

// Return a wall with a random start and end position
struct Wall get_random_wall();

#endif