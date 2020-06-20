%{
  #include <cstdio>
  #include <iostream>
  using namespace std;
  #include "Maepl.hpp"
  #include "Domain_Buffer.hpp"

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
  extern int line_num;
 
  void yyerror(const char *s);

  Domain_Interface* domain;
  Domain_Buffer* buffer;
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
%token OWNER_DEF
%token PRECONDITIONS_DEF
%token EVENT_DEF
%token EFFECT_DELETE_DEF
%token EFFECT_ADD_DEF

%token AND
%token OR
%token NOT


%token <sval> NAME

%token EQUALS

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING


%%


// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "snazzle file":
maepl: 
    DOMAIN_DEF NAME LBRACK                  { domain->new_domain(std::string($2));      }
    actions RBRACK                          { domain->finish_domain();                  }

  ;

action:
    ACTION_DEF NAME                         { domain->new_action(std::string($2));      }
    LBRACK action_input RBRACK
    LBRACK action_body
    RBRACK                                  { domain->finish_action();                  }

action_input:
    | NAME NAME                             { domain->add_action_input($1, $2);         }
        action_input


action_body:
    | OWNER_DEF EQUALS NAME                 { domain->set_action_owner($3);             } action_body
    | EVENT_DEF NAME LBRACK                 { buffer->set_event_name($2);                    } 
        event_body RBRACK                   { domain->create_event(buffer->get_event_name(), buffer->get_event_preconditions(), buffer->get_event_add_list(), buffer->get_event_delete_list());    } action_body

event_body:
    | PRECONDITIONS_DEF EQUALS LBRACK   { buffer->clear_formula();                  } 
        formula RBRACK                  {                                           } event_body
    | EFFECT_DELETE_DEF EQUALS          { buffer->clear_variable_list();            } 
        variables_container             {  buffer->push_event_delete_list();        } event_body
    | EFFECT_ADD_DEF EQUALS             { buffer->clear_variable_list();            }
        variables_container             { buffer->push_event_add_list();            } event_body



variables_container:
    | LBRACK variables RBRACK           {                                           }

formula_container:
    | LBRACK formula_single RBRACK      {                                           }

formula: 
    | NAME                                {buffer->push_pop_formula("Prop", $1);      } 
    | NAME                              {buffer->push_pop_formula("Prop", $1);      } formula
    | AND LBRACK                        {buffer->push_formula("And");               }
        formula RBRACK                  {buffer->pop_formula();                     } formula
    | OR LBRACK                         {buffer->push_formula("Or");                }
        formula RBRACK                  {buffer->pop_formula();                     } formula
    | NOT LBRACK                        {buffer->push_formula("Not");               }
        formula_single RBRACK           {buffer->pop_formula();                     } formula


formula_single: 
    | NAME                                {buffer->push_pop_formula("Prop", $1);      }
    | AND LBRACK                        {buffer->push_formula("And");               }
        formula RBRACK                  {buffer->pop_formula();                     }
    | OR LBRACK                         {buffer->push_formula("Or");                }
        formula RBRACK                  {buffer->pop_formula();                     }
    | NOT LBRACK                        {buffer->push_formula("Not");               }
        formula_single RBRACK           {buffer->pop_formula();                     }

variable: NAME                                      { buffer->add_variable($1);                  }

actions:
  actions action
  | action ;

variables:
  | variables variable
  | variable ;

ENDLS:
  ENDLS ENDL
  | ENDL ;

%%

void parse_domain(Domain_Interface* domain_input, Domain_Buffer* buffer_input, FILE* file_in) {
    domain = domain_input;
    buffer = buffer_input;
    yyin = file_in;
    yyparse();
}

void yyerror(const char *s) {
  std::cout << "EEK, parse error on line " << line_num << "!  Message: " << s << std::endl;
  // might as well halt now:
  exit(-1);
}
