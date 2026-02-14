#pragma once

#include <cstdint>

enum class ErrorEnums : uint8_t
{
    no_error = 0,
    unknown_command = 1,
    lox_error = 65,
};