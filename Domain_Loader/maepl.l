%{
  #include "maepl.tab.h"
  #include <string>

  int line_num = 1;
%}


%option noyywrap 

%%
[ \t]          ;
("("|"["|"{")		{ return LBRACK;			}
(")"|"]"|"}")		{ return RBRACK;			}
=					{ return EQUALS;			}
_domain				{ return DOMAIN_DEF;		}
_action				{ return ACTION_DEF;		}
_owner				{ return OWNER_DEF;			}
_preconditions		{ return PRECONDITIONS_DEF;	}
_effect_add			{ return EFFECT_ADD_DEF;	}
_effect_delete		{ return EFFECT_DELETE_DEF;	}
_event				{ return EVENT_DEF;	}


AND					{ return AND;				}		
OR					{ return OR;				}		
NOT					{ return NOT;				}		


sNaZZle				{ return SNAZZLE;			}
type				{ return TYPE;				}
end					{ return END;				}
[0-9]+\.[0-9]+		{ yylval.fval = atof(yytext); return FLOAT; }
[0-9]+				{ yylval.ival = atoi(yytext); return INT; }
[a-zA-Z0-9]+		{
  yylval.sval = _strdup(yytext);
  return NAME;
}
\n             { ++line_num; }
","				;
.              ;
%%