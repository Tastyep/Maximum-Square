#include "SquareFinder.hh"

#include <fstream>
# include <iostream>

SquareFinder::SquareFinder(const std::string& map, char valid) :
valid(valid),
square(),
width(0),
init(true) {
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

  if (file.is_open()) {
    this->binaryMatrix.clear();
    while (std::getline(file, line)) {
      if (line.size() == 0 || (size != 0 && line.size() != size))
        throw std::runtime_error("Invalid line length");
      else
        size = line.size();
      for (const auto& value : line) {
        this->binaryMatrix.push_back(value == this->valid ? true : false);
      }
      this->map.emplace_back(line);
    }
    this->data.clear();
    this->data.resize(this->binaryMatrix.size(), 0);
    this->init = true;
    file.close();
  }
  this->width = size;
}

const SquareFinder::squareUnit&
SquareFinder::findLargest() {
  unsigned int height = this->binaryMatrix.size() / this->width;
  unsigned int idx;

  if (this->binaryMatrix.size() % this->width)
    ++height;
  for (unsigned int x = 0; x < this->width; ++x) {
    if (this->square.width == 0 && this->binaryMatrix[x] == 1) {
      this->square.width = 1;
      this->square.x = x;
    }
    this->data[x] = this->binaryMatrix[x];
  }
  std::cout << "wi: " << height << std::endl;
  for (unsigned int y = 0; y < height; ++y) {
    this->data[y * this->width] = this->binaryMatrix[y * this->width];
  }
  for (unsigned int y = 1; y < height; ++y) {
    for (unsigned int x = 1; x < this->width; ++x) {
      idx = y * this->width + x;
      if (this->binaryMatrix[idx] == 1) {
        this->data[idx] = std::min(std::min(this->data[idx - 1], this->data[idx - this->width]),
                                   this->data[idx - this->width - 1]) + 1;
       if (this->square.width < this->data[idx]) {
         this->square.width = this->data[idx];
         this->square.x = x;
         this->square.y = y;
       }
      }
      else {
        this->data[idx] = 0;
      }
    }
  }
  if (this->square.width > 0) {
    this->square.x -= this->square.width - 1;
    this->square.y -= this->square.width - 1;
  }
  return this->square;
}
