#include "AdvancedDictionary.h"
#include <fstream>
#include <climits>

AdvancedDictionary::AdvancedDictionary() : root(new TrieNode()), nodeCount(1), minWordLength(INT_MAX), maxWordLength(0) {
}

AdvancedDictionary::~AdvancedDictionary() {
    try { deleteTrie(root); }
    catch (...) {}
}

void AdvancedDictionary::deleteTrie(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr)
            deleteTrie(node->children[i]);
    }
    delete node;
}

bool AdvancedDictionary::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    words.clear();
    deleteTrie(root);
    root = new TrieNode();
    nodeCount = 1;

    minWordLength = INT_MAX;
    maxWordLength = 0;

    std::string word;
    while (file >> word) {
        words.push_back(word);
        const int len = static_cast<int>(word.length());
        if (len < minWordLength) minWordLength = len;
        if (len > maxWordLength) maxWordLength = len;

        TrieNode* current = root;
        for (const char c : word) {
            const int idx = c - 'A';
            if (current->children[idx] == nullptr) {
                current->children[idx] = new TrieNode();
                nodeCount++;
            }
            current = current->children[idx];
        }
        current->isWord = true;
    }

    file.close();
    return true;
}

bool AdvancedDictionary::contains(const std::string& word) const {
    TrieNode* current = root;
    for (const char c : word) {
        visitCount++;
        const int idx = c - 'A';
        if (current->children[idx] == nullptr) return false;
        current = current->children[idx];
    }
    return current->isWord;
}

bool AdvancedDictionary::isPrefix(const std::string& prefix) const {
    TrieNode* current = root;
    for (const char c : prefix) {
        visitCount++;
        const int idx = c - 'A';
        if (current->children[idx] == nullptr) return false;
        current = current->children[idx];
    }
    return true;
}

std::pair<bool, bool> AdvancedDictionary::query(const std::string& word) const {
    TrieNode* current = root;
    for (const char c : word) {
        visitCount++;
        const int idx = c - 'A';
        if (current->children[idx] == nullptr) return { false, false };
        current = current->children[idx];
    }
    return { true, current->isWord };
}

void* AdvancedDictionary::step(const void* node, char c) const {
    visitCount++;
    const TrieNode* const current = static_cast<const TrieNode*>(node);
    const int idx = c - 'A';
    if (current->children[idx] == nullptr) return nullptr;
    return current->children[idx];
}

bool AdvancedDictionary::isWord(const void* node) const {
    return static_cast<const TrieNode*>(node)->isWord;
}