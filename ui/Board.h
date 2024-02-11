//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_BOARD_H
#define TEST_QT5_BOARD_H

#include <vector>
#include "Cell.h"

template<typename T>
using Matrix = std::vector<std::vector<T>>;

class Board {
    Matrix<Cell> board;

};


#endif //TEST_QT5_BOARD_H
