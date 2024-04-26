#include <cstddef>
#include <functional>
#include <queue>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "./FileCompression.h"


FileCompression::FileCompression(std::string file_name) noexcept(false)
{
    std::fstream in_file(file_name, std::ios::in);
    if (!in_file) {
        throw std::ios_base::failure("File not found!");
    } else {
        this->fileName = file_name;
    }

    std::stringstream contents_stream;
    contents_stream << in_file.rdbuf();
    in_file.close();
    this->contents = contents_stream.str();
}

FileCompression::~FileCompression()
{
}

void FileCompression::compressFile() noexcept(false)
{
    // Handle empty file
    if (this->contents.empty()) {
        throw std::ios_base::failure("File is empty!");
    }

    // Build frequency table of each character
    std::unordered_map<char, int> freq_table;
    for (char c : this->contents) {
        freq_table[c]++;
    }

    // Create a min_queue based on frequency
    std::priority_queue<FrequencyNode*, std::vector<FrequencyNode*>, FreqNodeComparator> pq;
    for (auto iter : freq_table) {
        pq.push(new FrequencyNode{ .value = iter.first, .freq = iter.second });
    }

    while (pq.size() > 1) {
        FrequencyNode* left = pq.top();
        pq.pop();
        FrequencyNode* right = pq.top();
        pq.pop();

        FrequencyNode* parent = new FrequencyNode{ .value = '\0', .freq = left->freq + right->freq };
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    this->root = pq.top();
    pq.pop();
    this->generateEncodings(this->root, "");
}

void FileCompression::decompressFile()
{
}

void FileCompression::generateEncodings(FrequencyNode* node, std::string encoding) {
    if (!node) {
        return;
    }

    if (!node->left && !node->right) {
        this->encodings[node->value] = encoding;
    }

    this->generateEncodings(node->left, encoding + "0");
    this->generateEncodings(node->right, encoding + "1");
}
