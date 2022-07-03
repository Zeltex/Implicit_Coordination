#include "Loader.hpp"


//extern int yylex(); 
extern int yyparse();
extern FILE* yyin;
extern int line_num;

namespace del {
    Loader::Loader(const std::string& file_path)
        : lexer(file_path), parser(&lexer)
    {
    }

    std::unique_ptr<General_Domain> Loader::get()
    {
        return parser.get();
    }
}
