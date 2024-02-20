//
// Created by beloin on 12/02/24.
//

#ifndef ONE_LEFT_GAMEUTILS_H
#define ONE_LEFT_GAMEUTILS_H

#include "../Board.h"

bool isLocationValid(int i, int j);

bool pieceHasMovement(const Board &board, int i, int j);

bool isMovementValid(const Board &board, int fromX, int fromY, int toX, int toY);

#endif //ONE_LEFT_GAMEUTILS_H
