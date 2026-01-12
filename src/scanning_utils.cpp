#include "scanning_utils.hpp"

void parse_characters(std::string_view file_contents, int& exit_code)
{
    int line_number {1};
    bool is_comment {false};

    for (int i {0}; i < file_contents.length(); ++i)
    {
        std::string rel_op_parse{};
        if (is_comment && file_contents[i] == '\n')
        {
            is_comment = false;
            ++line_number;
        } else if (!is_comment)
        {
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
                    is_comment = true;
                    break;
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
                parse_relational_op(file_contents, i);
                break;
            case ' ':
            case '\t':
                break;
            case '\n':
                ++line_number;
                break;
            case '"':
                parse_string_literal(file_contents, i, line_number, exit_code);
                break;
            default:
                std::cerr << "[line " << line_number
                    << "] Error: Unexpected character: " << file_contents[i] << '\n';
                exit_code = 65;
                break;
            }
        }
    }
}

void parse_relational_op(std::string_view file_contents, int& i)
{
    std::string rel_op_parse{};
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
}

void parse_string_literal(std::string_view file_contents, int& i, int& line_number, int& exit_code)
{
    int string_start = i;
    ++i;

    while (i < file_contents.length() && file_contents[i] != '"')
    {
        if (file_contents[i] == '\n')
        {
            ++line_number;
        }
        ++i;
    }

    if (i >= file_contents.length())
    {
        std::cerr << "[line " << line_number
            << "] Error: Unterminated string.\n";
        exit_code = 65;
    }
    else {
        std::string_view str = file_contents.substr(string_start + 1, i - string_start - 1);
        std::cout << "STRING \"" << str << "\" " << str << '\n';
    }
}
