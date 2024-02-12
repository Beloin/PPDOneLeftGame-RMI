//
// Created by beloin on 11/02/24.
//

#include "Board.h"

Cell &Board::at(int i, int j) {
    return board[i][j];
}

Board::Board(int size) : board(size) {
    for (auto &vec: board) {
        vec = std::vector<Cell>(size);
    }
}
