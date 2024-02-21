//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_CELL_H
#define TEST_QT5_CELL_H

typedef unsigned char CellSurround;

#define UPPER_LEFT 0b10000000
#define UPPER_CENTER 0b01000000
#define UPPER_RIGHT 0b00100000
#define LEFT 0b00010000
#define RIGHT 0b00001000
#define LOWER_LEFT 0b00000100
#define LOWER_CENTER 0b00000010
#define LOWER_RIGHT 0b00000001
#define NONE 0

class Cell {

private:
    // Is active at the moment
    bool active{false};

    // Is a valid position
    bool valid{true};

    // Is selected to Print
    bool selected{false};

    int _x, _y;

public:
    [[nodiscard]] bool isActive() const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] bool isSelected();

    bool toggle();

    void setActivation(bool v);

    void setSelected(bool v);

    Cell(bool valid, int x, int y) : valid(valid), _x(x), _y(y) {}

    [[nodiscard]] int x() const { return _x; }

    [[nodiscard]] int y() const { return _y; }

    [[nodiscard]] CellSurround getSurround();
};


#endif //TEST_QT5_CELL_H
