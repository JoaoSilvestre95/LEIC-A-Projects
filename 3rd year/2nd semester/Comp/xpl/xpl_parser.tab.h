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
extern YYSTYPE yylval;
