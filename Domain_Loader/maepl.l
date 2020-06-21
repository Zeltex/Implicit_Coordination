%{
  #include "maepl.tab.h"
  #include <string>
  #include <iostream>

  int line_num = 1;
%}


%option noyywrap 

%%
[ \t]          ;
("("|"["|"{")		{ return LBRACK;				}
(")"|"]"|"}")		{ return RBRACK;				}
=					{ return EQUALS;				}


_action				{ return ACTION_DEF;			}
_announce_enabled	{ return ANNOUNCE_DEF;			}
_designated_events	{ return DESIGNATED_EVENTS_DEF;	}
_designated_worlds  { return DESIGNATED_WORLDS_DEF; }
_domain				{ return DOMAIN_DEF;			}
_effect_add			{ return EFFECT_ADD_DEF;		}
_effect_delete		{ return EFFECT_DELETE_DEF;		}
_event				{ return EVENT_DEF;				}
_goal				{ return GOAL_DEF;				}
_initial_state  	{ return INIT_DEF;				}
_objects			{ return OBJECTS_DEF;			}
_owner				{ return OWNER_DEF;				}
_preconditions		{ return PRECONDITIONS_DEF;		}
_problem			{ return PROBLEM_DEF;			}
_propositions		{ return PROPOSITIONS_DEF;		}	
_reachability		{ return REACHAbility_DEF;		}
_reflexivity		{ return REFLEXIVITY_DEF;		}
_types				{ return TYPES_DEF;				}
_world				{ return WORLD_DEF;				}

true				{ yylval.bval = true; 
					  return TRUTH;					}
false				{ yylval.bval = false; 
					  return TRUTH;					}

AND					{ return AND;					}		
OR					{ return OR;					}		
NOT					{ return NOT;					}		

[0-9]+\.[0-9]+		{ yylval.fval = atof(yytext); return FLOAT; }
[0-9]+				{ yylval.ival = atoi(yytext); return INT; }
[a-zA-Z][a-zA-Z0-9_]*		{
  yylval.sval = _strdup(yytext);
  return NAME;
}
\n             { ++line_num; }
","				;
.              std::cout << "matched unknown sequence: " << yytext << "\n";
%%