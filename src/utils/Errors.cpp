#include "utils/Errors.hpp"

bool g_hadError = false;

void error(std::size_t line, std::string_view message)
{
    report(line, "", message);
}

void report(std::size_t line, std::string_view where, std::string_view message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << '\n';
    g_hadError = true;
}