#include "SquareFinder.hh"

#include <fstream>
#include <iostream>

SquareFinder::SquareFinder(const std::string& map, char valid) : valid(valid), square(), width(0) {
    this->parseMap(map);
}

std::vector<std::string>&
SquareFinder::getMatrix() {
    return this->map;
}

void
SquareFinder::parseMap(const std::string& map) {
    std::ifstream file(map.c_str());
    std::string line;
    unsigned int size = 0;

    std::cout << "Parsing map" << std::endl;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.size() == 0 || (size != 0 && line.size() != size))
                throw std::runtime_error("Invalid line length");
            else
                size = line.size();
            this->map.emplace_back(line);
        }
        this->width = size;
        this->data.clear();
        this->data.resize(this->map.size() * this->width);
        file.close();
    }
    std::cout << "Parsing done" << std::endl;
}

const SquareFinder::squareUnit&
SquareFinder::findLargest() {
    unsigned int height = this->map.size();
    unsigned int idx;

    for (unsigned int x = 0; x < this->width; ++x) {
        if (this->square.width == 0 && this->map[0][x] == this->valid) {
            this->square.width = 1;
            this->square.x = x;
        }
        this->data[x] = (this->map[0][x] == this->valid);
    }
    for (unsigned int y = 0; y < height; ++y) {
        this->data[y * this->width] = (this->map[y][0] == this->valid);
    }
    for (unsigned int y = 1; y < height; ++y) {
        idx = y * this->width;
        for (unsigned int x = 1; x < this->width; ++x) {
            ++idx;
            if (this->map[y][x] == this->valid) {
                this->data[idx] =
                    std::min(std::min(this->data[idx - 1], this->data[idx - this->width]),
                             this->data[idx - this->width - 1]) +
                    1;
                if (this->square.width < this->data[idx]) {
                    this->square.width = this->data[idx];
                    this->square.x = x;
                    this->square.y = y;
                }
            } else { this->data[idx] = 0; }
        }
    }
    if (this->square.width > 0) {
        this->square.x -= this->square.width - 1;
        this->square.y -= this->square.width - 1;
    }
    return this->square;
}
