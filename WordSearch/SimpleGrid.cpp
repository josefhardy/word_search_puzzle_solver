#include "SimpleGrid.h"
#include <fstream>

bool SimpleGrid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    grid.clear();

    int size;
    file >> size;
    grid.reserve(size);

    for (int i = 0; i < size; i++) {
        std::vector<char> row;
        row.reserve(size);
        for (int j = 0; j < size; j++) {
            char c;
            file >> c;
            row.push_back(c);
        }
        grid.push_back(std::move(row));
    }

    file.close();
    return true;
}

char SimpleGrid::get(int row, int col) const {
    return grid[row][col];
}