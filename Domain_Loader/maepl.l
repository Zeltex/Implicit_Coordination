%{
  #include "maepl.tab.h"
  #include <string>

  int line_num = 1;
%}


%option noyywrap 

%%
[ \t]          ;
("("|"["|"{")		{ return LBRACK; }
(")"|"]"|"}")		{ return RBRACK; }
_domain				{ return DOMAIN_DEF; }
_action				{ return ACTION_DEF; }
sNaZZle				{ return SNAZZLE; }
type				{ return TYPE; }
end					{ return END; }
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