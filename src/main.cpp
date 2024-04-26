#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "./FileCompression.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./FileCompression <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        std::cout << "Attempting to load file: " << argv[1] << std::endl;
        FileCompression file = FileCompression(argv[1]);
        std::cout << file.contents << std::endl;

        file.compressFile();
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Read the contents of the input file
    // std::fstream in_file(argv[1], std::ios::in);
    // if (!in_file) {
    //     std::cerr << "File not found!" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    // std::stringstream contents_stream;
    // contents_stream << in_file.rdbuf();
    // std::string contents = contents_stream.str();
    // in_file.close();

    return EXIT_SUCCESS;
}
