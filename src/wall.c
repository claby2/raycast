#include "wall.h"

#include <stddef.h>
#include <stdlib.h>

#include "render.h"

const struct Wall get_random_wall(void) {
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

void generate_walls(struct Wall *walls) {
    for (size_t i = 0; i < NUMBER_OF_WALLS; ++i) {
        walls[i] = get_random_wall();
    }
}
