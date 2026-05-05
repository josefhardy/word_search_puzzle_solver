#include <iostream>
#include "WordSearch.h"
#include <algorithm>
#include <fstream>

WordSearch::WordSearch(const std::string& puzzleFile, const std::string& dictionaryFile) :
    _puzzleFile(puzzleFile), _dictionaryFile(dictionaryFile)
{
}

uint32_t WordSearch::createSimplePuzzle(std::chrono::microseconds& duration)
{
    std::cout << "Creating simple puzzle..." << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();

    useAdvancedGrid = false;
    simpleGrid.loadFromFile(_puzzleFile);

    const uint32_t size = simpleGrid.getSize();
    const uint32_t byteSize = size * size * sizeof(char);

    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start
    );

    return byteSize;
}

uint32_t WordSearch::createAdvancedPuzzle(std::chrono::microseconds& duration)
{
    std::cout << "Creating advanced puzzle..." << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();

    useAdvancedGrid = true;
    advancedGrid.loadFromFile(_puzzleFile);

    const uint32_t size = advancedGrid.getSize();
    const uint32_t byteSize = size * size * static_cast<uint32_t>(sizeof(Cell));

    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start
    );

    return byteSize;
}

uint32_t WordSearch::createSimpleDictionary(std::chrono::microseconds& duration)
{
    std::cout << "Creating simple dictionary..." << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();

    useAdvancedDictionary = false;
    simpleDictionary.loadFromFile(_dictionaryFile);

    uint32_t byteSize = 0;
    for (const auto& w : simpleDictionary.getWords())
        byteSize += static_cast<uint32_t>(sizeof(std::string) + w.capacity());

    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start
    );

    return byteSize;
}

uint32_t WordSearch::createAdvancedDictionary(std::chrono::microseconds& duration)
{
    std::cout << "Creating advanced dictionary..." << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();

    useAdvancedDictionary = true;
    advancedDictionary.loadFromFile(_dictionaryFile);

    const uint32_t byteSize = advancedDictionary.getMemorySize();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start
    );

    return byteSize;
}

uint32_t WordSearch::createHashDictionary(std::chrono::microseconds& duration)
{
    std::cout << "Creating hash dictionary..." << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();

    useAdvancedDictionary = false;
    useHashDictionary = true;

    hashDictionary.loadFromFile(_dictionaryFile);

    const uint32_t byteSize = hashDictionary.getMemorySize();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start
    );

    return byteSize;
}

void WordSearch::solvePuzzle(std::chrono::microseconds& duration)
{
    gridVisits = 0;

    std::cout << "Solving puzzle..." << std::endl;

    foundWords.clear();
    foundPositions.clear();
    foundWordsSet.clear();

    if (useAdvancedDictionary)
        advancedDictionary.resetVisitCount();
    else if (useHashDictionary)
        hashDictionary.resetVisitCount();
    else
        simpleDictionary.resetVisitCount();

    const auto startTime = std::chrono::high_resolution_clock::now();

    if (!useAdvancedGrid)
    {
        const int size = simpleGrid.getSize();

        int directions[8][2] = {
            {0,1}, {0,-1}, {1,0}, {-1,0},
            {1,1}, {1,-1}, {-1,1}, {-1,-1}
        };

        const int minLen = useAdvancedDictionary ?
            advancedDictionary.getMinWordLength() :
            (useHashDictionary ?
                hashDictionary.getMinWordLength() :
                simpleDictionary.getMinWordLength());

        const int maxLen = useAdvancedDictionary ?
            advancedDictionary.getMaxWordLength() :
            (useHashDictionary ?
                hashDictionary.getMaxWordLength() :
                simpleDictionary.getMaxWordLength());

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int d = 0; d < 8; d++) {

                    const int dx = directions[d][0];
                    const int dy = directions[d][1];

                    const int endX = i + dx * (minLen - 1);
                    const int endY = j + dy * (minLen - 1);
                    if (endX < 0 || endX >= size || endY < 0 || endY >= size)
                        continue;

                    int x = i;
                    int y = j;

                    char buffer[64];
                    int length = 0;

                    void* trieNode = useAdvancedDictionary ?
                        advancedDictionary.getRoot() : nullptr;

                    while (x >= 0 && x < size && y >= 0 && y < size && length < maxLen) {

                        gridVisits++;

                        const char c = simpleGrid.get(x, y);
                        buffer[length++] = c;

                        bool isWord = false;

                        if (useAdvancedDictionary) {
                            trieNode = advancedDictionary.step(trieNode, c);
                            if (trieNode == nullptr) break;
                            if (length >= minLen) {
                                isWord = advancedDictionary.isWord(trieNode);
                            }
                        }
                        else if (length >= minLen) {
                            if (useHashDictionary) {
                                const std::string temp(buffer, length);
                                if (!hashDictionary.checkWordAndPrefix(temp, isWord)) break;
                            }
                            else {
                                const std::string temp(buffer, length);
                                if (!simpleDictionary.isPrefix(temp)) break;
                                isWord = simpleDictionary.contains(temp);
                            }
                        }

                        if (isWord) {
                            const std::string temp(buffer, length);
                            if (foundWordsSet.insert(temp).second) {
                                foundWords.push_back(temp);
                                foundPositions.push_back({ j, i });
                            }
                        }

                        x += dx;
                        y += dy;
                    }
                }
            }
        }
    }
    else
    {
        const int size = advancedGrid.getSize();

        const int minLen = useAdvancedDictionary ?
            advancedDictionary.getMinWordLength() :
            (useHashDictionary ?
                hashDictionary.getMinWordLength() :
                simpleDictionary.getMinWordLength());

        const int maxLen = useAdvancedDictionary ?
            advancedDictionary.getMaxWordLength() :
            (useHashDictionary ?
                hashDictionary.getMaxWordLength() :
                simpleDictionary.getMaxWordLength());

        Cell* Cell::* moves[8] = {
            &Cell::right,
            &Cell::left,
            &Cell::down,
            &Cell::up,
            &Cell::downRight,
            &Cell::downLeft,
            &Cell::upRight,
            &Cell::upLeft
        };

        Cell* row = advancedGrid.getTopLeft();

        for (int i = 0; i < size; i++) {

            Cell* start = row;

            for (int j = 0; j < size; j++) {

                for (int d = 0; d < 8; d++) {

                    Cell* current = start;

                    char buffer[64];
                    int length = 0;

                    void* trieNode = useAdvancedDictionary ?
                        advancedDictionary.getRoot() : nullptr;

                    while (current != nullptr && length < maxLen) {

                        gridVisits++;

                        const char c = current->value;
                        buffer[length++] = c;

                        bool isWord = false;

                        if (useAdvancedDictionary) {
                            trieNode = advancedDictionary.step(trieNode, c);
                            if (trieNode == nullptr) break;
                            if (length >= minLen) {
                                isWord = advancedDictionary.isWord(trieNode);
                            }
                        }
                        else if (length >= minLen) {
                            if (useHashDictionary) {
                                const std::string temp(buffer, length);
                                if (!hashDictionary.checkWordAndPrefix(temp, isWord)) break;
                            }
                            else {
                                const std::string temp(buffer, length);
                                if (!simpleDictionary.isPrefix(temp)) break;
                                isWord = simpleDictionary.contains(temp);
                            }
                        }

                        if (isWord) {
                            const std::string temp(buffer, length);
                            if (foundWordsSet.insert(temp).second) {
                                foundWords.push_back(temp);
                                foundPositions.push_back({ j, i });
                            }
                        }

                        current = current->*moves[d];
                    }
                }

                start = start->right;
            }

            row = row->down;
        }
    }

    duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - startTime
    );

    if (useAdvancedDictionary)
        dictionaryVisits = advancedDictionary.getVisitCount();
    else if (useHashDictionary)
        dictionaryVisits = hashDictionary.getVisitCount();
    else
        dictionaryVisits = simpleDictionary.getVisitCount();
}

void WordSearch::outputResults(const std::string& outputFile, const PerformanceResult& data)
{
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cout << "Failed to open output file\n";
        return;
    }

    // ===== Matched =====
    out << "Number of words matched: " << foundWords.size() << "\n\n";

    out << "Words matched in grid:\n";
    for (size_t i = 0; i < foundWords.size(); i++) {
        out << foundPositions[i].first << " "
            << foundPositions[i].second << " "
            << foundWords[i] << "\n";
    }
    out << "\n";

    // ===== Unmatched =====
    std::vector<std::string> unmatchedWords;
    const std::vector<std::string>& allWords =
        useAdvancedDictionary ? advancedDictionary.getWords() :
        useHashDictionary ? hashDictionary.getWords() :
        simpleDictionary.getWords();

    for (const auto& word : allWords) {
        if (foundWordsSet.find(word) == foundWordsSet.end()) {
            unmatchedWords.push_back(word);
        }
    }

    out << "Words unmatched in grid:\n";
    for (const auto& word : unmatchedWords) {
        out << word << "\n";
    }
    out << "\n";

    // ===== Stats =====
    out << "Number of grid cells visited: " << gridVisits << "\n";
    out << "Number of dictionary entries visited: " << dictionaryVisits << "\n\n";

    // ===== Timing =====
    out << "Time to populate grid: " << data.timeToCreatePuzzle.count() / 1000000.0 << "\n";
    out << "Time to populate dictionary: " << data.timeToCreateDictionary.count() / 1000000.0 << "\n";
    out << "Time to solve puzzle: " << data.timeToSolve.count() / 1000000.0 << "\n\n";

    // ===== Memory =====
    out << "Size of the grid data structure: " << data.puzzleSize << "\n";
    out << "Size of the dictionary data structure: " << data.dictionarySize << "\n";

    out.close();
}