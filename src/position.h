#ifndef POSITION_H
#define POSITION_H

struct Position {
    int x;
    int y;
};

struct FloatPosition {
    float x;
    float y;
};

// Check if the two given positions are equal
int positions_equal(struct Position position1, struct Position position2);

#endif