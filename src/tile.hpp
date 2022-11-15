#ifndef TILE_CLASS
#define TILE_CLASS

#include <utility>
#include <vector>

#include "car.hpp"
#include "item.hpp"

class Tile {
 public:
  Tile(const int speed_coefficient, const int friction_coefficient,
       const std::pair<int, int> pos)
      : speed_coefficient_(speed_coefficient),
        pos_(pos),
        friction_coefficient_(friction_coefficient) {}
  const int GetSpeedCoefficient() const { return speed_coefficient_; }
  const int GetFrictionCoefficient() const { return friction_coefficient_; }
  const std::pair<int, int> GetPosition() const { return pos_; }
  void ReceiveItem(Item &item);
  void GiveItem(Car car);

 private:
  const int speed_coefficient_;
  const int friction_coefficient_;
  const std::pair<int, int> pos_;
  std::vector<Item> items_;
};

#endif