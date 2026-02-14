#include "common/Token.hpp"

#include <utility>

Token::Token(TokenType type, std::string_view lexeme, Literal literal, int line)
	: m_token(type), m_lexeme(lexeme), m_literal(std::move(literal)), m_line(line) {}

// thanks to someone on codecrafters
static auto literal_to_string(const Literal &literal) -> std::string
{
	if (!literal) { return "null"; }
	if (std::holds_alternative<std::monostate>(*literal)) { return "nil"; }
	if (std::holds_alternative<std::string>(*literal)) { return std::get<std::string>(*literal); }

	double value = std::get<double>(*literal);

	std::ostringstream oss;
	const int max_precision{10};
	oss << std::fixed << std::setprecision(max_precision) << value;
	std::string str = oss.str();

	// Remove trailing zeros after decimal
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	if (str.back() == '.')
	{
		str += '0';
	}

	return str;
}

static auto token_type_to_string(TokenType type) -> std::string_view
{
	switch (type)
	{
	case TokenType::LEFT_PAREN:
		return "LEFT_PAREN";
	case TokenType::RIGHT_PAREN:
		return "RIGHT_PAREN";
	case TokenType::LEFT_BRACE:
		return "LEFT_BRACE";
	case TokenType::RIGHT_BRACE:
		return "RIGHT_BRACE";
	case TokenType::COMMA:
		return "COMMA";
	case TokenType::DOT:
		return "DOT";
	case TokenType::MINUS:
		return "MINUS";
	case TokenType::PLUS:
		return "PLUS";
	case TokenType::SEMICOLON:
		return "SEMICOLON";
	case TokenType::SLASH:
		return "SLASH";
	case TokenType::STAR:
		return "STAR";

	case TokenType::BANG:
		return "BANG";
	case TokenType::BANG_EQUAL:
		return "BANG_EQUAL";
	case TokenType::EQUAL:
		return "EQUAL";
	case TokenType::EQUAL_EQUAL:
		return "EQUAL_EQUAL";
	case TokenType::GREATER:
		return "GREATER";
	case TokenType::GREATER_EQUAL:
		return "GREATER_EQUAL";
	case TokenType::LESS:
		return "LESS";
	case TokenType::LESS_EQUAL:
		return "LESS_EQUAL";

	case TokenType::IDENTIFIER:
		return "IDENTIFIER";
	case TokenType::STRING:
		return "STRING";
	case TokenType::NUMBER:
		return "NUMBER";

	case TokenType::AND:
		return "AND";
	case TokenType::CLASS:
		return "CLASS";
	case TokenType::ELSE:
		return "ELSE";
	case TokenType::FALSE:
		return "FALSE";
	case TokenType::FUN:
		return "FUN";
	case TokenType::FOR:
		return "FOR";
	case TokenType::IF:
		return "IF";
	case TokenType::NIL:
		return "NIL";
	case TokenType::OR:
		return "OR";
	case TokenType::PRINT:
		return "PRINT";
	case TokenType::RETURN:
		return "RETURN";
	case TokenType::SUPER:
		return "SUPER";
	case TokenType::THIS:
		return "THIS";
	case TokenType::TRUE:
		return "TRUE";
	case TokenType::VAR:
		return "VAR";
	case TokenType::WHILE:
		return "WHILE";

	case TokenType::END_FILE:
		return "EOF";
	}
	return "UNKNOWN";
}

auto Token::to_string() const -> std::string
{
	std::ostringstream oss;
	oss << token_type_to_string(m_token) << ' ' << m_lexeme << ' ' << literal_to_string(m_literal);
	return oss.str();
}