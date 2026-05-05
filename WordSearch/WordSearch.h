#pragma once
#include <chrono>
#include <string>
#include <vector>
#include <unordered_set>
#include "SimpleGrid.h"
#include "SimpleDictionary.h"
#include "AdvancedDictionary.h"
#include "AdvancedGrid.h"
#include "HashDictionary.h"


struct PerformanceResult
{
    std::chrono::microseconds timeToCreatePuzzle{};
    std::chrono::microseconds timeToCreateDictionary{};
    std::chrono::microseconds timeToSolve{};

    uint32_t puzzleSize = 0;
    uint32_t dictionarySize = 0;
};


class WordSearch final
{
public:
    WordSearch(const std::string& puzzleFile, const std::string& dictionaryFile);

    WordSearch(const WordSearch&) = delete;
    WordSearch& operator=(const WordSearch&) = delete;

    uint32_t createSimplePuzzle(std::chrono::microseconds& duration);
    uint32_t createAdvancedPuzzle(std::chrono::microseconds& duration);
    uint32_t createSimpleDictionary(std::chrono::microseconds& duration);
    uint32_t createAdvancedDictionary(std::chrono::microseconds& duration);
    uint32_t createHashDictionary(std::chrono::microseconds& duration);
    void solvePuzzle(std::chrono::microseconds& duration);
    void outputResults(const std::string& outputFile, const PerformanceResult& data);

private:
    std::vector<std::string> foundWords;
    std::vector<std::pair<int, int>> foundPositions;
    std::unordered_set<std::string> foundWordsSet;

    SimpleGrid simpleGrid;
    AdvancedGrid advancedGrid;
    SimpleDictionary simpleDictionary;
    AdvancedDictionary advancedDictionary;
    HashDictionary hashDictionary;

    const std::string _puzzleFile;
    const std::string _dictionaryFile;

    int gridVisits = 0;
    int dictionaryVisits = 0;

    bool useAdvancedDictionary = false;
    bool useHashDictionary = false;
    bool useAdvancedGrid = false;
};
