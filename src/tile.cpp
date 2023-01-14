#include "tile.hpp"
#include <iostream>

void Tiles::tiles(std::string filePath) {
    input_file.open(filePath);
    int counter_x = 0;
    int counter_y = 0;

    char c;
    while (input_file.get(c)) {
        if (c == 'x') {
            x.push_back(counter_x * 125);
            x_y.push_back(counter_y * 125);
        } else if (c == '0') {
            zero.push_back(counter_x * 125);
            zero_y.push_back(counter_y * 125);
        } else if (c == '1') {
            one.push_back(counter_x * 125);
            one_y.push_back(counter_y * 125);
        } else if (c == '2') {
            two.push_back(counter_x * 125);
            two_y.push_back(counter_y * 125);
        } else if (c == '3') {
            three.push_back(counter_x * 125);
            three_y.push_back(counter_y * 125);
        } else if (c == '4') {
            four.push_back(counter_x * 125);
            four_y.push_back(counter_y * 125);
        } else if (c == '5') {
            five.push_back(counter_x * 125);
            five_y.push_back(counter_y * 125);
        } else if (c == '6') {
            six.push_back(counter_x * 125);
            six_y.push_back(counter_y * 125);
        } else if (c == '7') {
            seven.push_back(counter_x * 125);
            seven_y.push_back(counter_y * 125);
        }
            if (counter_x <= 23) {
                counter_x += 1;
            } else {
                counter_x = 0;
                counter_y += 1;
            }
        }

        // Close the document
        input_file.close();
    }
