#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/player.h"
#include "../src/position.h"
#include "../src/wall.h"

void test_positions_equal() {
    struct Position position1 = {1, 2};
    struct Position position2 = {2, 1};
    assert(positions_equal(position1, position1));
    assert(!(positions_equal(position1, position2)));
}

void test_move() {
    struct Player player = {0, 0};
    struct Position new_position = {2, 2};
    move(&player, new_position);
    assert(positions_equal(player.position, new_position));
}

void test_get_random_wall() {
    struct Wall wall = get_random_wall();
    // Testing randomness with seed 0
    assert(wall.start.x == 38);
    assert(wall.start.y == 23);
    assert(wall.end.x == 85);
    assert(wall.end.y == 32);
}

int main() {
    srand(0);
    test_positions_equal();
    test_move();
    test_get_random_wall();
    printf("Passed");
    return 0;
}