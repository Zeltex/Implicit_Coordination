%{
  #include "snazzle.tab.h"
  int line_num = 1;
%}


%option noyywrap 

%%
[ \t]          ;
sNaZZle        { return SNAZZLE; }
type           { return TYPE; }
end            { return END; }
[0-9]+\.[0-9]+ { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+         { yylval.ival = atoi(yytext); return INT; }
[a-zA-Z0-9]+   {
  yylval.sval = _strdup(yytext);
  return STRING;
}
\n             { ++line_num; return ENDL; }
.              ;
%%