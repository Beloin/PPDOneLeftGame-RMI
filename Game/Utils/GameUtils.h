//
// Created by beloin on 12/02/24.
//

#ifndef ONE_LEFT_GAMEUTILS_H
#define ONE_LEFT_GAMEUTILS_H

#include "../Board.h"

#define UPPER_LEFT 0b10000000
#define UPPER_CENTER 0b01000000
#define UPPER_RIGHT 0b00100000
#define LEFT 0b00010000
#define RIGHT 0b00001000
#define LOWER_LEFT 0b00000100
#define LOWER_CENTER 0b00000010
#define LOWER_RIGHT 0b00000001
#define NONE 0

bool isLocationValid(int i, int j);

bool pieceHasMovement(Board &board, int i, int j);
bool pieceHasMovement(Board &board, Cell &cell);

bool isMovementValid(const Board &board, int fromX, int fromY, int toX, int toY);

#include <ctime>
#include <iostream>
#include <unistd.h>

std::string getRandomString(int len);

std::string getTimestamp();

#endif //ONE_LEFT_GAMEUTILS_H
