#include "main.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "player.h"
#include "position.h"
#include "render.h"
#include "wall.h"

#define number_of_walls 10

const float TWO_PI = 2 * M_PI;
const float ray_density = 1000;
struct Player player = {0, 0, 20, 20};
struct Wall walls[number_of_walls];

void generate_walls() {
    for (size_t i = 0; i < number_of_walls; ++i) {
        walls[i] = get_random_wall();
    }
}

int main(int argv, char** args) {
    srand(time(NULL));
    generate_walls();
    initialize();
    struct Position previous_position = {0, 0};
    int first_render = 1;
    while (!has_quit()) {
        const struct Position mouse_position = get_mouse_position();
        if ((first_render == 0) &&
            positions_equal(mouse_position, previous_position)) {
            continue;
        }
        move(&player, mouse_position);
        render_start();
        const float step = (float)(1 / ray_density);
        // Maximum factor is an arbitrary value
        const float maximum_factor = (window_width * window_height);
        for (float i = 0; i < TWO_PI; i += step) {
            // Calculate relative end position, the position where the ray would
            // end if no intersections were detected
            struct FloatPosition end = {cos(i) * maximum_factor,
                                        sin(i) * maximum_factor};
            for (int j = 0; j < (sizeof(walls) / sizeof(walls[0])); ++j) {
                // For each wall, find intersection of two lines given two
                // points on each line
                struct Wall wall = walls[j];
                const float denominator =
                    (float)((mouse_position.x - end.x) *
                            (wall.start.y - wall.end.y)) -
                    ((mouse_position.y - end.y) * (wall.start.x - wall.end.x));
                if (denominator == 0) {
                    // The two lines are parallel or coincident
                    continue;
                }
                const float t = ((mouse_position.x - wall.start.x) *
                                     (wall.start.y - wall.end.y) -
                                 (mouse_position.y - wall.start.y) *
                                     (wall.start.x - wall.end.x)) /
                                denominator;
                const float u = -1 *
                                ((mouse_position.x - end.x) *
                                     (mouse_position.y - wall.start.y) -
                                 (mouse_position.y - end.y) *
                                     (mouse_position.x - wall.start.x)) /
                                denominator;
                if ((t > 0) && (t < 1) && (u > 0) && (u < 1)) {
                    // Lines intersect, calculate and update end point to be
                    // equal to intersection point
                    end.x = mouse_position.x + t * (end.x - mouse_position.x);
                    end.y = mouse_position.y + t * (end.y - mouse_position.y);
                }
            }
            // Set line end to integer position for renderering
            struct Position line_end = {(int)end.x, (int)end.y};
            render_ray(player.position, line_end);
        }
        render_player(player);
        render_walls(walls, number_of_walls);
        render_end();
        first_render = 0;
    }
    close();
}