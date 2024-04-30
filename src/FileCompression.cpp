#include <cstddef>
#include <functional>
#include <queue>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cassert>

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
    this->deleteTree(this->root);
}

void FileCompression::deleteTree(FrequencyNode* node)
{
    if (!node) {
        return;
    }

    this->deleteTree(node->left);
    this->deleteTree(node->right);
    delete node;
}

void FileCompression::compressFile() noexcept(false)
{
    // Handle empty file
    if (this->contents.empty()) {;
        throw std::ios_base::failure("File is empty!");
    }

    // Build frequency table from each character
    std::unordered_map<char, int> freq_table;
    for (char c : this->contents) {
        freq_table[c]++;
    }

    this->root = this->buildHuffmanTree(freq_table);
    this->generateEncodings(this->root); // Saves encodings to this->encodings

    // TODO: Write compressed file
}

void FileCompression::decompressFile()
{
    assert(false); // Not implemented
}

FrequencyNode* FileCompression::buildHuffmanTree(std::unordered_map<char, int> freq_table)
{
    // Define custom comparator for min_queue
    struct min_queue_compare {
        bool operator()(FrequencyNode* left, FrequencyNode* right) {
            return left->freq > right->freq;
        }
    };

    // Create a min_queue based on frequency
    std::priority_queue<FrequencyNode*, std::vector<FrequencyNode*>, min_queue_compare> pq;
    for (auto iter : freq_table) {
        pq.push(new FrequencyNode{ .value = iter.first, .freq = iter.second });
    }

    // Create huffman tree
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

    FrequencyNode* tree_root = pq.top();
    pq.pop();
    return tree_root;
}

void FileCompression::generateEncodings(FrequencyNode* tree_root)
{
    std::queue<std::pair<FrequencyNode*, std::string>> encode_q;
    encode_q.push({tree_root, ""});
    while (!encode_q.empty()) {
        auto [node, encoding] = encode_q.front();
        encode_q.pop();

        if (!node) {
            continue;
        }

        if (!node->left && !node->right) {
            this->encodings[node->value] = encoding;
        }

        encode_q.push({ node->left, encoding + "0" });
        encode_q.push({ node->right, encoding + "1" });
    }
}
