#ifndef MAP_CLASS
#define MAP_CLASS

#include "tile.hpp"

class Map {
public:
  //constructor takes screen, map and tile sizes
  Map(const int screen_width, const int screen_height, const int map_width, const int map_height, const int tile_size)
      : screen_width_(screen_width), screen_height_(screen_height), 
      map_width_(map_width), map_height_(map_height), tile_size_(tile_size) {}

  const int GetScreenWidth() const {return screen_width_;}
  const int GetScreenHeight() const {return screen_height_;}
  const int GetMapWidth() const {return map_width_;}
  const int GetMapHeight() const {return map_height_;}
  const int GetTileSize() const {return tile_size_;}

  //public variable for grid
  std::vector<std::vector<Tile>> grid_;


private:
  const int screen_width_;
  const int screen_height_;
  const int map_width_;
  const int map_height_;
  const int tile_size_;
};

#endif