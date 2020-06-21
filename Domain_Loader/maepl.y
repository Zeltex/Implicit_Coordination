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
  bool bval;
}

// define the constant-string tokens:

%token ACTION_DEF
%token ANNOUNCE_DEF
%token DEFINE_DEF
%token DESIGNATED_EVENTS_DEF
%token DESIGNATED_WORLDS_DEF
%token DOMAIN_DEF
%token EFFECT_ADD_DEF
%token EFFECT_DELETE_DEF
%token EVENT_DEF
%token GOAL_DEF
%token INIT_DEF
%token OBJECTS_DEF
%token OWNER_DEF
%token PRECONDITIONS_DEF
%token PROBLEM_DEF
%token PROPOSITIONS_DEF
%token REACHAbility_DEF
%token REFLEXIVITY_DEF
%token TYPES_DEF
%token WORLD_DEF

%token LBRACK
%token RBRACK

%token AND
%token OR
%token NOT


%token <sval> NAME
%token <bval> TRUTH

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
    |DOMAIN_DEF NAME LBRACK                                     { domain->new_domain(std::string($2));                                  }
       domain_body RBRACK                                       { domain->finish_domain();                                              } maepl
    | PROBLEM_DEF NAME LBRACK
        problem_body RBRACK                                     { if (buffer->is_reflexive()) domain->create_reflexive_reachables();
                                                                  domain->finish_problem();                                             } maepl  

domain_body:
     announce_container types_container propositions_container actions

problem_body:
    | DOMAIN_DEF EQUALS NAME                                    { domain->set_domain($3);                                               } problem_body
    | OBJECTS_DEF EQUALS LBRACK objects RBRACK                  { domain->set_objects(buffer->get_objects());                           } problem_body
    | INIT_DEF EQUALS LBRACK proposition_instances RBRACK       { domain->set_initial_propositions(buffer->get_proposition_instances());} problem_body
    | WORLD_DEF NAME LBRACK proposition_instances RBRACK        { domain->create_world($2, buffer->get_proposition_instances());        } problem_body
    | GOAL_DEF EQUALS LBRACK formula RBRACK                     {                                                                       } problem_body
    | DESIGNATED_WORLDS_DEF EQUALS LBRACK variables RBRACK      { domain->set_designated_worlds(buffer->get_variables());               } problem_body
    | REACHAbility_DEF EQUALS LBRACK reachability_body RBRACK   {                                                                       } problem_body
    | REFLEXIVITY_DEF EQUALS TRUTH                              { buffer->set_reflexivity($3);                                          } problem_body

reachability_body:
    | NAME EQUALS LBRACK bracketed_input RBRACK                 { domain->add_reachability($1, buffer->get_inputs());                   } reachability_body

goal_body:
    | 


objects:
    | NAME EQUALS LBRACK variables RBRACK    { buffer->set_object_type($1);
                                               buffer->push_objects();                                      } objects

announce_container:
    | ANNOUNCE_DEF EQUALS TRUTH              { if ($3) domain->set_announce_enabled();            } 

types_container:                             { std::cerr << "Missing types definition\n";                   }    
    | TYPES_DEF EQUALS LBRACK        
        variables RBRACK                     { buffer->push_types(); 
                                               domain->set_types(buffer->get_types());                      }

proposition_instance:
    NAME LBRACK ordered_variables RBRACK  {buffer->push_proposition_instance($1);                           } 


propositions_container:                      { std::cerr << "Missing propositions definition\n";            }    
    | PROPOSITIONS_DEF EQUALS LBRACK        
        propositions RBRACK                 

proposition:
    | NAME LBRACK input RBRACK               { domain->add_proposition($1, buffer->get_inputs());           }    
           

bracketed_input:
    | LBRACK NAME NAME RBRACK                { buffer->add_input($2, $3);                                   } bracketed_input

input:                                       
    | NAME NAME                              { buffer->add_input($1, $2);                                   } input           
                                             
action:                                      
    ACTION_DEF NAME                          { domain->new_action(std::string($2));                         }
    LBRACK input RBRACK                      { domain->set_action_input(buffer->get_inputs());              }
    LBRACK action_body                       
    RBRACK                                   { domain->finish_action();                                     }
                                             
action_body:                                 
    | OWNER_DEF EQUALS NAME                  { domain->set_action_owner($3);                                } action_body
    | EVENT_DEF NAME LBRACK                  { buffer->set_event_name($2);                                  } 
        event_body RBRACK                    { domain->create_event(                                        
                                                 buffer->get_event_name(),                                  
                                                 buffer->get_event_preconditions(),                         
                                                 buffer->get_event_add_list(),                              
                                                 buffer->get_event_delete_list());                          } action_body
    | DESIGNATED_EVENTS_DEF EQUALS LBRACK    { buffer->clear_designated_events();                           }       
        designated_events_body RBRACK        { domain->set_designated_events(buffer->get_designated_events());} action_body

designated_events_body:
    | NAME                                   { buffer->add_designated_event($1);                            } designated_events_body     
                                             
event_body:                                  
    | PRECONDITIONS_DEF EQUALS LBRACK        { buffer->clear_formula();                                     } 
        formula_single RBRACK                {                                                              } event_body
    | EFFECT_DELETE_DEF EQUALS               { buffer->clear_variable_list();                               } 
        bracketed_propositions_instances     { buffer->push_event_delete_list();                            } event_body
    | EFFECT_ADD_DEF EQUALS                  { buffer->clear_variable_list();                               }
        bracketed_propositions_instances     { buffer->push_event_add_list();                               } event_body
                                             
                                             
                                             
variables_container:                         
    | LBRACK variables RBRACK                {                                                              }
                                             
formula_container:                           
    | LBRACK formula_single RBRACK           {                                                              }
                                             
formula:                                     
    | proposition_instance                   {buffer->push_pop_formula();                                 } 
    | proposition_instance                   {buffer->push_pop_formula();                                 } formula
    | AND LBRACK                             {buffer->push_formula("And");                                  }
        formula RBRACK                       {buffer->pop_formula();                                        } formula
    | OR LBRACK                              {buffer->push_formula("Or");                                   }
        formula RBRACK                       {buffer->pop_formula();                                        } formula
    | NOT LBRACK                             {buffer->push_formula("Not");                                  }
        formula_single RBRACK                {buffer->pop_formula();                                        } formula
                                             
                                             
formula_single:                              
    | proposition_instance                   {buffer->push_pop_formula();                                 }
    | AND LBRACK                             {buffer->push_formula("And");                                  }
        formula RBRACK                       {buffer->pop_formula();                                        }
    | OR LBRACK                              {buffer->push_formula("Or");                                   }
        formula RBRACK                       {buffer->pop_formula();                                        }
    | NOT LBRACK                             {buffer->push_formula("Not");                                  }
        formula_single RBRACK                {buffer->pop_formula();                                        }

variable: NAME                               { buffer->add_variable($1);                                    }

bracketed_propositions_instances:
    LBRACK proposition_instances RBRACK ;

proposition_instances:
    | proposition_instance proposition_instances ;

propositions:
  propositions proposition
  | proposition ;

actions:
  actions action
  | action ;

variables:
  | variables variable
  | variable ;

ordered_variables:
  | NAME                                    {buffer->add_ordered_variable($1);                               } ordered_variables
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
