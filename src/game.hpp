#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SFML/Graphics.hpp>
#include <memory>
#include "map.hpp"
#include "car.hpp"


/* Game object handles game logic and memory operations related to it. It also opens a given file to read the chosen map from
- game situation is handled through getters and setters to restrict access
-
*/

class Car;
class Game {
 private:
  int lap_;
  std::vector<std::shared_ptr<Car>> cars_;

 public:
  Game(Map, b2World& world);
  void Update();
  int GetMaxlaps();
  int GetLaps();
  Car &GetPlayer1();
  Car &GetCar();
};

#endif