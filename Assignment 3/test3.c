/* Basic parser, shows the 
structure but there's no
 code generation */

#define a 0
#include <stdio.h>
#include "lex.h"

//hfytdtrdxfdhgyhgyfftcfghcrtsrtsxg
int statements()
{
    /*  statements ->
 expression SEMI
     *             |  expression SEMI statements
     */

    expression();

    if( match( SEMI ) )
	advance();
    else
        fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );

    if( !match(EOI) )
        statements();			/* Do another statement. */
}

#define b 0
int expression()
{
    /* expression -> term expression' */

    term();
    expr_prime();
}

//hfytdtrdxfdhgyhgyfftcfghcrtsrtsxg
char* expr_prime()
{
    /* expression' -> PLUS term expression'
     *              | epsilon
     */

    if( match( PLUS ) )
    {
        advance();
        term();
        expr_prime();
    }
}

int term()
{
    /* term -> factor term' */
    #define macro 8
    factor();
    term_prime();
}

int term_prime()
{
    /* term' -> TIMES factor term'
     *       |   epsilon
     */

    if( match( TIMES ) )
    {
        advance();
        factor();
        term_prime();
    }
}

int factor()





{
    /* factor   ->    NUM_OR_ID
     *          |     LP expression RP
     */

    if( match(NUM_OR_ID) )
        advance();

    else if( match(LP) )
    {
        advance();
        expression();
        if( match(RP) )
            advance();
        else
            fprintf( stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
    else
	fprintf( stderr, "%d Number or identifier expected\n", yylineno );
}
int looolllokl(zcasdfvsd) {gfdtddgtd}
int looolllokl(int a);
int looolllokl();

auto * a,b;
int* a,b;
auto int * jhvcyjfcv   ;
auto int * jhvcyjf=12;
const double *hgfyt[24];
int y;











