#pragma once

#include <iostream>
#include <string_view>

class ErrorHandling
{
    public:
    
    static void lox_error(int line, std::string_view msg);
    static bool had_error_;
};
