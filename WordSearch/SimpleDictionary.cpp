#include "SimpleDictionary.h"
#include <fstream>
#include <algorithm>
#include <climits>

bool SimpleDictionary::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    words.clear();
    minWordLength = INT_MAX;
    maxWordLength = 0;

    std::string word;
    while (file >> word) {
        words.push_back(word);
        const int len = static_cast<int>(word.length());
        if (len < minWordLength) minWordLength = len;
        if (len > maxWordLength) maxWordLength = len;
    }

    std::sort(words.begin(), words.end());
    file.close();
    return true;
}

bool SimpleDictionary::contains(const std::string& word) const {
    visitCount++;
    return std::binary_search(words.begin(), words.end(), word);
}

bool SimpleDictionary::isPrefix(const std::string& prefix) const {
    visitCount++;
    const auto it = std::lower_bound(words.begin(), words.end(), prefix);
    if (it == words.end()) return false;
    return it->compare(0, prefix.size(), prefix) == 0;
}