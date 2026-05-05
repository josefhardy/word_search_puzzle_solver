#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

class SimpleDictionary final
{
public:
    SimpleDictionary() = default;
    ~SimpleDictionary() = default;

    SimpleDictionary(const SimpleDictionary&) = delete;
    SimpleDictionary& operator=(const SimpleDictionary&) = delete;

    bool loadFromFile(const std::string& filename);
    bool contains(const std::string& word) const;
    bool isPrefix(const std::string& prefix) const;

    const std::vector<std::string>& getWords() const { return words; }
    int getMinWordLength() const { return minWordLength; }
    int getMaxWordLength() const { return maxWordLength; }
    void resetVisitCount() { visitCount = 0; }
    int getVisitCount() const { return visitCount; }

private:
    std::vector<std::string> words;
    int minWordLength = INT_MAX;
    int maxWordLength = 0;
    mutable int visitCount = 0;
};