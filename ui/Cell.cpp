//
// Created by beloin on 11/02/24.
//

#include "Cell.h"

bool Cell::isActive() const {
    return _isActive;
}

bool Cell::toggle() {
    return _isActive = !_isActive;
}

void Cell::setActivation(bool v) {
    _isActive = v;
}
