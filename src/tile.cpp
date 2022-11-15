#include "tile.hpp"

void Tile::ReceiveItem(Item &item) { items_.push_back(item); }

void Tile::GiveItem(Car car) {
  if (items_.begin() != items_.end()) {
    car.ReceiveItem(items_[0]);
    items_.empty();
  }
}