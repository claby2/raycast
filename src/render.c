#include "render.h"

#include <SDL2/SDL.h>
#include <math.h>
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

const float TWO_PI = 2 * M_PI;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
int window_width = 640;
int window_height = 480;

struct Color player_color = {255, 0, 0, 255};
struct Color wall_color = {255, 255, 255, 255};
struct Color ray_color = {32, 32, 32, 255};
struct Color background_color = {0, 0, 0, 255};

void set_color(struct Color color) {
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue,
                           color.alpha);
}

void initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_ShowCursor(SDL_DISABLE);
    window = SDL_CreateWindow("raycast", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, window_width,
                              window_height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}

void render_player(struct Player player) {
    set_color(player_color);
    SDL_Rect rect = {player.position.x, player.position.y, player.width,
                     player.height};
    SDL_RenderDrawRect(renderer, &rect);
}

void render_walls(struct Wall walls[]) {
    set_color(wall_color);
    for (size_t i = 0; i < number_of_walls; ++i) {
        struct Wall wall = walls[i];
        SDL_RenderDrawLine(renderer, wall.start.x, wall.start.y, wall.end.x,
                           wall.end.y);
    }
}

void render_ray(struct Position position1, struct Position position2) {
    set_color(ray_color);
    SDL_RenderDrawLine(renderer, position1.x, position1.y, position2.x,
                       position2.y);
}

void render_rays(const float step, const float maximum_factor,
                 struct Wall walls[], struct Position mouse) {
    for (float i = 0; i < TWO_PI; i += step) {
        // Calculate relative end position, the position where the ray would
        // end if no intersections were detected
        struct FloatPosition end = {cos(i) * maximum_factor,
                                    sin(i) * maximum_factor};
        for (int j = 0; j < number_of_walls; ++j) {
            // For each wall, find intersection of two lines given two
            // points on each line
            struct Wall wall = walls[j];
            const float denominator =
                (float)((mouse.x - end.x) * (wall.start.y - wall.end.y)) -
                ((mouse.y - end.y) * (wall.start.x - wall.end.x));
            if (denominator == 0) {
                // The two lines are parallel or coincident
                continue;
            }
            const float t =
                ((mouse.x - wall.start.x) * (wall.start.y - wall.end.y) -
                 (mouse.y - wall.start.y) * (wall.start.x - wall.end.x)) /
                denominator;
            const float u = -1 *
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

void render_start() {
    set_color(background_color);
    SDL_RenderClear(renderer);
}

inline void render_end() { SDL_RenderPresent(renderer); }

const int has_quit() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 1;
        }
    }
    return 0;
}

inline const struct Position get_mouse_position() {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    struct Position position = {x, y};
    return position;
}