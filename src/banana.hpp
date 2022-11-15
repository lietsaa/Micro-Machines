#ifndef BANANA_CLASS
#define BANANA_CLASS

#include "car.hpp"
#include "item.hpp"
#include "tile.hpp"

class Banana : public Item {
 public:
  Banana() {}
  virtual void Use(Tile tile);
};

#endif