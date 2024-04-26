#include <cstddef>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include "./FileCompression.h"


FileCompression::FileCompression(std::string file_name)
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

void FileCompression::compressFile()
{
    // Huffman compression
    // 1. Count frequency of each character
    // 2. Create a priority queue of nodes
    // 3. Create a huffman tree
    // 4. Create a huffman code table
    // 5. Encode the file
    // 6. Write the encoded file to a new file

}

void FileCompression::decompressFile()
{
}
