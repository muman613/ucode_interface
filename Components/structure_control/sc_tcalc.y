/* sc_tcalc.y - Parsing arithmetic expressions */

%{

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

//extern int value ;
int value = 0;

extern "C" {
	int yylex(void);
	int yyparse(void);
	int yywrap(void);
	int yyparse_file(FILE* fIn);
	int parse_expression(const char* szExpression);
	int calculate_sizeof(char* szSymbol);
};

void yyerror(const char *str)
{
//	fprintf(stderr,"Parser: %s\n",str);
    return;
}

#define E(x) /* (x) */


%}

/* BISON Declarations */
%token NEWLINE PLUS MINUS SLASH ASTERISK LPAREN RPAREN SHIFTLEFT ENUM

%union
{
        int number;
        char *string;
}

%token <number> NUMBER
%token <string> SYMBOL
%token <number> SIZEOF

%type <number> expr
%type <number> term
%type <number> factor

/* Grammar follows */
%%
input:              /* empty string */
    | input line
    ;
line: NEWLINE
    | expr NEWLINE           {  value = (int)$1; }
    ;
expr: expr PLUS term         { E(printf("expr PLUS term\n")); $$ = $1 + $3; }
    | expr MINUS term        { E(printf("expr MINUS term\n")); $$ = $1 - $3; }
    | term                   { E(printf("term %d\n", $$)); $$ = $1; }
    ;
term: term ASTERISK factor   { E(printf("term ASTERISK factor\n")); $$ = $1 * $3; }
    | term SLASH factor      { E(printf("term SLASH factor\n")); $$ = $1 / $3; }
	| term SHIFTLEFT factor  { E(printf("term SHIFTLEFT factor\n")); $$ = $1 << $3; }
    | factor                 { E(printf("factor %d\n", $1)); $$ = $1; }
    ;
factor:  LPAREN expr RPAREN  { $$ = $2; }
      | NUMBER               { $$ = $1; }
      | SIZEOF LPAREN ENUM SYMBOL RPAREN { $$ = 4; }
      | SIZEOF LPAREN SYMBOL RPAREN { $$ = calculate_sizeof($3); }
      ;
%%
/*--------------------------------------------------------*/
/* Additional C code */
/* Error processor for yyparse */
#include <stdio.h>
#include "sc_lexer.h"

int parse_expression(const char* szExpression) {
	int result = -1;

    value = 0;
//  printf("parse_expression(%s)\n", szExpression);

	if (szExpression != 0L) {
		struct yy_buffer_state*  pBuffer = 0L;

		yyrestart(yyin);
		pBuffer = yy_scan_string(szExpression);
		yy_switch_to_buffer(pBuffer);
		yyparse();
        E(printf("final result = %d\n", value));
		result = value;
		yy_delete_buffer(pBuffer);
	}

	return result;
}


int calculate_sizeof(char* szSymbol) {
    int size = 0;

    E(printf("calculating sizeof(%s)\n", szSymbol));

    if (strcmp(szSymbol, "RMuint32") == 0) {
        size = 4;
    } else if (strcmp(szSymbol, "RMuint16") == 0) {
        size = 2;
    } else if (strcmp(szSymbol, "RMuint8") == 0) {
        size = 1;
    } else if (strcmp(szSymbol, "RMbool") == 0) {
        size = 1;
    } else {
        /* */
    }

    return size;
}
