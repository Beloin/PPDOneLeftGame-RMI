//
// Created by beloin on 11/02/24.
//

#include "Board.h"
#include "Utils/GameUtils.h"

Cell &Board::at(int i, int j) {
    return board[i][j];
}

//Board::Board(int size) : qtBoard(size) {
//    for (auto &vec: qtBoard) {
//        vec = std::vector<Cell>(size);
//        for (int i = 0; i < size; i++) {
//
//        }
//    }
//}

Board::Board() : board(7) {
    int i = 0;
    for (auto &vec: board) {
        for (int j = 0; j < 7; j++) {
            bool args = isLocationValid(i, j);
            vec.emplace_back(args, i, j);
        }

        i++;
    }
}

int Board::size() {
    return board.size();
}

void Board::setup() {

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; j++) {
            if (i == 3 && j == 3) {
                board[3][3].setActivation(false);
                continue;
            }

            board[i][j].setActivation(true);

        }
    }
}

void Board::reset() {
    setup();
}

void Board::move(int fromX, int fromY, int toX, int toY) {
    auto xDiff = fromX - toX;
    auto yDiff = fromY - toY;

    int removedX = fromX;
    int removedY = fromY;
    if (xDiff > 0) {
        removedX = fromX - 1;
    } else if (xDiff < 0) {
        removedX = fromX + 1;
    }

    if (yDiff > 0) {
        removedY = fromY - 1;
    } else if (yDiff < 0) {
        removedY = fromY + 1;
    }

    at(removedX, removedY).setActivation(false);

    at(fromX, fromY).toggle();
    at(toX, toY).toggle();
}

bool Board::isPlayableYet() {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; j++) {
            Cell &cell = at(i, j);

            if (cell.isValid() && cell.isActive()) {
                if (pieceHasMovement(*this, i, j)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::hasMovement(int i, int j) {
    return pieceHasMovement(*this, i, j);
}

bool Board::hasMovement(Cell &cell) {
    return pieceHasMovement(*this, cell.x(), cell.y());
}
