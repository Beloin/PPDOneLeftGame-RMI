//
// Created by beloin on 11/02/24.
//

#include "Cell.h"

bool Cell::isActive() const {
    return active;
}

bool Cell::toggle() {
    return active = !active;
}

void Cell::setActivation(bool v) {
    active = v;
}

bool Cell::isValid() const {
    return valid;
}

void Cell::setSelected(bool v) {
    selected = v;
}

bool Cell::isSelected() {
    return selected;
}
