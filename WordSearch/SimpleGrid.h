#pragma once
#include <vector>
#include <string>

class SimpleGrid final
{
public:
    SimpleGrid() = default;
    ~SimpleGrid() = default;

    SimpleGrid(const SimpleGrid&) = delete;
    SimpleGrid& operator=(const SimpleGrid&) = delete;

    bool loadFromFile(const std::string& filename);
    char get(int row, int col) const;
    int getSize() const { return static_cast<int>(grid.size()); }

private:
    std::vector<std::vector<char>> grid;
};