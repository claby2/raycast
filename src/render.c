#include "render.h"

#include <SDL2/SDL.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "player.h"
#include "position.h"
#include "wall.h"

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

const double TWO_PI = 2 * M_PI;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
int window_width = 640;
int window_height = 480;

const struct Color PLAYER_COLOR = {255, 0, 0, 255};
const struct Color WALL_COLOR = {255, 255, 255, 255};
const struct Color RAY_COLOR = {32, 32, 32, 255};
const struct Color BACKGROUND_COLOR = {0, 0, 0, 255};

void set_color(const struct Color color) {
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue,
                           color.alpha);
}

void initialize(void) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_ShowCursor(SDL_DISABLE);
    window = SDL_CreateWindow(
        "raycast", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        window_width, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void close_render(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}

void render_player(const struct Player player) {
    set_color(PLAYER_COLOR);
    SDL_Rect rect = {player.position.x, player.position.y, player.width,
                     player.height};
    SDL_RenderDrawRect(renderer, &rect);
}

void render_walls(struct Wall walls[]) {
    set_color(WALL_COLOR);
    for (size_t i = 0; i < NUMBER_OF_WALLS; ++i) {
        struct Wall wall = walls[i];
        SDL_RenderDrawLine(renderer, wall.start.x, wall.start.y, wall.end.x,
                           wall.end.y);
    }
}

void render_ray(const struct Position position1,
                const struct Position position2) {
    set_color(RAY_COLOR);
    SDL_RenderDrawLine(renderer, position1.x, position1.y, position2.x,
                       position2.y);
}

void render_rays(const double step, const double maximum_factor,
                 struct Wall walls[], struct Position mouse) {
    for (double i = 0; i < TWO_PI; i += step) {
        // Calculate relative end position, the position where the ray would
        // end if no intersections were detected
        struct DoublePosition end = {cos(i) * maximum_factor,
                                     sin(i) * maximum_factor};
        for (int j = 0; j < NUMBER_OF_WALLS; ++j) {
            // For each wall, find intersection of two lines given two
            // points on each line
            struct Wall wall = walls[j];
            const double denominator =
                (double)((mouse.x - end.x) * (wall.start.y - wall.end.y)) -
                ((mouse.y - end.y) * (wall.start.x - wall.end.x));
            if (denominator == 0) {
                // The two lines are parallel or coincident
                continue;
            }
            const double t =
                ((mouse.x - wall.start.x) * (wall.start.y - wall.end.y) -
                 (mouse.y - wall.start.y) * (wall.start.x - wall.end.x)) /
                denominator;
            const double u = -1 *
                             ((mouse.x - end.x) * (mouse.y - wall.start.y) -
                              (mouse.y - end.y) * (mouse.x - wall.start.x)) /
                             denominator;
            if ((t > 0) && (t < 1) && (u > 0) && (u < 1)) {
                // Lines intersect, calculate and update end point to be
                // equal to intersection point
                end.x = mouse.x + t * (end.x - mouse.x);
                end.y = mouse.y + t * (end.y - mouse.y);
            }
        }
        // Set line end to integer position for renderering
        struct Position line_end = {(int)end.x, (int)end.y};
        render_ray(mouse, line_end);
    }
}

void render_start(void) {
    set_color(BACKGROUND_COLOR);
    SDL_RenderClear(renderer);
}

inline void render_end(void) { SDL_RenderPresent(renderer); }

const int has_quit(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 1;
        }
    }
    return 0;
}

inline const struct Position get_mouse_position(void) {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    struct Position position = {x, y};
    return position;
}
