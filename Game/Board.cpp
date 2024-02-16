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
            vec.emplace_back(args);
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
