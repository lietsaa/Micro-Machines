#include "car.hpp"

void Car::Draw() {}
void Car::Sound() {}
void Car::Update() {}
void Car::Accelerate() {}
void Car::Decelerate() {}
void Car::TurnRight() {}
void Car::TurnLeft() {}
void Car::ReceiveItem(Item &item) { items_.push_back(item); }
void Car::UseItem() {
  if (items_.begin() != items_.end()) {
    items_[0].Use();
  }
}