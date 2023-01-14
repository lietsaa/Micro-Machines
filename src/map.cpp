#include "map.hpp"

sf::Image Map::MapFunction(std::string filePath) {
    input_file.open(filePath);

    // Read in the contents of the file
    std::string line;
    while (std::getline(input_file, line)) {
        lines.push_back(line);
    }

    // Determine the size of the output image
    int width = 1024;
    int height = 1024;

    // Create the output image
    image.create(width, height);

    // Set the pixels in the image based on the input file
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char c = lines[y / (1024 / 24) % lines.size()][x / (1024 / 24) % lines[0].size()];
            if (c == 'x') {
                image.setPixel(x, y, sf::Color::Black);
            } else if (c == '0') {
                image.setPixel(x, y, sf::Color::White);
            } else if (c == '1') {
                image.setPixel(x, y, sf::Color::Red);
            } else if (c == '2') {
                image.setPixel(x, y, sf::Color::Green);
            } else if (c == '3') {
                image.setPixel(x, y, sf::Color::Blue);
            } else if (c == '4') {
                image.setPixel(x, y, sf::Color::Green);
            } else if (c == '5') {
                image.setPixel(x, y, sf::Color::Red);
            } else if (c == '6') {
                image.setPixel(x, y, sf::Color::Magenta);
            } else if (c == '7') {
                image.setPixel(x, y, sf::Color::Yellow);
            }
        }
    }
    return image;
}
