%{
  #include <cstdio>
  #include <iostream>
  using namespace std;
  #include "Maepl.hpp"

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
  extern int line_num;
 
  void yyerror(const char *s);

  Domain_Interface* domain;
%}


%union {
  int ival;
  float fval;
  char *sval;
}

// define the constant-string tokens:
%token SNAZZLE TYPE
%token END ENDL
%token LBRACK
%token RBRACK
%token DOMAIN_DEF
%token DEFINE_DEF
%token ACTION_DEF
%token <sval> NAME

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING


%%


// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "snazzle file":
maepl: 
    DOMAIN_DEF NAME LBRACK {
      domain->new_domain(std::string($2))
    }
    actions RBRACK {
        domain->finish_domain();
    }

  ;

action:
    ACTION_DEF NAME                     { domain->new_action(std::string($2));}
    LBRACK ACTION_INPUT RBRACK
    LBRACK 
    RBRACK                       { domain->finish_action();}

ACTION_INPUT:
    | NAME NAME                     { domain->add_action_input($1, $2); }
        ACTION_INPUT


actions:
  actions action
  | action ;

ENDLS:
  ENDLS ENDL
  | ENDL ;

%%

void parse_domain(Domain_Interface* domain_input, FILE* file_in) {
    domain = domain_input;
    yyin = file_in;
    yyparse();
}

void yyerror(const char *s) {
  std::cout << "EEK, parse error on line " << line_num << "!  Message: " << s << std::endl;
  // might as well halt now:
  exit(-1);
}
