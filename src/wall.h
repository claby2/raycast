#ifndef WALL_H
#define WALL_H

#include "position.h"

struct Wall {
    struct Position start;
    struct Position end;
};

#endif