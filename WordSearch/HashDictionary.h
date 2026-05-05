#pragma once
#include <unordered_set>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>

class HashDictionary final
{
public:
    HashDictionary() = default;
    ~HashDictionary() = default;

    HashDictionary(const HashDictionary&) = delete;
    HashDictionary& operator=(const HashDictionary&) = delete;

    bool loadFromFile(const std::string& filename);
    bool checkWordAndPrefix(const std::string& str, bool& isWord) const;

    int getMinWordLength() const { return minWordLength; }
    int getMaxWordLength() const { return maxWordLength; }
    void resetVisitCount() { visitCount = 0; }
    int getVisitCount() const { return visitCount; }
    const std::vector<std::string>& getWords() const { return wordList; }
    uint32_t getMemorySize() const;

private:
    std::unordered_map<std::string, bool> dict;
    std::vector<std::string> wordList;
    int minWordLength = 0;
    int maxWordLength = 0;
    mutable int visitCount = 0;
};