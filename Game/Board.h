//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_BOARD_H
#define TEST_QT5_BOARD_H

#include <vector>
#include "Cell.h"

template<class T>
using Matrix = std::vector<std::vector<T>>;

class Board {
    Matrix<Cell> board;

public:

//    explicit Board(int size);
    explicit Board();

    Cell &at(int i, int j);

    int size();
};


#endif //TEST_QT5_BOARD_H
