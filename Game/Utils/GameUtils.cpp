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
bool pieceHasMovement(Board &board, int i, int j) {
    CellSurround movement = board.at(i, j).getSurround();
    if (movement == NONE) return false;

    if (movement & UPPER_CENTER) {
        int x = i;
        int y = j + 1;
        CellSurround upperSurround = board.at(x, y).getSurround();

        if (upperSurround & UPPER_CENTER) {
            Cell &upperCell = board.at(x, y + 1);
            if (upperCell.isValid() && !upperCell.isActive())
                return true;
        }
    }

    if (movement & LEFT) {
        int x = i - 1;
        int y = j;
        CellSurround upperSurround = board.at(x, y).getSurround();

        // Cell needs to be "empty" and valid
        if (upperSurround & LEFT) {
            Cell &upperCell = board.at(x - 1, y);
            if (upperCell.isValid() && !upperCell.isActive())
                return true;
        }
    }

    if (movement & RIGHT) {
        int x = i + 1;
        int y = j;
        CellSurround upperSurround = board.at(x, y).getSurround();

        // Cell needs to be "empty" and valid
        if (upperSurround & RIGHT) {
            Cell &upperCell = board.at(x + 1, y);
            if (upperCell.isValid() && !upperCell.isActive())
                return true;
        }
    }

    if (movement & LOWER_CENTER) {
        int x = i;
        int y = j - 1;
        CellSurround upperSurround = board.at(x, y).getSurround();

        // Cell needs to be "empty" and valid
        if (upperSurround & LOWER_CENTER) {
            Cell &upperCell = board.at(x, y - 1);
            if (upperCell.isValid() && !upperCell.isActive())
                return true;
        }
    }

    return false;
}

bool isMovementValid(const Board &board, int fromX, int fromY, int toX, int toY) {}