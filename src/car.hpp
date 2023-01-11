#ifndef CAR_CLASS
#define CAR_CLASS
#include <cmath>

class Car {

public:
    Car(int speed_ = 2, int angle_ = 0)
        : speed(speed_), angle(angle_) {}
    float getSpeed();
    float getAngle();
    void move();

    float x;
    float y;
    float speed;
    float angle;
private:

};

#endif
