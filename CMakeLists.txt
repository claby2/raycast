project(raycast C)
cmake_minimum_required(VERSION 3.10)

set(SourcesList "src/player.c" "src/position.c" "src/render.c" "src/wall.c")

link_libraries(SDL2 SDL2main m)
add_executable(raycast src/main.c ${SourcesList})
add_executable(raycast_test test/raycast_test.c ${SourcesList})