#pragma once

#include <iostream>
#include <string_view>

extern bool g_hadError;
void error(std::size_t line, std::string_view message);
void report(std::size_t line, std::string_view where, std::string_view message);