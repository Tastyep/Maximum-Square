#pragma once

#include <vector>
#include <string>

class SquareFinder {
public:
    struct squareUnit {
        unsigned int x;
        unsigned int y;
        unsigned int width;

        squareUnit() : x(0), y(0), width(0){};
    };

public:
    SquareFinder(const std::string& file, char valid);
    ~SquareFinder() = default;

    std::vector<std::string>& getMatrix();

    const squareUnit& findLargest();

private:
    void parseMap(const std::string& map);

private:
    std::vector<unsigned int> data;
    std::vector<std::string> map;
    squareUnit square;
    char valid;
    unsigned int width;
};
