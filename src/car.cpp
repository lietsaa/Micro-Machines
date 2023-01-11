#include "car.hpp"

float Car::getSpeed() {
    return speed;
}

float Car::getAngle() {
    return angle;
}


void Car::move() {
    x += sin(getAngle()) * getSpeed();
    y -= cos(getAngle()) * getSpeed();
}
