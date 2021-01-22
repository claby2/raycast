project(raycast C)
cmake_minimum_required(VERSION 3.10)

set(SourcesList "src/player.c" "src/position.c" "src/render.c" "src/wall.c")

add_executable(raycast src/main.c ${SourcesList})
target_link_libraries(raycast PRIVATE SDL2 SDL2main m)
