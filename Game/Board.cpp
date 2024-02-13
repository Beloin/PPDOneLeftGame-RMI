//
// Created by beloin on 11/02/24.
//

#include "Board.h"
#include "Utils/GameUtils.h"

Cell &Board::at(int i, int j) {
    return board[i][j];
}

//Board::Board(int size) : board(size) {
//    for (auto &vec: board) {
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
