#include "main.h"

#include <stdlib.h>
#include <time.h>

#include "player.h"
#include "position.h"
#include "render.h"
#include "wall.h"

const float ray_density = 1000;
const float step = (float)(1 / ray_density);
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
        // Maximum factor is an arbitrary value
        const float maximum_factor = (window_width * window_height);
        render_rays(step, maximum_factor, walls, mouse_position);
        render_player(player);
        render_walls(walls);
        render_end();
        previous_position = mouse_position;
        first_render = 0;
    }
    close();
}