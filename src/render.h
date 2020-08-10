#ifndef RENDER_HPP
#define RENDER_HPP

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

#include "player.h"
#include "position.h"
#include "wall.h"

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern int window_width;
extern int window_height;

// Initialize SDL2 window and renderer
void initialize();

// Close SDL2 window and renderer
void close();

void render_player(struct Player player);

void render_walls(struct Wall walls[], size_t size);

void render_ray(struct Position position1, struct Position position2);

// Render background and clear screen
void render_start();

// Present renderer
void render_end();

int has_quit();

struct Position get_mouse_position();
#endif