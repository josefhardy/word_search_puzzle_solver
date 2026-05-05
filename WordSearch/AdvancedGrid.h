#pragma once
#include <string>

struct Cell final
{
    char value = '\0';
    Cell* up = nullptr;
    Cell* down = nullptr;
    Cell* left = nullptr;
    Cell* right = nullptr;
    Cell* upLeft = nullptr;
    Cell* upRight = nullptr;
    Cell* downLeft = nullptr;
    Cell* downRight = nullptr;

    Cell() = default;
    Cell(const Cell&) = delete;
    Cell& operator=(const Cell&) = delete;
};

class AdvancedGrid final
{
public:
    AdvancedGrid() = default;
    ~AdvancedGrid();

    AdvancedGrid(const AdvancedGrid&) = delete;
    AdvancedGrid& operator=(const AdvancedGrid&) = delete;

    bool loadFromFile(const std::string& filename);

    Cell* getTopLeft() const { return topLeft; }
    int getSize() const { return size; }

private:
    Cell* topLeft = nullptr;
    Cell* flatCells = nullptr;
    int size = 0;
};