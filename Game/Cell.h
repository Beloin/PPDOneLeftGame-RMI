//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_CELL_H
#define TEST_QT5_CELL_H


class Cell {

private:
    // Is active at the moment
    bool active{false};

    // Is a valid position
    bool valid{true};

public:
    [[nodiscard]] bool isActive() const;

    [[nodiscard]] bool isValid() const;

    bool toggle();

    void setActivation(bool v);

    Cell() : valid(true) {}

    explicit Cell(bool valid) : valid(valid) {}

};


#endif //TEST_QT5_CELL_H
