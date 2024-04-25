#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./FileCompression <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    // Read the contents of the input file
    std::fstream in_file(argv[1], std::ios::in);
    std::stringstream contents_stream;
    contents_stream << in_file.rdbuf();
    std::string contents = contents_stream.str();
    in_file.close();

    std::cout << contents << std::endl;

    return EXIT_SUCCESS;
}
