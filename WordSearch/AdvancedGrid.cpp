#include "AdvancedGrid.h"
#include <fstream>

AdvancedGrid::~AdvancedGrid() {
    delete[] flatCells;
    flatCells = nullptr;
    topLeft = nullptr;
}

bool AdvancedGrid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    file >> size;

    Cell* const cells = new Cell[size * size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char c;
            file >> c;
            cells[i * size + j].value = c;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Cell* const cell = &cells[i * size + j];
            if (i > 0)                        cell->up = &cells[(i - 1) * size + j];
            if (i < size - 1)                 cell->down = &cells[(i + 1) * size + j];
            if (j > 0)                        cell->left = &cells[i * size + (j - 1)];
            if (j < size - 1)                 cell->right = &cells[i * size + (j + 1)];
            if (i > 0 && j > 0)               cell->upLeft = &cells[(i - 1) * size + (j - 1)];
            if (i > 0 && j < size - 1)        cell->upRight = &cells[(i - 1) * size + (j + 1)];
            if (i < size - 1 && j > 0)        cell->downLeft = &cells[(i + 1) * size + (j - 1)];
            if (i < size - 1 && j < size - 1) cell->downRight = &cells[(i + 1) * size + (j + 1)];
        }
    }

    topLeft = &cells[0];
    flatCells = cells;

    file.close();
    return true;
}