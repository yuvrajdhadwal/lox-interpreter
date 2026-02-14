#include <iostream>
#include <string_view>
#include <vector>

void defineAST(std::string_view outputDir, std::string_view baseName,
    const std::vector<std::string_view>& productions);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./generateAST <output_directory>\n";
        return 64;
    }

    std::string outputDir {argv[1]};

    std::cout << outputDir << '\n';

    defineAST(outputDir, "Expr", std::vector<std::string_view> {
      "Binary   : Expr left, Token operator, Expr right",
      "Grouping : Expr expression",
      "Literal  : Object value",
      "Unary    : Token operator, Expr right"
    });

    return 0;
}