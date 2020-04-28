%option yylineno

%{
#include <bits/stdc++.h>
#include "bas.tab.h"
void yyerror(char *);
%}

printable [\x20-\x7E]  

%%


[ \n\t\r]+                      ;/* ignore whitespaces */
"/*"{printable}*"*/"            ;/* Ignore Comments */

"const"							{return CONST;}
"int"							{return INT;}
"float"							{return FLOAT;}
"char"							{return CHAR;}
"bool"							{return BOOL;}

"true"                          {return B_TRUE;}
"false"                         {return B_FALSE;}

"{"								{return '{';}
"}"								{return '}';}
"("								{return '(';}
")"								{return ')';}
";"								{return ';';}

"="								{return '=';}
"+"								{return '+';}
"-"								{return '-';}
"*"								{return '*';}
"/"								{return '/';}

[a-zA-Z_][a-zA-Z_0-9]*			{yylval.val = strdup(yytext);  return VAR;}
[+-]?[0-9]+						{yylval.val = strdup(yytext);  return INTEGER;}
[+-]?[0-9]+['.'][0-9]*			{yylval.val = strdup(yytext);  return DECIMAL;}
\'.?\'							{yylval.val = strdup(yytext);  return CHARACTER;}

<<EOF>>							{return ENDOFFILE;}

.                               yyerror("Unknown Token");
%%


int yywrap(void){
	return 1;
}