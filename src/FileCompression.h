#pragma once

#include <ios>
#include <string>
#include <unordered_map>

struct FrequencyNode {
    char value;
    int freq;
    FrequencyNode* left;
    FrequencyNode* right;
};

class FileCompression {
public:
    std::string contents;
    std::string fileName;

    FileCompression(std::string file_name) noexcept(false);
    ~FileCompression();
    void compressFile() noexcept(false);
    void decompressFile();

private:
    std::unordered_map<char, std::string> encodings;
    FrequencyNode* root;

    void deleteTree(FrequencyNode* node);
    FrequencyNode* buildHuffmanTree(std::unordered_map<char, int> freq_table);
    void generateEncodings(FrequencyNode* tree_root);
};
