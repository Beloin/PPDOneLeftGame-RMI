//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_CELL_H
#define TEST_QT5_CELL_H


class Cell {

private:
    bool _isActive{false};

public:
    [[nodiscard]] bool isActive() const;

    bool toggle();

    void setActivation(bool v);

    Cell() : _isActive(false) {}
};


#endif //TEST_QT5_CELL_H
