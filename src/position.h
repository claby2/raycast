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
const int positions_equal(const struct Position position1,
                          const struct Position position2);

#endif