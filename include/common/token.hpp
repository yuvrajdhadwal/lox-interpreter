#pragma once

#include "common/token_type_enums.hpp"

#include <string_view>
#include <optional>
#include <variant>
#include <sstream>
#include <utility>
#include <iomanip>

using Literal = std::optional<std::variant<std::monostate, std::string_view, double>>;

class Token
{
    public:
    Token(TokenType type, std::string_view lexeme, Literal literal, int line);
    std::string_view to_string() const;

    TokenType type_;
    std::string_view lexeme_;
    Literal literal_;
    int line_;

    private:

};