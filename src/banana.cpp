#include "banana.hpp"

void Banana::Use(Tile tile) { tile.ReceiveItem(*this); }