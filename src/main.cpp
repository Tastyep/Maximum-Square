#include <iostream>

#include "SquareFinder.hh"

void
printMap(SquareFinder& finder, const SquareFinder::squareUnit& square) {
    auto& map = finder.getMatrix();

    for (unsigned int y = square.y; y < square.y + square.width; ++y) {
        for (unsigned int x = square.x; x < square.x + square.width; ++x) { map[y][x] = 'X'; }
    }
    for (const auto& str : map) { std::cout << str << std::endl; }
}

int
main(int argc, char const* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " map.txt empty_char" << std::endl;
        return 0;
    }

    SquareFinder finder(argv[1], argv[2][0]);

    const auto& square = finder.findLargest();

    std::cout << "pos: " << square.x << "/" << square.y << " " << square.width << std::endl;
    printMap(finder, square);
    return 0;
}
