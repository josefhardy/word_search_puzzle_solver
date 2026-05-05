#include "HashDictionary.h"
#include <fstream>
#include <climits>

bool HashDictionary::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    wordList.clear();
    dict.clear();
    dict.reserve(50000);

    minWordLength = INT_MAX;
    maxWordLength = 0;

    std::string word;
    while (file >> word) {
        wordList.push_back(word);
        const int len = static_cast<int>(word.length());
        if (len < minWordLength) minWordLength = len;
        if (len > maxWordLength) maxWordLength = len;

        std::string prefix;
        for (const char c : word) {
            prefix.push_back(c);
            if (dict.find(prefix) == dict.end()) {
                dict[prefix] = false;
            }
        }
        dict[word] = true;
    }

    file.close();
    return true;
}

bool HashDictionary::checkWordAndPrefix(const std::string& str, bool& isWord) const {
    visitCount++;
    const auto it = dict.find(str);
    if (it == dict.end())
        return false;
    isWord = it->second;
    return true;
}

uint32_t HashDictionary::getMemorySize() const {
    uint32_t size = sizeof(dict);
    for (const auto& pair : dict) {
        size += static_cast<uint32_t>(sizeof(pair));
        size += static_cast<uint32_t>(pair.first.capacity());
    }
    return size;
}