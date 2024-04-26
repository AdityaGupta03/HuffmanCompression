#pragma once

#include <string>

class FileCompression {
public:
    std::string contents;
    std::string fileName;

    FileCompression(std::string file_name);
    ~FileCompression();
    void compressFile();
    void decompressFile();

private:
    void writeContents(std::string output_file_name);
    void build_frequency_table();
    void build_huffman_tree();
    void build_huffman_table();
};
