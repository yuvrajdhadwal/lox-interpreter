#pragma once

#include "common/TokenType.hpp"

#include <string_view>
#include <optional>
#include <variant>
#include <sstream>
#include <utility>
#include <iomanip>

// someone else on code crafters came up with this
using Literal = std::optional<std::variant<std::monostate, std::string, double>>;

class Token
{
public:
    Token(TokenType type, std::string_view lexeme, Literal literal, int line);
    [[nodiscard]] auto to_string() const -> std::string;

private:
    TokenType m_token;
    std::string m_lexeme;
    Literal m_literal;
    int m_line;
};