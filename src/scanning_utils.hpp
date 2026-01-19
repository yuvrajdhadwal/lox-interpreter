#pragma once

// #include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

std::string read_file_contents(const std::string& filename);
void parse_characters(std::string_view file_contents, int& exit_code);
void parse_string_literal(std::string_view file_contents, size_t& i, int& line_number, int& exit_code);
void parse_relational_op(std::string_view file_contents, size_t& i);
void parse_number(std::string_view file_contents, size_t& i);
bool is_identifier(char c);
void parse_identifier(std::string_view file_contents, size_t& i);