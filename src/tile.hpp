#ifndef Tile_CLASS
#define Tile_CLASS
#include <vector>
#include <fstream>

class Tiles {
public:
    std::vector<int> x;
    std::vector<int> x_y;
    std::vector<int> zero;
    std::vector<int> zero_y;
    std::vector<int> one;
    std::vector<int> one_y;
    std::vector<int> two;
    std::vector<int> two_y;
    std::vector<int> three;
    std::vector<int> three_y;
    std::vector<int> four;
    std::vector<int> four_y;
    std::vector<int> five;
    std::vector<int> five_y;
    std::vector<int> six;
    std::vector<int> six_y;
    std::vector<int> seven;
    std::vector<int> seven_y;
    std::ifstream input_file;

    void tiles();
};


#endif