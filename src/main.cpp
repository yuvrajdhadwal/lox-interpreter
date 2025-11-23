#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

std::string read_file_contents(const std::string& filename);
void parse_characters(std::string_view file_contents);
void scan_errors(std::string_view file_contents);

int main(int argc, char *argv[]) {
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return 1;
    }

    const std::string command = argv[1];

    if (command == "tokenize") {
        std::string file_contents = read_file_contents(argv[2]);
        
        if (!file_contents.empty())
        {
            scan_errors(file_contents);
            parse_characters(file_contents);
        }

        std::cout << "EOF  null" << std::endl;
        
        
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
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

void parse_characters(std::string_view file_contents)
{
    for (char c : file_contents)
    {
        switch (c)
        {
        case '(':
            std::cout << "LEFT_PAREN ( null\n";
            break;
        case ')':
            std::cout << "RIGHT_PAREN ) null\n";
            break;
        case '{':
            std::cout << "LEFT_BRACE { null\n";
            break;
        case '}':
            std::cout << "RIGHT_BRACE } null\n";
            break;
        case ',':
            std::cout << "COMMA , null\n";
            break;
        case '.':
            std::cout << "DOT . null\n";
            break;
        case '-':
            std::cout << "MINUS - null\n";
            break;
        case '+':
            std::cout << "PLUS + null\n";
            break;
        case ';':
            std::cout << "SEMICOLON ; null\n";
            break;
        case '/':
            std::cout << "SLASH / null\n";
            break;
        case '*':
            std::cout << "STAR * null\n";
            break;
        default:
            ;  // null statement
        }   
    }
}

void scan_errors(std::string_view file_contents)
{
    for (char c : file_contents)
    {
        switch (c)
        {
        case '$':
        case '#':
            std::cerr << "[line 1] Error: Unexpected character: " << c << '\n';
        }
    }
}