#include "wall.h"

#include <stdlib.h>

#include "render.h"

struct Wall get_random_wall() {
    // Get maximum position values from window dimensions
    int maximum_x = window_width + 1;
    int maximum_y = window_height + 1;
    struct Wall wall;
    // Set a random position for wall start and end positions
    wall.start.x = (rand() % maximum_x);
    wall.start.y = (rand() % maximum_y);
    wall.end.x = (rand() % maximum_x);
    wall.end.y = (rand() % maximum_y);
    return wall;
}