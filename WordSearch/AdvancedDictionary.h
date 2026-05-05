#pragma once
#include <string>
#include <vector>
#include <climits>
#include <cstdint>
#include <utility>

class AdvancedDictionary final
{
public:
    AdvancedDictionary();
    ~AdvancedDictionary();

    AdvancedDictionary(const AdvancedDictionary&) = delete;
    AdvancedDictionary& operator=(const AdvancedDictionary&) = delete;

    bool loadFromFile(const std::string& filename);
    bool contains(const std::string& word) const;
    bool isPrefix(const std::string& prefix) const;
    std::pair<bool, bool> query(const std::string& word) const;

    // For direct Trie walking in the solver
    void* getRoot() const { return root; }
    void* step(const void* node, char c) const;
    bool isWord(const void* node) const;

    int getMinWordLength() const { return minWordLength; }
    int getMaxWordLength() const { return maxWordLength; }
    int getNodeCount() const { return nodeCount; }
    uint32_t getMemorySize() const { return static_cast<uint32_t>(nodeCount * sizeof(TrieNode)); }
    const std::vector<std::string>& getWords() const { return words; }
    void resetVisitCount() { visitCount = 0; }
    int getVisitCount() const { return visitCount; }

private:
    struct TrieNode
    {
        bool isWord = false;
        TrieNode* children[26] = {};

        TrieNode() = default;
        TrieNode(const TrieNode&) = delete;
        TrieNode& operator=(const TrieNode&) = delete;
    };

    TrieNode* root = nullptr;
    std::vector<std::string> words;
    int nodeCount = 1;
    int minWordLength = INT_MAX;
    int maxWordLength = 0;
    mutable int visitCount = 0;

    void deleteTrie(TrieNode* node);
};