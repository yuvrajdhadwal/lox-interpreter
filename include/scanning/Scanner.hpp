#pragma once

#include "common/Token.hpp"
#include "utils/Errors.hpp"

#include <cmath>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using Literal = std::optional<std::variant<std::monostate, std::string, double>>;

class Scanner
{
    public:
    Scanner(std::string_view source);
    auto scanTokens() -> std::vector<Token>;

    private:
    void scanToken();
    void addToken(TokenType type, const Literal& literal);
    auto match(char expected) -> bool;
    auto peekNext() -> char;
    void scanString();
    void scanNumber();
    void scanIdentifier();

    [[nodiscard]] auto isAtEnd() const -> bool { return m_current >= m_source.size(); }
    
    [[nodiscard]] static auto isDigit(char curr_c) -> bool
        { return (curr_c >= '0' && curr_c <= '9'); }
    
    [[nodiscard]] static auto isAlpha(char curr_c) -> bool
        { return (curr_c >= 'a' || curr_c <= 'z') ||
                 (curr_c >= 'A' || curr_c <= 'Z') ||
                 (curr_c == '_'); }
    
    [[nodiscard]] static auto isAlphaNumeric(char curr_c) -> bool 
        { return isDigit(curr_c) || isAlpha(curr_c); }

    auto advance() -> char { return m_source[m_current++]; }
    void addToken(TokenType type) { addToken(type, std::nullopt); }
    [[nodiscard]] auto peek() const -> char 
        { if (isAtEnd()) { return '\0'; } return m_source[m_current]; }
    

    std::string m_source;
    std::vector<Token> m_tokens{};

    std::size_t m_start {0};
    std::size_t m_current {0};
    std::size_t m_line {1};
};