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
};


#endif //TEST_QT5_CELL_H
