#include "main.h"

#include <stdlib.h>
#include <time.h>

#include "player.h"
#include "position.h"
#include "render.h"
#include "wall.h"

int main(int argv, char** args) {
    SDL_SetMainReady();
    const double RAY_DENSITY = 1000;
    const double STEP = (double)(1 / RAY_DENSITY);
    struct Player player = {0, 0, 20, 20};
    struct Wall walls[NUMBER_OF_WALLS];
    struct Position previous_position = {0, 0};
    int first_render = 1;
    srand(time(NULL));
    generate_walls(walls);
    initialize();
    while (!has_quit()) {
        const struct Position MOUSE_POSITION = get_mouse_position();
        if ((first_render == 0) &&
            positions_equal(MOUSE_POSITION, previous_position)) {
            continue;
        }
        move(&player, MOUSE_POSITION);
        render_start();
        // Maximum factor is an arbitrary value relative to window dimensions
        render_rays(STEP, (window_width * window_height), walls,
                    MOUSE_POSITION);
        render_player(player);
        render_walls(walls);
        render_end();
        previous_position = MOUSE_POSITION;
        first_render = 0;
    }
    close_render();
}