//
// Created by beloin on 12/02/24.
//

#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>
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
// Y X←?
// TODO: WTF? Why X is coming through RIGHT->LEFT
// TODO: WTF? Why Y is coming through BOOTOM->TOP
//  Fix this!
bool pieceHasMovement(Board &board, int i, int j) {
    Cell &cell = board.at(i, j);
    if (!cell.isValid()) return false;

    CellSurround movement = cell.getSurround();
    if (movement == NONE) return false;

    if (movement & UPPER_CENTER) {
        int x = i;
        int y = j + 1;
        Cell &toUp = board.at(x, y);
        if (toUp.isValid() && toUp.isActive()) {

            CellSurround upperSurround = toUp.getSurround();
            if (upperSurround & UPPER_CENTER) {
                Cell &upperCell = board.at(x, y + 1);
                if (upperCell.isValid() && !upperCell.isActive())
                    return true;
            }

        }
    }

    if (movement & LEFT) {
        int x = i + 1;
        int y = j;
        Cell &toLeft = board.at(x, y);

        if (toLeft.isValid() && toLeft.isActive()) {

            CellSurround leftSurround = toLeft.getSurround();
            // Cell needs to be "empty" and valid
            if (leftSurround & LEFT) {
                Cell &upperCell = board.at(x + 1, y);
                if (upperCell.isValid() && !upperCell.isActive())
                    return true;
            }
        }
    }

    if (movement & RIGHT) {
        int x = i - 1;
        int y = j;
        Cell &toRight = board.at(x, y);
        if (toRight.isValid() && toRight.isActive()) {

            CellSurround rightSurround = toRight.getSurround();
            // Cell needs to be "empty" and valid
            if (rightSurround & RIGHT) {
                Cell &upperCell = board.at(x - 1, y);
                if (upperCell.isValid() && !upperCell.isActive())
                    return true;
            }
        }
    }

    if (movement & LOWER_CENTER) {
        int x = i;
        int y = j - 1;
        Cell &toLower = board.at(x, y);

        if (toLower.isValid() && toLower.isActive()) {
            CellSurround lowerSurround = toLower.getSurround();

            // Cell needs to be "empty" and valid
            if (lowerSurround & LOWER_CENTER) {
                Cell &upperCell = board.at(x, y - 1);
                if (upperCell.isValid() && !upperCell.isActive())
                    return true;
            }
        }
    }

    return false;
}

bool isMovementValid(const Board &board, int fromX, int fromY, int toX, int toY) {}

std::random_device dev;
std::mt19937 rng(dev());

std::string getRandomString(int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);


    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, sizeof(alphanum) - 1);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[dist6(rng)];
    }

    return tmp_s;
}

std::string getTimestamp() {
// get a precise timestamp as a string
    const auto now = std::chrono::system_clock::now();
    const auto nowAsTimeT = std::chrono::system_clock::to_time_t(now);
    const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
    std::stringstream nowSs;
    nowSs << std::put_time(std::localtime(&nowAsTimeT), "%a %b %d %Y %T")
          << '.' << std::setfill('0') << std::setw(3)
          << nowMs.count();

    return nowSs.str();
}