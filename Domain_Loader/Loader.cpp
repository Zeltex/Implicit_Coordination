#include "Loader.hpp"


//extern int yylex(); 
extern int yyparse();
extern FILE* yyin;
extern int line_num;


void Loader::parse(Domain_Interface* domain, std::string file_path) {
	domain->set_debug_working();
    
    //FILE* myfile = fopen_s(file_path.c_str(), "r");
    FILE* myfile;
    fopen_s(&myfile, file_path.c_str(), "r");
    if (!myfile) {
        std::cout << "I can't open in.snazzle!" << std::endl;
        return;
    }
    // Set Flex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    //// Parse through the input:
    yyparse();
}