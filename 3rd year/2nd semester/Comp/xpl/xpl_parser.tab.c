/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20150711

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "xpl_parser.y"
/* $Id: xpl_parser.y,v 1.19 2017/05/16 00:39:13 ist180996 Exp $*/
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#line 14 "xpl_parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int                   i;	/* integer value */
  double                d;      /* double value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  xpl::block_node *b;
  basic_type *type;
  
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 56 "xpl_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 54 "xpl_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tINTEGER 257
#define tREAL 258
#define tIDENTIFIER 259
#define tSTRING 260
#define tWHILE 261
#define tIF 262
#define tELSIF 263
#define tELSE 264
#define tPRINTLN 265
#define tBEGIN 266
#define tEND 267
#define tINT 268
#define tREALTEXT 269
#define tPROCEDURE 270
#define tSTR 271
#define tPUBLIC 272
#define tUSE 273
#define tSWEEP 274
#define tNEXT 275
#define tNULL 276
#define tSTOP 277
#define tRETURN 278
#define tIFX 279
#define tEQ 280
#define tNE 281
#define tGE 282
#define tLE 283
#define tUNARY 284
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   10,   10,    1,    1,   11,   11,    4,    2,
    2,    2,    2,    2,    2,   20,   20,   20,   20,   14,
   14,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    6,    6,    9,    9,    9,    7,    7,    7,    7,    7,
   21,   21,   21,   21,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,   17,   17,   17,   17,
   22,   22,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   18,   18,   15,   15,
   19,   19,   12,   12,   13,   13,    8,
};
static const YYINT yylen[] = {                            2,
    1,    0,    1,    2,    1,    1,    1,    2,    2,    3,
    2,    3,    5,    4,    5,    1,    1,    1,    3,    1,
    2,    2,    2,    2,    1,    1,    1,    1,    1,    1,
    5,    6,    5,    6,    2,    5,   10,   12,   10,   12,
    4,    3,    3,    2,    5,    6,    6,    5,    6,    6,
    6,    7,    6,    7,    8,    9,    1,    1,    1,    1,
    1,    2,    1,    2,    2,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    2,    3,    3,    3,    3,    1,
    3,    3,    1,    2,    3,    1,    4,    3,    1,    3,
    1,    4,    1,    0,    1,    3,    2,
};
static const YYINT yydefred[] = {                         0,
   16,   18,    0,   17,    0,    0,    0,    0,    3,    0,
    6,    5,    0,    0,    0,    0,    0,    0,    0,    0,
    9,    4,    0,    0,    0,    0,    0,    0,   19,    0,
    0,   95,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   57,   59,    0,   61,   60,    0,    0,    0,    0,
    0,   80,    0,   63,   86,    0,    0,    0,    0,    0,
   97,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   84,   62,
    0,    0,   53,   96,    0,    0,   50,   47,   88,    0,
    0,   82,   81,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   51,
    0,    0,    0,    0,    0,   25,   26,   27,    0,   44,
    7,   20,   28,   29,    0,    0,    0,    0,   30,   54,
    0,   52,   87,    0,   92,    0,    0,    0,    0,    0,
    0,    0,   42,    8,    0,   43,   21,   24,   22,   23,
    0,    0,    0,   55,    0,    0,    0,    0,    0,    0,
   41,   56,    0,    0,    0,    0,    0,   36,    0,    0,
    0,    0,    0,   32,    0,    0,    0,   35,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   37,
    0,   39,    0,   34,    0,    0,   38,   40,
};
static const YYINT yydgoto[] = {                          8,
    9,   10,   11,   12,  132,  133,  134,   32,  184,   13,
  135,   33,   34,  136,  100,  137,   54,   55,   56,   35,
  139,   57,
};
static const YYINT yysindex[] = {                       -88,
    0,    0, -253,    0,  -73,  -49,  -28,    0,    0,  -24,
    0,    0,  -88, -204,   17, -197, -192, -181, -179,   20,
    0,    0,   -9,  -28,   45,   -8,   54,   -7,    0,  490,
  -28,    0,   55,   51, -147,  -28,  490,  -28,  -28,  490,
  -28,    0,    0,   85,    0,    0,  490,  490,  490,  490,
  490,    0, 1020,    0,    0,  -27, -131,   93,   25,  -28,
    0,   99, 1020,  113,  115, 1020,  120,   75, 1088,   72,
   72,  633,  718,  490,  490,  490,  490,  490,  490,  490,
  490,  490,  490,  490,  490,  490,  490,  490,    0,    0,
  -59, 1145,    0,    0,   25,  -46,    0,    0,    0,   73,
 1020,    0,    0, 1067, 1088, 1109, 1109,    2,    2,    2,
    2,   37,   37,   72,   72,   72,  773, 1020, -220,    0,
  124,  127,  -28,  -28,    3,    0,    0,    0, 1413,    0,
    0,    0,    0,    0, 1167, 1205,  357,  -87,    0,    0,
 -220,    0,    0,  490,    0,   25,  490,  490,  -81,  -72,
  131,  149,    0,    0, 1234,    0,    0,    0,    0,    0,
  142,   25, 1020,    0,  813,  840,  145,  146,  490,  490,
    0,    0,  -23,  -23, 1020,   69,  165,    0, -240,  490,
  490,  170,  -23,    0,  880,  912,  490,    0,  490,  490,
  946,  566,  680,  -23,  -23,  490,  -23,  490, -240,    0,
  973,    0,  984,    0,  -23,  -23,    0,    0,
};
static const YYINT yyrindex[] = {                       217,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  242,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  168,  203,    0,  186,    0,  187,    0,    0,
  203,    0,    0,  216,    0,  203,    0,  203,  203,    0,
  203,    0,    0,  -33,    0,    0,    0,    0,    0,    0,
    0,    0,  200,    0,    0,   64,   28,    0,    1,    0,
    0,    0,  201,    0,    0,  202,    0,    0,  561,  100,
  132,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    7,    0,    0,    0,   13,   19,    0,    0,    0,    0,
  105,    0,    0,  424,  744,  525,  532,  426,  454,  463,
  493,  385,  417,  171,  279,  315,    0,  588,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  168,    0,  109,    0,    0,    0,  186,  187,    0,    0,
    0,    0,    0,    0,    0, 1041, 1041,    0, 1241,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1270,    0,
    0,    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  249,    0,    0,  -76,  634,    0,    0,  207,   95,    0,
    0,  227,    0,  161,    0, 1521,  -98,    0, -119,   76,
   40,    0,
};
#define YYTABLESIZE 1719
static const YYINT yytable[] = {                         91,
   48,  119,    7,   91,   91,   15,   45,   91,   91,   91,
   91,   91,   49,   91,  141,  131,   51,    7,   46,   48,
  146,   49,  182,  183,   91,   91,   91,   91,   91,   91,
   31,   38,   41,   88,   21,   89,   42,   43,   86,   45,
   52,    7,  162,   84,   82,  151,   83,  152,   85,  176,
  177,   30,   37,   40,   23,   46,   24,   91,  154,   91,
   58,   25,    7,   92,   58,   58,   26,   50,   58,   58,
   58,   58,   58,   86,   58,   14,   92,   27,   84,   28,
   17,   19,   20,   85,   36,   58,   58,   58,   14,   58,
   91,   48,   87,   39,   60,   59,   83,   45,   93,   92,
   83,   83,   47,   49,   83,   83,   83,   83,   83,   46,
   83,   61,   29,  143,   51,   99,  144,   48,   58,   49,
   58,   83,   83,   83,   68,   83,  180,   87,   90,   88,
  120,   89,   65,   91,  140,  142,   65,   65,   52,   95,
   65,   65,   65,   65,   65,   89,   65,   92,   89,   90,
   58,   58,   90,   96,   83,   97,   83,   65,   65,   65,
   98,   65,   87,  147,   64,   50,  148,  138,   64,   64,
  169,  161,   64,   64,   64,   64,   64,  167,   64,    1,
    2,    3,    4,    5,    6,  164,  168,   83,  170,   64,
   64,   64,   65,   64,    1,    2,   16,    4,  149,  150,
   47,  172,   30,   68,   20,   37,   40,   68,   68,  187,
  138,   68,   68,   68,   68,   68,    2,   68,    1,    2,
   18,    4,  181,   65,   64,   88,   11,   89,   68,   68,
   68,   91,   68,   42,   43,   44,   45,  121,  122,    1,
    2,    1,    4,   94,   10,   12,   91,   91,   91,   91,
  125,  126,   46,  127,  128,   64,   93,   58,   14,   13,
   15,   22,   62,   68,   64,   65,   94,   67,   48,   48,
   48,   48,   48,   48,   45,   45,   45,   45,   45,   45,
   49,   49,   49,   49,   49,   49,   46,   46,   46,   46,
   46,   46,   58,  204,   68,  155,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   58,   58,   58,
   58,   69,    0,    0,    0,   69,   69,    0,    0,   69,
   69,   69,   69,   69,    0,   69,    0,    0,   83,    0,
    0,   42,   43,   44,   45,    0,   69,   69,   69,    0,
   69,    0,    0,   83,   83,   83,   83,   70,    0,    0,
   46,   70,   70,    0,    0,   70,   70,   70,   70,   70,
    0,   70,    0,    0,   65,    0,    0,    0,    0,    0,
    0,   69,   70,   70,   70,    0,   70,    0,    0,   65,
   65,   65,   65,    0,    0,    0,    0,    0,    0,  160,
    0,    0,    0,   86,   75,    0,   64,    0,   84,   82,
    0,   83,   69,   85,    0,    0,    0,   70,    0,    0,
    0,   64,   64,   64,   64,  159,   81,   66,   80,    0,
    0,    0,   66,    0,    0,   66,    0,   66,   66,   66,
    0,    0,    0,    0,    0,   68,    0,    0,   70,    0,
    0,    0,   66,   66,   66,    0,   66,   87,    0,   67,
   68,   68,   68,   68,   67,    0,   74,   67,   76,   67,
   67,   67,    0,   76,   74,    0,   76,   74,    0,   76,
    0,    0,    0,    0,   67,   67,   67,   66,   67,    0,
   74,   74,   74,   76,   76,   76,   77,   76,    0,    0,
    0,   77,    0,    0,   77,   72,    0,   77,    0,    0,
   72,    0,    0,   72,    0,    0,   72,    0,   66,   67,
    0,   77,   77,   77,    0,   77,   74,    0,   76,    0,
   72,   72,   72,    0,   72,   71,    0,    0,    0,   51,
   71,    0,   48,   71,   49,    0,   71,    0,    0,    0,
   67,    0,    0,   69,    0,    0,   77,   74,    0,   76,
   71,   71,   71,   52,   71,   72,    0,   79,   69,   69,
   69,   69,   79,    0,   78,   79,    0,    0,   79,   78,
    0,    0,   78,    0,    0,   78,    0,   77,    0,   70,
   50,    0,   79,   79,    0,   71,   72,    0,    0,   78,
   78,    0,    0,   75,   70,   70,   70,   70,   75,    0,
    0,   75,   86,   75,   75,    0,  195,   84,   82,    0,
   83,    0,   85,    0,    0,   47,   71,   79,   75,   75,
   85,  158,    0,  196,   78,   81,    0,   80,   85,    0,
    0,   85,    0,    0,    0,    0,   76,   77,   78,   79,
    0,    0,    0,    0,    0,   85,   85,    0,   79,   66,
    0,    0,    0,   75,    0,   78,   87,    0,    0,    0,
    0,    0,    0,    0,   66,   66,   66,   66,    0,   86,
   75,    0,    0,    0,   84,   82,    0,   83,    0,   85,
   85,   67,    0,    0,   75,    0,    0,    0,   74,   74,
   76,    0,   81,    0,   80,    0,   67,   67,   67,   67,
    0,    0,    0,    0,    0,   76,   76,   76,   76,    0,
    0,    0,    0,    0,    0,    0,   86,   75,   77,    0,
  197,   84,   82,   87,   83,  102,   85,   72,    0,    0,
    0,    0,    0,   77,   77,   77,   77,  198,    0,   81,
    0,   80,   72,   72,   72,   72,   42,   43,   44,   45,
    0,    0,    0,    0,   86,   75,   74,   71,  103,   84,
   82,    0,   83,    0,   85,   46,    0,    0,    0,  157,
   87,    0,   71,   71,   71,   71,   73,   81,    0,   80,
    0,   73,    0,    0,   73,    0,    0,   73,  157,   79,
    0,    0,    0,    0,    0,    0,   78,    0,    0,    0,
    0,   73,   73,   74,   79,   79,  178,  179,   87,   86,
   75,   78,   78,    0,   84,   82,  188,   83,    0,   85,
    0,    0,    0,    0,    0,   75,    0,  199,  200,    0,
  202,    0,   81,    0,   80,    0,   73,    0,  207,  208,
    0,   74,    0,    0,    0,   76,   77,   78,   79,   86,
   75,    0,   85,  173,   84,   82,    0,   83,    0,   85,
    0,    0,    0,   87,    0,  145,    0,   73,    0,    0,
    0,    0,   81,    0,   80,    0,   86,   75,    0,    0,
  174,   84,   82,    0,   83,    0,   85,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   74,    0,    0,   81,
    0,   80,    0,   87,    0,    0,    0,    0,    0,    0,
    0,    0,   76,   77,   78,   79,   86,   75,    0,    0,
    0,   84,   82,    0,   83,    0,   85,    0,    0,    0,
   87,    0,    0,    0,    0,    0,   74,  189,    0,   81,
    0,   80,    0,    0,    0,    0,    0,    0,   86,   75,
    0,    0,    0,   84,   82,    0,   83,    0,   85,   76,
   77,   78,   79,   74,    0,    0,    0,    0,    0,  190,
   87,   81,    0,   80,    0,    0,    0,    0,    0,    0,
    0,    0,   86,   75,    0,    0,  194,   84,   82,    0,
   83,    0,   85,    0,    0,    0,    0,   76,   77,   78,
   79,    0,   87,   74,    0,   81,    0,   80,   73,   86,
   75,    0,    0,  205,   84,   82,    0,   83,    0,   85,
   86,   75,    0,    0,  206,   84,   82,    0,   83,    0,
   85,    0,   81,    0,   80,   74,   87,    0,    0,    0,
    0,    0,    0,   81,    0,   80,    0,    0,    0,    0,
    0,    0,   76,   77,   78,   79,   86,   75,    0,    0,
    0,   84,   82,   87,   83,    0,   85,    0,    0,   74,
    0,    0,    0,    0,   87,    0,    0,   83,   83,   81,
    0,   80,   83,   83,    0,   83,    0,   83,    0,    0,
    0,    0,   76,   77,   78,   79,   74,    0,    0,    0,
   83,    0,   83,   86,   75,    0,    0,   74,   84,   82,
   87,   83,    0,   85,    0,    0,    0,    0,    0,   76,
   77,   78,   79,    0,   86,    0,   81,    0,   80,   84,
   82,   83,   83,    0,   85,    0,    0,    0,    0,    0,
    0,    0,    0,   74,    0,   86,    0,   81,    0,   80,
   84,   82,    0,   83,    0,   85,    0,   87,    0,   76,
   77,   78,   79,    0,   83,    0,    0,    0,   81,    0,
   80,    0,    0,    0,    0,    0,    0,    0,   87,    0,
    0,    0,    0,    0,   51,    0,    0,   48,    0,   49,
    0,   76,   77,   78,   79,    0,    0,    0,    0,   87,
    0,    0,    0,    0,    0,    0,   51,    0,   52,   48,
    0,   49,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   76,   77,   78,   79,    0,
   52,    0,    0,    0,    0,  129,    0,    0,    0,    0,
    0,    0,    0,    0,   51,    0,    0,   48,    0,   49,
    0,    0,   76,   77,   78,   79,    0,  129,    0,    0,
    0,    0,    0,   76,   77,   78,   79,   92,   52,  130,
   47,    0,    0,   51,    0,    0,   48,    0,   49,    0,
   31,    0,    0,   31,    0,   31,    0,    0,    0,   92,
    0,  153,   47,    0,    0,   50,    0,   52,    0,   76,
   77,   78,   79,    0,   31,    0,    0,    0,    0,   33,
    0,    0,   33,    0,   33,    0,    0,    0,    0,    0,
   83,   83,   83,   83,   50,    0,    0,   92,    0,  156,
   47,   31,    0,   33,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   76,   77,   78,   79,
    0,    0,    0,    0,    0,    0,   92,    0,  171,   47,
   33,    0,    0,   31,    0,   31,   31,   76,   77,   78,
   79,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   78,   79,   33,    0,   33,   33,    0,    0,    0,    0,
    0,   42,   43,   44,   45,  121,  122,    0,    0,    0,
    0,    0,    1,    2,    0,    4,  123,  124,  125,  126,
   46,  127,  128,   42,   43,   44,   45,  121,  122,    0,
    0,    0,    0,    0,    1,    2,    0,    4,  123,  124,
  125,  126,   46,  127,  128,    0,    0,    0,    0,    0,
    0,    0,   51,    0,    0,   48,    0,   49,    0,    0,
    0,   42,   43,   44,   45,  121,  122,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   52,    0,  125,  126,
   46,  127,  128,    0,    0,    0,    0,    0,    0,    0,
   42,   43,   44,   45,  121,  122,    0,   31,   31,   31,
   31,   31,   31,  129,    0,    0,    0,  125,  126,   46,
  127,  128,    0,    0,   31,   31,   31,   31,   31,    0,
    0,    0,    0,    0,    0,    0,   33,   33,   33,   33,
   33,   33,    0,    0,    0,    0,    0,    0,   47,    0,
    0,    0,    0,   33,   33,   33,   33,   33,    0,    0,
   53,    0,    0,    0,    0,    0,    0,   63,    0,    0,
   66,    0,    0,    0,    0,    0,    0,   69,   70,   71,
   72,   73,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  101,    0,
    0,    0,    0,    0,  104,  105,  106,  107,  108,  109,
  110,  111,  112,  113,  114,  115,  116,  117,  118,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   72,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  163,    0,    0,  165,  166,   42,
   43,   44,   45,    0,    0,    0,    0,    0,    0,    0,
    1,    2,    0,    4,    0,    0,    0,    0,   46,  175,
  175,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  185,  186,    0,    0,    0,    0,    0,  191,    0,  192,
  193,    0,    0,    0,    0,    0,  201,    0,  203,
};
static const YYINT yycheck[] = {                         33,
    0,   61,   91,   37,   38,  259,    0,   41,   42,   43,
   44,   45,    0,   47,   61,   92,   40,   91,    0,   43,
  119,   45,  263,  264,   58,   59,   60,   61,   62,   63,
   40,   40,   40,   61,   59,   63,  257,  258,   37,  260,
   64,   91,  141,   42,   43,   43,   45,   45,   47,  169,
  170,   61,   61,   61,  259,  276,   40,   91,  135,   93,
   33,  259,   91,  123,   37,   38,  259,   91,   41,   42,
   43,   44,   45,   37,   47,    0,  123,  259,   42,  259,
    5,    6,    7,   47,   40,   58,   59,   60,   13,   62,
  124,   91,   91,   40,   44,   41,   33,   91,   59,  123,
   37,   38,  126,   91,   41,   42,   43,   44,   45,   91,
   47,  259,   93,   41,   40,   41,   44,   43,   91,   45,
   93,   58,   59,   60,   40,   62,   58,   91,  260,   61,
   91,   63,   33,   41,   95,   96,   37,   38,   64,   41,
   41,   42,   43,   44,   45,   41,   47,  123,   44,   41,
  123,  124,   44,   41,   91,   41,   93,   58,   59,   60,
   41,   62,   91,   40,   33,   91,   40,   92,   37,   38,
   40,  259,   41,   42,   43,   44,   45,  259,   47,  268,
  269,  270,  271,  272,  273,  146,  259,  124,   40,   58,
   59,   60,   93,   62,  268,  269,  270,  271,  123,  124,
  126,  162,   61,   33,  129,   61,   61,   37,   38,   40,
  135,   41,   42,   43,   44,   45,    0,   47,  268,  269,
  270,  271,   58,  124,   93,   61,   59,   63,   58,   59,
   60,  265,   62,  257,  258,  259,  260,  261,  262,  268,
  269,    0,  271,   41,   59,   59,  280,  281,  282,  283,
  274,  275,  276,  277,  278,  124,   41,   31,   59,   59,
   59,   13,   36,   93,   38,   39,   60,   41,  268,  269,
  270,  271,  272,  273,  268,  269,  270,  271,  272,  273,
  268,  269,  270,  271,  272,  273,  268,  269,  270,  271,
  272,  273,  265,  199,  124,  135,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  280,  281,  282,
  283,   33,   -1,   -1,   -1,   37,   38,   -1,   -1,   41,
   42,   43,   44,   45,   -1,   47,   -1,   -1,  265,   -1,
   -1,  257,  258,  259,  260,   -1,   58,   59,   60,   -1,
   62,   -1,   -1,  280,  281,  282,  283,   33,   -1,   -1,
  276,   37,   38,   -1,   -1,   41,   42,   43,   44,   45,
   -1,   47,   -1,   -1,  265,   -1,   -1,   -1,   -1,   -1,
   -1,   93,   58,   59,   60,   -1,   62,   -1,   -1,  280,
  281,  282,  283,   -1,   -1,   -1,   -1,   -1,   -1,   33,
   -1,   -1,   -1,   37,   38,   -1,  265,   -1,   42,   43,
   -1,   45,  124,   47,   -1,   -1,   -1,   93,   -1,   -1,
   -1,  280,  281,  282,  283,   59,   60,   33,   62,   -1,
   -1,   -1,   38,   -1,   -1,   41,   -1,   43,   44,   45,
   -1,   -1,   -1,   -1,   -1,  265,   -1,   -1,  124,   -1,
   -1,   -1,   58,   59,   60,   -1,   62,   91,   -1,   33,
  280,  281,  282,  283,   38,   -1,   33,   41,   33,   43,
   44,   45,   -1,   38,   41,   -1,   41,   44,   -1,   44,
   -1,   -1,   -1,   -1,   58,   59,   60,   93,   62,   -1,
  124,   58,   59,   58,   59,   60,   33,   62,   -1,   -1,
   -1,   38,   -1,   -1,   41,   33,   -1,   44,   -1,   -1,
   38,   -1,   -1,   41,   -1,   -1,   44,   -1,  124,   93,
   -1,   58,   59,   60,   -1,   62,   93,   -1,   93,   -1,
   58,   59,   60,   -1,   62,   33,   -1,   -1,   -1,   40,
   38,   -1,   43,   41,   45,   -1,   44,   -1,   -1,   -1,
  124,   -1,   -1,  265,   -1,   -1,   93,  124,   -1,  124,
   58,   59,   60,   64,   62,   93,   -1,   33,  280,  281,
  282,  283,   38,   -1,   33,   41,   -1,   -1,   44,   38,
   -1,   -1,   41,   -1,   -1,   44,   -1,  124,   -1,  265,
   91,   -1,   58,   59,   -1,   93,  124,   -1,   -1,   58,
   59,   -1,   -1,   33,  280,  281,  282,  283,   38,   -1,
   -1,   41,   37,   38,   44,   -1,   41,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,  126,  124,   93,   58,   59,
   33,  265,   -1,   58,   93,   60,   -1,   62,   41,   -1,
   -1,   44,   -1,   -1,   -1,   -1,  280,  281,  282,  283,
   -1,   -1,   -1,   -1,   -1,   58,   59,   -1,  124,  265,
   -1,   -1,   -1,   93,   -1,  124,   91,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  280,  281,  282,  283,   -1,   37,
   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
   93,  265,   -1,   -1,  124,   -1,   -1,   -1,  265,  124,
  265,   -1,   60,   -1,   62,   -1,  280,  281,  282,  283,
   -1,   -1,   -1,   -1,   -1,  280,  281,  282,  283,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,  265,   -1,
   41,   42,   43,   91,   45,   93,   47,  265,   -1,   -1,
   -1,   -1,   -1,  280,  281,  282,  283,   58,   -1,   60,
   -1,   62,  280,  281,  282,  283,  257,  258,  259,  260,
   -1,   -1,   -1,   -1,   37,   38,  124,  265,   41,   42,
   43,   -1,   45,   -1,   47,  276,   -1,   -1,   -1,  136,
   91,   -1,  280,  281,  282,  283,   33,   60,   -1,   62,
   -1,   38,   -1,   -1,   41,   -1,   -1,   44,  155,  265,
   -1,   -1,   -1,   -1,   -1,   -1,  265,   -1,   -1,   -1,
   -1,   58,   59,  124,  280,  281,  173,  174,   91,   37,
   38,  280,  281,   -1,   42,   43,  183,   45,   -1,   47,
   -1,   -1,   -1,   -1,   -1,  265,   -1,  194,  195,   -1,
  197,   -1,   60,   -1,   62,   -1,   93,   -1,  205,  206,
   -1,  124,   -1,   -1,   -1,  280,  281,  282,  283,   37,
   38,   -1,  265,   41,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,   -1,   91,   -1,   93,   -1,  124,   -1,   -1,
   -1,   -1,   60,   -1,   62,   -1,   37,   38,   -1,   -1,
   41,   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,   60,
   -1,   62,   -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  280,  281,  282,  283,   37,   38,   -1,   -1,
   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,
   91,   -1,   -1,   -1,   -1,   -1,  124,   58,   -1,   60,
   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,
   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,  280,
  281,  282,  283,  124,   -1,   -1,   -1,   -1,   -1,   58,
   91,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   37,   38,   -1,   -1,   41,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   -1,   -1,  280,  281,  282,
  283,   -1,   91,  124,   -1,   60,   -1,   62,  265,   37,
   38,   -1,   -1,   41,   42,   43,   -1,   45,   -1,   47,
   37,   38,   -1,   -1,   41,   42,   43,   -1,   45,   -1,
   47,   -1,   60,   -1,   62,  124,   91,   -1,   -1,   -1,
   -1,   -1,   -1,   60,   -1,   62,   -1,   -1,   -1,   -1,
   -1,   -1,  280,  281,  282,  283,   37,   38,   -1,   -1,
   -1,   42,   43,   91,   45,   -1,   47,   -1,   -1,  124,
   -1,   -1,   -1,   -1,   91,   -1,   -1,   37,   38,   60,
   -1,   62,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
   -1,   -1,  280,  281,  282,  283,  124,   -1,   -1,   -1,
   60,   -1,   62,   37,   38,   -1,   -1,  124,   42,   43,
   91,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,  280,
  281,  282,  283,   -1,   37,   -1,   60,   -1,   62,   42,
   43,   91,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  124,   -1,   37,   -1,   60,   -1,   62,
   42,   43,   -1,   45,   -1,   47,   -1,   91,   -1,  280,
  281,  282,  283,   -1,  124,   -1,   -1,   -1,   60,   -1,
   62,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   91,   -1,
   -1,   -1,   -1,   -1,   40,   -1,   -1,   43,   -1,   45,
   -1,  280,  281,  282,  283,   -1,   -1,   -1,   -1,   91,
   -1,   -1,   -1,   -1,   -1,   -1,   40,   -1,   64,   43,
   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  280,  281,  282,  283,   -1,
   64,   -1,   -1,   -1,   -1,   91,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   40,   -1,   -1,   43,   -1,   45,
   -1,   -1,  280,  281,  282,  283,   -1,   91,   -1,   -1,
   -1,   -1,   -1,  280,  281,  282,  283,  123,   64,  125,
  126,   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,
   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,  123,
   -1,  125,  126,   -1,   -1,   91,   -1,   64,   -1,  280,
  281,  282,  283,   -1,   64,   -1,   -1,   -1,   -1,   40,
   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,
  280,  281,  282,  283,   91,   -1,   -1,  123,   -1,  125,
  126,   91,   -1,   64,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  280,  281,  282,  283,
   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,  125,  126,
   91,   -1,   -1,  123,   -1,  125,  126,  280,  281,  282,
  283,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  282,  283,  123,   -1,  125,  126,   -1,   -1,   -1,   -1,
   -1,  257,  258,  259,  260,  261,  262,   -1,   -1,   -1,
   -1,   -1,  268,  269,   -1,  271,  272,  273,  274,  275,
  276,  277,  278,  257,  258,  259,  260,  261,  262,   -1,
   -1,   -1,   -1,   -1,  268,  269,   -1,  271,  272,  273,
  274,  275,  276,  277,  278,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,
   -1,  257,  258,  259,  260,  261,  262,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   64,   -1,  274,  275,
  276,  277,  278,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  257,  258,  259,  260,  261,  262,   -1,  257,  258,  259,
  260,  261,  262,   91,   -1,   -1,   -1,  274,  275,  276,
  277,  278,   -1,   -1,  274,  275,  276,  277,  278,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
  261,  262,   -1,   -1,   -1,   -1,   -1,   -1,  126,   -1,
   -1,   -1,   -1,  274,  275,  276,  277,  278,   -1,   -1,
   30,   -1,   -1,   -1,   -1,   -1,   -1,   37,   -1,   -1,
   40,   -1,   -1,   -1,   -1,   -1,   -1,   47,   48,   49,
   50,   51,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   68,   -1,
   -1,   -1,   -1,   -1,   74,   75,   76,   77,   78,   79,
   80,   81,   82,   83,   84,   85,   86,   87,   88,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  129,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  144,   -1,   -1,  147,  148,  257,
  258,  259,  260,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  268,  269,   -1,  271,   -1,   -1,   -1,   -1,  276,  169,
  170,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  180,  181,   -1,   -1,   -1,   -1,   -1,  187,   -1,  189,
  190,   -1,   -1,   -1,   -1,   -1,  196,   -1,  198,
};
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 284
#define YYUNDFTOKEN 309
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,
0,0,0,0,0,"':'","';'","'<'","'='","'>'","'?'","'@'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tINTEGER","tREAL",
"tIDENTIFIER","tSTRING","tWHILE","tIF","tELSIF","tELSE","tPRINTLN","tBEGIN",
"tEND","tINT","tREALTEXT","tPROCEDURE","tSTR","tPUBLIC","tUSE","tSWEEP","tNEXT",
"tNULL","tSTOP","tRETURN","tIFX","tEQ","tNE","tGE","tLE","tUNARY",0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file : listdecl",
"file :",
"listdecl : decl",
"listdecl : listdecl decl",
"decl : vblockdecl",
"decl : fdecl",
"listvblockdecl : vblockdecl",
"listvblockdecl : listvblockdecl vblockdecl",
"vblockdecl : vdecl ';'",
"vdecl : tPUBLIC type tIDENTIFIER",
"vdecl : type tIDENTIFIER",
"vdecl : tUSE type tIDENTIFIER",
"vdecl : tPUBLIC type tIDENTIFIER '=' expr",
"vdecl : type tIDENTIFIER '=' expr",
"vdecl : tUSE type tIDENTIFIER '=' expr",
"type : tINT",
"type : tSTR",
"type : tREALTEXT",
"type : '[' type ']'",
"listinstr : instr",
"listinstr : listinstr instr",
"instr : expr ';'",
"instr : expr '!'",
"instr : expr tPRINTLN",
"instr : tNEXT",
"instr : tSTOP",
"instr : tRETURN",
"instr : condinstr",
"instr : iter",
"instr : block",
"condinstr : tIF '(' expr ')' instr",
"condinstr : tIF '(' expr ')' instr elsif",
"elsif : tELSIF '(' expr ')' instr",
"elsif : tELSIF '(' expr ')' instr elsif",
"elsif : tELSE instr",
"iter : tWHILE '(' expr ')' instr",
"iter : tSWEEP '+' '(' lval ':' expr ':' expr ')' instr",
"iter : tSWEEP '+' '(' lval ':' expr ':' expr ':' expr ')' instr",
"iter : tSWEEP '-' '(' lval ':' expr ':' expr ')' instr",
"iter : tSWEEP '-' '(' lval ':' expr ':' expr ':' expr ')' instr",
"block : '{' listvblockdecl listinstr '}'",
"block : '{' listvblockdecl '}'",
"block : '{' listinstr '}'",
"block : '{' '}'",
"fdecl : type tIDENTIFIER '(' fargs ')'",
"fdecl : tPUBLIC type tIDENTIFIER '(' fargs ')'",
"fdecl : tUSE type tIDENTIFIER '(' fargs ')'",
"fdecl : tPROCEDURE tIDENTIFIER '(' fargs ')'",
"fdecl : tPUBLIC tPROCEDURE tIDENTIFIER '(' fargs ')'",
"fdecl : tUSE tPROCEDURE tIDENTIFIER '(' fargs ')'",
"fdecl : type tIDENTIFIER '(' fargs ')' block",
"fdecl : tPUBLIC type tIDENTIFIER '(' fargs ')' block",
"fdecl : tPROCEDURE tIDENTIFIER '(' fargs ')' block",
"fdecl : tPUBLIC tPROCEDURE tIDENTIFIER '(' fargs ')' block",
"fdecl : type tIDENTIFIER '(' fargs ')' '=' literal block",
"fdecl : tPUBLIC type tIDENTIFIER '(' fargs ')' '=' literal block",
"literal : tINTEGER",
"literal : lstring",
"literal : tREAL",
"literal : tNULL",
"lstring : tSTRING",
"lstring : lstring tSTRING",
"expr : literal",
"expr : '-' expr",
"expr : '+' expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr '&' expr",
"expr : expr '|' expr",
"expr : '~' expr",
"expr : expr tGE expr",
"expr : expr tLE expr",
"expr : expr tNE expr",
"expr : expr tEQ expr",
"expr : '@'",
"expr : '(' expr ')'",
"expr : '[' expr ']'",
"expr : lval",
"expr : lval '?'",
"expr : lval '=' expr",
"expr : funcinvoc",
"funcinvoc : tIDENTIFIER '(' fargsinvo ')'",
"funcinvoc : tIDENTIFIER '(' ')'",
"fargsinvo : expr",
"fargsinvo : fargsinvo ',' expr",
"lval : tIDENTIFIER",
"lval : expr '[' expr ']'",
"fargs : args",
"fargs :",
"args : arg",
"args : args ',' arg",
"arg : type tIDENTIFIER",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 63 "xpl_parser.y"
	{ compiler->ast(yystack.l_mark[0].sequence);}
break;
case 2:
#line 64 "xpl_parser.y"
	{ compiler->ast(new cdk::nil_node(LINE));}
break;
case 3:
#line 67 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 4:
#line 68 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 5:
#line 71 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 6:
#line 72 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 7:
#line 75 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 8:
#line 76 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 9:
#line 79 "xpl_parser.y"
	{yyval.node = yystack.l_mark[-1].node;}
break;
case 10:
#line 82 "xpl_parser.y"
	{ yyval.node = new xpl::variable_declaration_node(LINE, true, false, yystack.l_mark[0].s, yystack.l_mark[-1].type, nullptr); }
break;
case 11:
#line 83 "xpl_parser.y"
	{ yyval.node = new xpl::variable_declaration_node(LINE, false, false, yystack.l_mark[0].s, yystack.l_mark[-1].type, nullptr); }
break;
case 12:
#line 84 "xpl_parser.y"
	{ yyval.node = new xpl::variable_declaration_node(LINE, false, true, yystack.l_mark[0].s, yystack.l_mark[-1].type, nullptr); }
break;
case 13:
#line 85 "xpl_parser.y"
	{ yyval.node = new xpl::variable_declaration_node(LINE, true, false, yystack.l_mark[-2].s, yystack.l_mark[-3].type, yystack.l_mark[0].expression); }
break;
case 14:
#line 86 "xpl_parser.y"
	{ yyval.node = new xpl::variable_declaration_node(LINE, false, false, yystack.l_mark[-2].s, yystack.l_mark[-3].type, yystack.l_mark[0].expression); }
break;
case 15:
#line 87 "xpl_parser.y"
	{ yyval.node = new xpl::variable_declaration_node(LINE, false, true, yystack.l_mark[-2].s, yystack.l_mark[-3].type, yystack.l_mark[0].expression); }
break;
case 16:
#line 89 "xpl_parser.y"
	{yyval.type = new basic_type(4, basic_type::TYPE_INT);}
break;
case 17:
#line 90 "xpl_parser.y"
	{yyval.type = new basic_type(4, basic_type::TYPE_STRING);}
break;
case 18:
#line 91 "xpl_parser.y"
	{yyval.type = new basic_type(8, basic_type::TYPE_DOUBLE);}
break;
case 19:
#line 92 "xpl_parser.y"
	{yyval.type = new basic_type(8, basic_type::TYPE_POINTER);}
break;
case 20:
#line 95 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 21:
#line 96 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 22:
#line 99 "xpl_parser.y"
	{ yyval.node = new xpl::evaluation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 23:
#line 100 "xpl_parser.y"
	{ yyval.node = new xpl::print_node(LINE, false, yystack.l_mark[-1].expression); }
break;
case 24:
#line 101 "xpl_parser.y"
	{ yyval.node = new xpl::print_node(LINE, true, yystack.l_mark[-1].expression); }
break;
case 25:
#line 102 "xpl_parser.y"
	{ yyval.node = new xpl::next_node(LINE); }
break;
case 26:
#line 103 "xpl_parser.y"
	{ yyval.node = new xpl::stop_node(LINE); }
break;
case 27:
#line 104 "xpl_parser.y"
	{ yyval.node = new xpl::return_node(LINE); }
break;
case 28:
#line 105 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 29:
#line 106 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 30:
#line 107 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].b; }
break;
case 31:
#line 110 "xpl_parser.y"
	{ yyval.node = new xpl::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 32:
#line 111 "xpl_parser.y"
	{ yyval.node = new xpl::if_else_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[-1].node, yystack.l_mark[0].node); }
break;
case 33:
#line 114 "xpl_parser.y"
	{ yyval.node = new xpl::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 34:
#line 115 "xpl_parser.y"
	{ yyval.node = new xpl::if_else_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[-1].node, yystack.l_mark[0].node); }
break;
case 35:
#line 116 "xpl_parser.y"
	{ yyval.node = yystack.l_mark[0].node;}
break;
case 36:
#line 118 "xpl_parser.y"
	{ yyval.node = new xpl::while_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 37:
#line 119 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_plus_node(LINE, yystack.l_mark[-6].lvalue, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, nullptr, yystack.l_mark[0].node);}
break;
case 38:
#line 120 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_plus_node(LINE, yystack.l_mark[-8].lvalue, yystack.l_mark[-6].expression, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].node);}
break;
case 39:
#line 121 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_minus_node(LINE, yystack.l_mark[-6].lvalue, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, nullptr, yystack.l_mark[0].node);}
break;
case 40:
#line 122 "xpl_parser.y"
	{ yyval.node = new xpl::sweep_minus_node(LINE, yystack.l_mark[-8].lvalue, yystack.l_mark[-6].expression, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].node);}
break;
case 41:
#line 124 "xpl_parser.y"
	{ yyval.b = new xpl::block_node(LINE, yystack.l_mark[-2].sequence, yystack.l_mark[-1].sequence); }
break;
case 42:
#line 125 "xpl_parser.y"
	{ yyval.b = new xpl::block_node(LINE, yystack.l_mark[-1].sequence, nullptr); }
break;
case 43:
#line 126 "xpl_parser.y"
	{ yyval.b = new xpl::block_node(LINE, nullptr, yystack.l_mark[-1].sequence); }
break;
case 44:
#line 127 "xpl_parser.y"
	{ yyval.b = new xpl::block_node(LINE, nullptr, nullptr); }
break;
case 45:
#line 130 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE, false, false, yystack.l_mark[-3].s, yystack.l_mark[-4].type, yystack.l_mark[-1].sequence, nullptr); }
break;
case 46:
#line 131 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE, true, false, yystack.l_mark[-3].s, yystack.l_mark[-4].type, yystack.l_mark[-1].sequence, nullptr); }
break;
case 47:
#line 132 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE, false, true, yystack.l_mark[-3].s, yystack.l_mark[-4].type, yystack.l_mark[-1].sequence, nullptr); }
break;
case 48:
#line 133 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE, false, false, yystack.l_mark[-3].s, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-1].sequence, nullptr); }
break;
case 49:
#line 134 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE, true, false, yystack.l_mark[-3].s, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-1].sequence, nullptr); }
break;
case 50:
#line 135 "xpl_parser.y"
	{ yyval.node = new xpl::function_declaration_node(LINE, false, true, yystack.l_mark[-3].s, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-1].sequence, nullptr); }
break;
case 51:
#line 137 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE, false, yystack.l_mark[-5].type, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, nullptr, yystack.l_mark[0].b); }
break;
case 52:
#line 138 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE, true, yystack.l_mark[-5].type, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, nullptr, yystack.l_mark[0].b); }
break;
case 53:
#line 139 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE, false, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, nullptr, yystack.l_mark[0].b); }
break;
case 54:
#line 140 "xpl_parser.y"
	{yyval.node = new xpl::function_definition_node(LINE, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, nullptr, yystack.l_mark[0].b);}
break;
case 55:
#line 141 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE, false, yystack.l_mark[-7].type, yystack.l_mark[-6].s, yystack.l_mark[-4].sequence, yystack.l_mark[-1].expression, yystack.l_mark[0].b); }
break;
case 56:
#line 142 "xpl_parser.y"
	{ yyval.node = new xpl::function_definition_node(LINE, true, yystack.l_mark[-7].type, yystack.l_mark[-6].s, yystack.l_mark[-4].sequence, yystack.l_mark[-1].expression, yystack.l_mark[0].b); }
break;
case 57:
#line 145 "xpl_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 58:
#line 146 "xpl_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s); }
break;
case 59:
#line 147 "xpl_parser.y"
	{ yyval.expression = new cdk::double_node(LINE, yystack.l_mark[0].d); }
break;
case 60:
#line 148 "xpl_parser.y"
	{ yyval.expression = new xpl::null_node(LINE);}
break;
case 61:
#line 150 "xpl_parser.y"
	{ yyval.s = yystack.l_mark[0].s; }
break;
case 62:
#line 151 "xpl_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[-1].s + *yystack.l_mark[0].s); }
break;
case 63:
#line 154 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression;}
break;
case 64:
#line 155 "xpl_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 65:
#line 156 "xpl_parser.y"
	{ yyval.expression = new xpl::identity_node(LINE, yystack.l_mark[0].expression); }
break;
case 66:
#line 157 "xpl_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 67:
#line 158 "xpl_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 68:
#line 159 "xpl_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 69:
#line 160 "xpl_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 70:
#line 161 "xpl_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 71:
#line 162 "xpl_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 72:
#line 163 "xpl_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 73:
#line 164 "xpl_parser.y"
	{ yyval.expression = new cdk::and_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 74:
#line 165 "xpl_parser.y"
	{ yyval.expression = new cdk::or_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 75:
#line 166 "xpl_parser.y"
	{ yyval.expression = new cdk::not_node(LINE, yystack.l_mark[0].expression); }
break;
case 76:
#line 167 "xpl_parser.y"
	{ yyval.expression = new cdk::ge_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 77:
#line 168 "xpl_parser.y"
	{ yyval.expression = new cdk::le_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 78:
#line 169 "xpl_parser.y"
	{ yyval.expression = new cdk::ne_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 79:
#line 170 "xpl_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 80:
#line 171 "xpl_parser.y"
	{ yyval.expression = new xpl::read_node(LINE);}
break;
case 81:
#line 172 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 82:
#line 173 "xpl_parser.y"
	{ yyval.expression = new xpl::malloc_node(LINE, yystack.l_mark[-1].expression); }
break;
case 83:
#line 174 "xpl_parser.y"
	{ yyval.expression = new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 84:
#line 175 "xpl_parser.y"
	{ yyval.expression = new xpl::address_node(LINE, yystack.l_mark[-1].lvalue); }
break;
case 85:
#line 176 "xpl_parser.y"
	{ yyval.expression = new cdk::assignment_node(LINE, yystack.l_mark[-2].lvalue, yystack.l_mark[0].expression); }
break;
case 86:
#line 177 "xpl_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 87:
#line 180 "xpl_parser.y"
	{ yyval.expression = new xpl::function_invocation_node(LINE, yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); }
break;
case 88:
#line 181 "xpl_parser.y"
	{ yyval.expression = new xpl::function_invocation_node(LINE, yystack.l_mark[-2].s, new cdk::sequence_node(LINE)); }
break;
case 89:
#line 183 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression); }
break;
case 90:
#line 184 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression, yystack.l_mark[-2].sequence); }
break;
case 91:
#line 187 "xpl_parser.y"
	{ yyval.lvalue = new cdk::identifier_node(LINE, yystack.l_mark[0].s); }
break;
case 92:
#line 188 "xpl_parser.y"
	{ yyval.lvalue = new xpl::index_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[-1].expression);}
break;
case 93:
#line 191 "xpl_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence;}
break;
case 94:
#line 192 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE);}
break;
case 95:
#line 194 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 96:
#line 195 "xpl_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-2].sequence); }
break;
case 97:
#line 197 "xpl_parser.y"
	{ yyval.node = new xpl::variable_declaration_node(LINE, false, false, yystack.l_mark[0].s, yystack.l_mark[-1].type, nullptr); }
break;
#line 1317 "xpl_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
