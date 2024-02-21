//
// Created by beloin on 11/02/24.
//

#include <utility>
#include "Cell.h"

bool Cell::isActive() const {
    return active;
}

bool Cell::toggle() {
    return active = !active;
}

void Cell::setActivation(bool v) {
    active = v;
}

bool Cell::isValid() const {
    return valid;
}

void Cell::setSelected(bool v) {
    selected = v;
}

bool Cell::isSelected() {
    return selected;
}

// 0 0 X X X 0 0
// 0 0 X X X 0 0
// X X X X X X X
// X X X 0 X X X
// X X X X X X X
// 0 0 X X X 0 0
// 0 0 X X X 0 0
// Y↑ X←
CellSurround Cell::getSurround() {
    std::pair upperLeft{_x - 1, _y + 1};
    std::pair upperCenter{_x, _y + 1};
    std::pair upperRight{_x + 1, _y + 1};

    std::pair left{_x - 1, _y};
    std::pair right{_x + 1, _y};

    std::pair lowerLeft{_x - 1, _y - 1};
    std::pair lowerCenter{_x, _y - 1};
    std::pair lowerRight{_x + 1, _y - 1};

    // 0x1_1_1_1_1_1_1_1:
    // 1 2 3
    // 4 0 5
    // 6 7 8
    CellSurround movement = -1;

    // Validate if position is valid
    if (upperLeft.first <= 0 || upperLeft.second >= 7) movement &= ~UPPER_LEFT;
    if (upperCenter.second >= 7) movement &= ~UPPER_CENTER;
    if (upperRight.first >= 7 || upperRight.second >= 7) movement &= ~UPPER_RIGHT;

    if (left.first <= 0) movement &= ~LEFT;
    if (right.first >= 7) movement &= ~RIGHT;

    if (lowerLeft.first <= 0 || lowerLeft.second <= 0) movement &= ~LOWER_LEFT;
    if (lowerCenter.second <= 0) movement &= ~LOWER_CENTER;
    if (lowerRight.first >= 7 || lowerRight.second <= 0) movement &= ~LOWER_RIGHT;

    return movement;
}
