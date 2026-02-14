#include "common/ErrorEnums.hpp"
#include "common/Token.hpp"

#include "scanning/Scanner.hpp"

#include "utils/Errors.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto read_file_contents(const std::string& filename) -> std::string;

int main(int argc, char *argv[]) {
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here!" << '\n';

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << '\n';
        return static_cast<int>(ErrorEnums::unknown_command);
    }

    const std::string command = argv[1];

    if (command == "tokenize") {
        Scanner scanner {read_file_contents(argv[2])};
        std::vector<Token> tokens (scanner.scanTokens());

        for (const Token& token : tokens)
        {
            std::cout << token.to_string() << '\n';
        }

        if (g_hadError)
        {
            return static_cast<int>(ErrorEnums::lox_error);
        }
    }  
    
    std::cerr << "Unknown command: " << command << '\n';
    return static_cast<int>(ErrorEnums::unknown_command);
}

auto read_file_contents(const std::string& filename) -> std::string {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << '\n';
        std::exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}