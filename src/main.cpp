#include "common/error_enums.hpp"
#include "scanning/scanning_utils.hpp"
#include "utils/error_handling.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return static_cast<int>(ErrorEnums::unknown_command);
    }

    const std::string command = argv[1];

    if (command == "tokenize") {
        std::string file_contents = read_file_contents(argv[2]);
        
        // if (!file_contents.empty())
        // {
            parse_characters(file_contents);
        // }

        // std::cout << "EOF  null" << std::endl;

        if (ErrorHandling::had_error_)
        {
            return static_cast<int>(ErrorEnums::lox_error);
        }

        return static_cast<int>(ErrorEnums::no_error);
        
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return static_cast<int>(ErrorEnums::unknown_command);
    }
}

std::string read_file_contents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
