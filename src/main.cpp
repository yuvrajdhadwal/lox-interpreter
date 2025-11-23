#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

std::string read_file_contents(const std::string& filename);
int parse_characters(std::string_view file_contents);

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
    int exit_code {0};

    if (command == "tokenize") {
        std::string file_contents = read_file_contents(argv[2]);
        
        if (!file_contents.empty())
        {
            exit_code = parse_characters(file_contents);
        }

        std::cout << "EOF  null" << std::endl;
        
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }
    return exit_code;
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

int parse_characters(std::string_view file_contents)
{
    int exit_code {0};
    for (int i {0}; i < file_contents.length(); ++i)
    {
        std::string rel_op_parse{};
        switch (file_contents[i])
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
            if (i + 1 < file_contents.length() && file_contents[i + 1] == '/')
            {
                return exit_code;
            }

            std::cout << "SLASH / null\n";
            break;
        case '*':
            std::cout << "STAR * null\n";
            break;
        case '=':
        case '!':
        case '<':
        case '>':
            if (file_contents[i] == '=')
            {
                rel_op_parse = "EQUAL";
            } else if (file_contents[i] == '!')
            {
                rel_op_parse = "BANG";
            } else if (file_contents[i] == '<')
            {
                rel_op_parse = "LESS";
            } else
            {
                rel_op_parse = "GREATER";
            }

            if (i + 1 < file_contents.length() && file_contents[i + 1] == '=')
            {
                std::cout << rel_op_parse << "_EQUAL " << file_contents[i] << "= null\n";
                i += 1;
            } else {
                std::cout << rel_op_parse << ' ' << file_contents[i] << " null\n";
            }
            break;
        case ' ':
        case '\t':
        case '\n':
            break;
        default:
            std::cerr << "[line 1] Error: Unexpected character: " << file_contents[i] << '\n';
            exit_code = 65;
            break;
        }   
    }

    return exit_code;
}
