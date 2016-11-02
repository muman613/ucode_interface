%{
// sc_lexer.l -- Parsing arithmetic expression

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sc_tcalc.hpp"
#include "dbgutils.h"

extern "C" {
    int yylex(void);
};

extern YYSTYPE yylval;

#define ECHO  /*  */

#define E(x)  /*  (x) */

%}

%option noyywrap
%option nounput

delim         [ \t]
whitesp       {delim}+
symbol		  [a-zA-Z0-9]+
digit         [0-9]
number        {digit}*[.]?{digit}+
hexdigit	  [0-9a-fA-F]
hexnumber	  0x{hexdigit}+

%%

{number}    { sscanf(yytext, "%d", (int *)&yylval.number); E(printf("NUMBER %d ", (int)yylval.number)); return NUMBER;}
{hexnumber} { sscanf(yytext, "0x%08x", (int *)&yylval.number); E(printf("HEXNUMBER %d", yylval.number)); return NUMBER; }
"+"         { E(printf("PLUS ")); return PLUS; }
"-"         { E(printf("MINUS ")); return MINUS; }
"/"         { E(printf("SLASH ")); return SLASH; }
"*"         { E(printf("ASTERISK ")); return ASTERISK; }
"("         { E(printf("LPAREN ")); return LPAREN; }
")"         { E(printf("RPAREN ")); return RPAREN; }
"<<"	    { E(printf("SHIFTLEFT ")); return SHIFTLEFT; }
"\n"        { E(printf("\n")); return NEWLINE; }
"sizeof"    { E(printf("SIZEOF ")); return SIZEOF; }
"enum"	    { E(printf("ENUM ")); return ENUM; }
{symbol}  { E(printf("SYMBOL ")); yylval.string = strdup(yytext); return SYMBOL; }
{whitesp}   { /* No action and no return */}

