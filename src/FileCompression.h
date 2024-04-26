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

struct FreqNodeComparator {
    bool operator()(FrequencyNode* left, FrequencyNode* right) {
        return left->freq > right->freq;
    }
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
    void generateEncodings(FrequencyNode*, std::string);
};
