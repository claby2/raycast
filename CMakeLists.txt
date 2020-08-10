project(raycast C)
cmake_minimum_required(VERSION 3.10)

link_libraries(SDL2 SDL2main)
add_executable(raycast src/main.c src/player.c src/position.c src/render.c src/wall.c)
