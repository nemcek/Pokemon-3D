//
// Created by Martin on 6. 12. 2015.
//

#include "src/extensions/Math.hpp"

float Math::random(float min, float max) {
    return ((max - min) * ((float) rand() / (float) RAND_MAX)) + min;
}