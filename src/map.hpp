#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

class Map {
public:
    std::ifstream input_file;
    std::vector<std::string> lines;
    sf::Image image;

    sf::Image MapFunction(std::string filePath);
};