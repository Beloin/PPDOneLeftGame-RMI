//
// Created by beloin on 12/02/24.
//

#include "GameUtils.h"

bool isLocationValid(int i, int j) {
    if (i >= 2 && i < 5) {
        return true;
    }

    if (j >= 2 && j < 5) {
        return true;
    }

    return false;
}
