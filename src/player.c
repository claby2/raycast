#include "player.h"

#include "position.h"

inline void move(struct Player* player, const struct Position position) {
    // Set to position subtracted by half of respective dimension to center
    // player at position
    player->position.x = position.x - (player->width / 2);
    player->position.y = position.y - (player->height / 2);
}
