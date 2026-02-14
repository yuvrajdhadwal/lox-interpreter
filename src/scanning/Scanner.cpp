#include "scanning/Scanner.hpp"

Scanner::Scanner(std::string_view source)
    : m_source {source} {}

auto Scanner::scanTokens() -> std::vector<Token>
{
    while (!isAtEnd())
    {
        m_start = m_current;
        scanToken();
    }

    m_tokens.emplace_back(TokenType::END_FILE, "", std::nullopt, m_line);
    return m_tokens;
}

void Scanner::scanToken()
{
    char curr_c {advance()};

    switch (curr_c)
    {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;

        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;

        case '/':
            if (match('/')) { while (peek() != '\n' && !isAtEnd()) { advance(); }}
            else { addToken(TokenType::SLASH); }
            break;

        case ' ':
        case '\r':
        case '\t':
            break;  // ignoring whitespace
        
        case '\n': m_line++; break;

        case '"': scanString(); break;

        default: 
            if (isDigit(curr_c)) { scanNumber(); }
            else if (isAlpha(curr_c)) { scanIdentifier(); }
            else { error(m_line, "Unexpected character."); }
            break;
    }
}

void Scanner::scanString()
{
    while (!isAtEnd() && peek() != '"')
    {
        if (peek() == '\n') { ++m_line; }
        advance();
    }

    if (isAtEnd())
    {
        error(m_line, "Unterminated string.");
        return;
    }

    advance();  // advance past end quote

    std::string value {m_source.substr(m_start + 1, m_current - m_start - 2)};  // trimming quotes
    addToken(TokenType::STRING, value);
}

void Scanner::scanNumber()
{
    while (isDigit(peek())) { advance(); }

    // checking for decimal
    if (peek() == '.' && isDigit(peekNext()))
    {
        advance();  // skipping decimal

        while (isDigit(peek())) { advance(); }
    }

    addToken(TokenType::NUMBER, std::stod(m_source.substr(m_start, m_current - m_start - 1)));
}

static const std::unordered_map<std::string, TokenType> g_keywords
{
    {"and",     TokenType::AND},
    {"class",   TokenType::CLASS},
    {"else",    TokenType::ELSE},
    {"false",   TokenType::FALSE},
    {"for",     TokenType::FOR},
    {"fun",     TokenType::FUN},
    {"if",      TokenType::IF},
    {"nil",     TokenType::NIL},
    {"or",      TokenType::OR},
    {"print",   TokenType::PRINT},
    {"return",  TokenType::RETURN},
    {"super",   TokenType::SUPER},
    {"this",    TokenType::THIS},
    {"true",    TokenType::TRUE},
    {"var",     TokenType::VAR},
    {"while",   TokenType::WHILE}
};

void Scanner::scanIdentifier()
{
    while (isAlphaNumeric(peek())) { advance(); }

    std::string text {m_source.substr(m_start, m_current - m_start - 1)};
    auto iter {g_keywords.find(text)};
    TokenType type{};

    if (iter == g_keywords.end()) { type = TokenType::IDENTIFIER; }
    else { type = iter->second; }

    addToken(type);
}

void Scanner::addToken(TokenType type, const Literal& literal)
{
    std::string_view text {m_source.substr(m_start, m_current - m_start - 1)};
    m_tokens.emplace_back(type, text, literal, m_line);
}

auto Scanner::match(char expected) -> bool
{
    if (isAtEnd()) { return false; }
    if (m_source[m_current] != expected) { return false; }

    m_current++;
    return true;
}

auto Scanner::peekNext() -> char
{
    if (m_current + 1 >= m_source.length()) { return '\0'; }
    return m_source[m_current + 1];
}