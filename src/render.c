#include "render.h"

#include <SDL2/SDL.h>

#include "player.h"
#include "position.h"
#include "wall.h"

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

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

void render_walls(struct Wall walls[], size_t size) {
    set_color(wall_color);
    for (size_t i = 0; i < size; ++i) {
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

void render_start() {
    set_color(background_color);
    SDL_RenderClear(renderer);
}

inline void render_end() { SDL_RenderPresent(renderer); }

int has_quit() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 1;
        }
    }
    return 0;
}

inline struct Position get_mouse_position() {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    struct Position position = {x, y};
    return position;
}