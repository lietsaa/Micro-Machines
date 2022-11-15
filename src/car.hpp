#ifndef CAR_CLASS
#define CAR_CLASS

#include <vector>

#include "item.hpp"

class Car {
 public:
  Car(const int weight, int max_speed, int handling)
      : weight_(weight), max_speed_(max_speed), handling_(handling) {}
  const int GetWeight() const { return weight_; }
  int GetMaxSpeed() const { return max_speed_; }
  int GetHandling() const { return handling_; }
  void Draw();
  void Sound();
  void Update();
  void Accelerate();
  void Decelerate();
  void TurnRight();
  void TurnLeft();
  void ReceiveItem(Item &item);
  void UseItem();

 private:
  const int weight_;
  int max_speed_;
  int handling_;
  std::vector<Item> items_;
};

#endif