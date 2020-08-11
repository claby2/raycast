#include "position.h"

inline const int positions_equal(const struct Position position1,
                                 const struct Position position2) {
    return ((position1.x == position2.x) && (position1.y == position2.y));
}