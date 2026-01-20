#include "utils/error_handling.hpp"

bool ErrorHandling::had_error_ = false;

void ErrorHandling::lox_error(int line, std::string_view msg)
{
    std::cerr << "[line " << line
                        << "] Error: " << msg << '\n';
    had_error_ = true;
}