//
// Created by beloin on 12/02/24.
//

#include "GameUtils.h"

bool isLocationValid(int i, int j) {
    if (i >= 2 && i < 5) {
        return true;
    }

    if (j >= 2 && j < 5) {
        return true;
    }

    return false;
}


// 0 0 X X X 0 0
// 0 0 X X X 0 0
// X X X X X X X
// X X X 0 X X X
// X X X X X X X
// 0 0 X X X 0 0
// 0 0 X X X 0 0
// Y↑ X➔
bool pieceHasMovement(const Board &board, int i, int j) {
    std::pair upperCenter{i, j + 1};
    std::pair upperLeft{i - 1, j + 1};
    std::pair upperRight{i + 1, j + 1};

    std::pair left{i - 1, j};
    std::pair right{i + 1, j};

    std::pair lowerCenter{i, j - 1};
    std::pair lowerLeft{i - 1, j - 1};
    std::pair lowerRight{i + 1, j - 1};

    // 0x1_1_1_1_1_1_1_1:
    // 1 2 3
    // 4 0 5
    // 6 7 8
    char movement = -1;
    if (upperLeft.first <= 0 || upperLeft.second >= 7) return false;
    if (upperCenter.second >= 7) return false;
    if (upperRight.first >= 7 || upperLeft.second >= 7) return false;

    if (left.first <= 0) return false;
    if (right.first >= 7) return false;

    if (lowerLeft.first <= 0 || lowerLeft.second <= 0) return false;
    if (lowerCenter.second <= 0) return false;
    if (lowerRight.first >= 7 || lowerRight.second <= 0) return false;


    return true;
}

bool isMovementValid(const Board &board, int fromX, int fromY, int toX, int toY) {}