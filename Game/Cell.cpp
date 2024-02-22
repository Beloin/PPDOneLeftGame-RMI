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
    std::pair _upperRight{_x - 1, _y + 1};
    std::pair upperCenter{_x, _y + 1};
    std::pair upperLeft{_x + 1, _y + 1};

    std::pair _right{_x - 1, _y};
    std::pair left{_x + 1, _y};

    std::pair _lowerRight{_x - 1, _y - 1};
    std::pair lowerCenter{_x, _y - 1};
    std::pair lowerLeft{_x + 1, _y - 1};

    // 0x1_1_1_1_1_1_1_1:
    // 1 2 3
    // 4 0 5
    // 6 7 8
    CellSurround movement = -1;

    // Y↑ X←
    // Example:
    // (1, 4) (0, 4) (-1, 4)
    // (1, 3) (0, 3) (-1, 3)
    // (1, 2) (0, 2) (-1, 2)

    // Validate if position is valid
    if (_upperRight.first < 0 || _upperRight.second >= 7) movement &= ~UPPER_RIGHT;
    if (upperCenter.second >= 7) movement &= ~UPPER_CENTER;
    if (upperLeft.first >= 7 || upperLeft.second >= 7) movement &= ~UPPER_LEFT;

    if (_right.first < 0) movement &= ~RIGHT;
    if (left.first >= 7) movement &= ~LEFT;

    if (_lowerRight.first < 0 || _lowerRight.second < 0) movement &= ~LOWER_RIGHT;
    if (lowerCenter.second < 0) movement &= ~LOWER_CENTER;
    if (lowerLeft.first >= 7 || lowerLeft.second < 0) movement &= ~LOWER_LEFT;

    return movement;
}
