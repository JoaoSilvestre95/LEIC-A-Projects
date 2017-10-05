%option c++ yyclass="xpl_scanner" outfile="xpl_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
/* $Id: xpl_scanner.l,v 1.10 2017/05/15 23:14:36 ist180996 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "xpl_scanner.h"
#include "xpl_parser.tab.h"

// don't change this
#define yyerror LexerError

%}

INTEGER 0|([1-9][0-9]*)
HEXADECIMAL 0[xX][0-9a-fA-F]+ 

REAL_1    [0-9]+\.[0-9]*([eE][0-9]+)?
REAL_2    \.[0-9]+([eE][0-9]+)?
REAL  {REAL_1}|{REAL_2}

%x X_STRING X_STRING_S X_COMMENT
%%

">="                   return tGE; 
"<="                   return tLE; 
"=="                   return tEQ; 
"!="                   return tNE; 

"!!"                   return tPRINTLN;

"while"                return tWHILE; 
"if"                   return tIF; 
"elsif"                return tELSIF;
"else"                 return tELSE;  
"begin"                return tBEGIN; 
"end"                  return tEND;
"sweep"                return tSWEEP;
"real"                 return tREALTEXT;
"int"                  return tINT;
"string"               return tSTR;
"procedure"            return tPROCEDURE;
"public"               return tPUBLIC;
"use"                  return tUSE;
"next"                 return tNEXT;
"null"                 return tNULL;
"stop"                 return tSTOP;
"return"               return tRETURN;


[A-Za-z_][A-Za-z0-9_]*  yylval.s = new std::string(yytext); return tIDENTIFIER;


\"                     yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"           yy_pop_state(); return tSTRING;
<X_STRING>\\\"         *yylval.s += yytext + 1;
<X_STRING>\\           yy_push_state(X_STRING_S);
<X_STRING>.            *yylval.s += yytext;
<X_STRING>\n           yyerror("newline in string");

<X_STRING_S>n                           {yy_pop_state(); *yylval.s += std::string(1,10);}
<X_STRING_S>r                           {yy_pop_state(); *yylval.s += std::string(1,13);}
<X_STRING_S>t                           {yy_pop_state(); *yylval.s += std::string(1,9);}
<X_STRING_S>[\"\\]                      {yy_pop_state(); *yylval.s += std::string(1, (int)*yytext);}
<X_STRING_S>[0-9a-fA-F][0-9a-fA-F]?     {yy_pop_state(); *yylval.s += std::string(1, strtol(yytext, nullptr, 16));}
<X_STRING_S>.|\n                        yyerror("Invalid special character");

"/*"            yy_push_state(X_COMMENT);
<X_COMMENT>"/*" yy_push_state(X_COMMENT);
<X_COMMENT>"*/" yy_pop_state();
<X_COMMENT>.|\n ;

"//".*$         ;

{HEXADECIMAL}   {yylval.i = strtol(yytext, nullptr, 16); if(errno == ERANGE) yyerror("Overflow occurred"); return tINTEGER;}
{INTEGER}   {yylval.i = strtol(yytext, nullptr, 10); if(errno == ERANGE) yyerror("Overflow occurred"); return tINTEGER;}
{REAL}  {yylval.d = strtod(yytext, nullptr); if(errno == ERANGE) yyerror("Overflow occurred"); return tREAL;}

0[0-9]+                 yyerror("Number malformed");

[,;()!]                return *yytext; /*delimiter*/
[-=+*/%<>?{}~|:\&@]    return *yytext; 
"["|"]"                return *yytext;

[ \t\n\r]+               ; /* ignore whitespace */

.                      yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int xpl_scanner::yywrap() { return 1; }
