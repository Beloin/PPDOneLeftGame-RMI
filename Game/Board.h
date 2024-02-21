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

    Cell &at(int i, int j) ;

    bool hasMovement(int i, int j) ;
    bool hasMovement(Cell&) ;

    int size();

    void reset();

    void setup();

    void move(int i, int i1, int i2, int i3);

    bool isPlayableYet();
};


#endif //TEST_QT5_BOARD_H
