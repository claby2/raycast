#ifndef PLAYER_H
#define PLAYER_H

#include "player.h"
#include "position.h"

struct Player {
    struct Position position;
    int width;
    int height;
};

// Move given player to given position
void move(struct Player* player, struct Position position);

#endif