%{
// $Id: xpl_parser.y,v 1.19 2017/05/16 00:39:13 ist180996 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                   i;	/* integer value */
  double                d;      /* double value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  xpl::block_node *b;
  basic_type *type;
  
};

%token <i> tINTEGER
%token <d> tREAL
%token <s> tIDENTIFIER tSTRING
%token tWHILE tIF tELSIF tELSE tPRINTLN tBEGIN tEND
%token tINT tREALTEXT tPROCEDURE tSTR tPUBLIC tUSE tSWEEP tNEXT tNULL tSTOP tRETURN

%nonassoc tIFX
%nonassoc tELSE tELSIF

%right '='
%left '|'
%left '&'
%nonassoc '~'
%left tEQ tNE
%left tGE tLE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc tUNARY
%nonassoc '['

%type <node> decl vdecl fdecl vblockdecl instr condinstr iter arg elsif
%type <sequence> listdecl listvblockdecl fargs args listinstr fargsinvo
%type <expression> expr literal funcinvoc
%type <lvalue> lval
%type <type> type
%type <b> block
%type <s> lstring

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

//program	: tBEGIN list tEND { compiler->ast(new xpl::program_node(LINE, $2)); }
	     // ;

file : listdecl         { compiler->ast($1);}
     |                  { compiler->ast(new cdk::nil_node(LINE));}
     ;

listdecl : decl	            { $$ = new cdk::sequence_node(LINE, $1); }
         | listdecl decl    { $$ = new cdk::sequence_node(LINE, $2, $1); }
         ;
     
decl : vblockdecl            { $$ = $1; }
     | fdecl                 { $$ = $1; }
     ;

listvblockdecl : vblockdecl	                { $$ = new cdk::sequence_node(LINE, $1); }
               | listvblockdecl vblockdecl           { $$ = new cdk::sequence_node(LINE, $2, $1); }
               ;

vblockdecl : vdecl ';' {$$ = $1;}
           ;

vdecl : tPUBLIC type tIDENTIFIER            { $$ = new xpl::variable_declaration_node(LINE, true, false, $3, $2, nullptr); }
      | type tIDENTIFIER                    { $$ = new xpl::variable_declaration_node(LINE, false, false, $2, $1, nullptr); }
      | tUSE type tIDENTIFIER               { $$ = new xpl::variable_declaration_node(LINE, false, true, $3, $2, nullptr); }
      | tPUBLIC type tIDENTIFIER '=' expr   { $$ = new xpl::variable_declaration_node(LINE, true, false, $3, $2, $5); }
      | type tIDENTIFIER '=' expr           { $$ = new xpl::variable_declaration_node(LINE, false, false, $2, $1, $4); }
      | tUSE type tIDENTIFIER '=' expr      { $$ = new xpl::variable_declaration_node(LINE, false, true, $3, $2, $5); }
      ;     
type : tINT                         {$$ = new basic_type(4, basic_type::TYPE_INT);}
     | tSTR                         {$$ = new basic_type(4, basic_type::TYPE_STRING);}
     | tREALTEXT                    {$$ = new basic_type(8, basic_type::TYPE_DOUBLE);}
     |'['type']'                    {$$ = new basic_type(8, basic_type::TYPE_POINTER);}
     ;
     
listinstr : instr                   { $$ = new cdk::sequence_node(LINE, $1); }
          | listinstr instr         { $$ = new cdk::sequence_node(LINE, $2, $1); }
          ;

instr : expr ';'                    { $$ = new xpl::evaluation_node(LINE, $1); }
      | expr '!'                    { $$ = new xpl::print_node(LINE, false, $1); }
      | expr tPRINTLN               { $$ = new xpl::print_node(LINE, true, $1); }
      | tNEXT                       { $$ = new xpl::next_node(LINE); }
      | tSTOP                       { $$ = new xpl::stop_node(LINE); }
      | tRETURN                     { $$ = new xpl::return_node(LINE); }
      | condinstr                   { $$ = $1; }
      | iter                        { $$ = $1; }
      | block                       { $$ = $1; }
      ;

condinstr : tIF '(' expr ')' instr %prec tIFX                    { $$ = new xpl::if_node(LINE, $3, $5); }
          | tIF '(' expr ')' instr elsif                         { $$ = new xpl::if_else_node(LINE, $3, $5, $6); }           
          ;
          
elsif: tELSIF '(' expr ')' instr %prec tIFX                      { $$ = new xpl::if_node(LINE, $3, $5); }
     | tELSIF '(' expr ')' instr elsif                           { $$ = new xpl::if_else_node(LINE, $3, $5, $6); }
     | tELSE instr                                               { $$ = $2;}
     ;
iter : tWHILE '(' expr ')' instr      { $$ = new xpl::while_node(LINE, $3, $5); }
     | tSWEEP '+' '(' lval ':' expr ':' expr ')' instr { $$ = new xpl::sweep_plus_node(LINE, $4, $6, $8, nullptr, $10);}
     | tSWEEP '+' '(' lval ':' expr ':' expr ':' expr')' instr { $$ = new xpl::sweep_plus_node(LINE, $4, $6, $8, $10, $12);}
     | tSWEEP '-' '(' lval ':' expr ':' expr ')' instr { $$ = new xpl::sweep_minus_node(LINE, $4, $6, $8, nullptr, $10);}
     | tSWEEP '-' '(' lval ':' expr ':' expr ':' expr')' instr { $$ = new xpl::sweep_minus_node(LINE, $4, $6, $8, $10, $12);}
     ;
block : '{' listvblockdecl listinstr '}'  { $$ = new xpl::block_node(LINE, $2, $3); }
      | '{' listvblockdecl '}'            { $$ = new xpl::block_node(LINE, $2, nullptr); }
      | '{' listinstr '}'                 { $$ = new xpl::block_node(LINE, nullptr, $2); }
      | '{' '}'                           { $$ = new xpl::block_node(LINE, nullptr, nullptr); }
      ;

fdecl : type tIDENTIFIER '(' fargs ')'              { $$ = new xpl::function_declaration_node(LINE, false, false, $2, $1, $4, nullptr); }
      | tPUBLIC type tIDENTIFIER '(' fargs ')'      { $$ = new xpl::function_declaration_node(LINE, true, false, $3, $2, $5, nullptr); }
      | tUSE type tIDENTIFIER '(' fargs ')'         { $$ = new xpl::function_declaration_node(LINE, false, true, $3, $2, $5, nullptr); }
      | tPROCEDURE tIDENTIFIER '(' fargs ')'        { $$ = new xpl::function_declaration_node(LINE, false, false, $2, new basic_type(0, basic_type::TYPE_VOID), $4, nullptr); }
      | tPUBLIC tPROCEDURE tIDENTIFIER '(' fargs ')'{ $$ = new xpl::function_declaration_node(LINE, true, false, $3, new basic_type(0, basic_type::TYPE_VOID), $5, nullptr); }
      | tUSE tPROCEDURE tIDENTIFIER '(' fargs ')'   { $$ = new xpl::function_declaration_node(LINE, false, true, $3, new basic_type(0, basic_type::TYPE_VOID), $5, nullptr); }
      
      | type tIDENTIFIER '(' fargs ')' block                                { $$ = new xpl::function_definition_node(LINE, false, $1, $2, $4, nullptr, $6); }
      | tPUBLIC type tIDENTIFIER '(' fargs ')' block                        { $$ = new xpl::function_definition_node(LINE, true, $2, $3, $5, nullptr, $7); }
      | tPROCEDURE tIDENTIFIER '(' fargs ')' block    { $$ = new xpl::function_definition_node(LINE, false, new basic_type(0, basic_type::TYPE_VOID), $2, $4, nullptr, $6); }
      | tPUBLIC tPROCEDURE tIDENTIFIER '(' fargs ')' block {$$ = new xpl::function_definition_node(LINE, true, new basic_type(0, basic_type::TYPE_VOID), $3, $5, nullptr, $7);}      
      | type tIDENTIFIER '(' fargs ')' '=' literal block                    { $$ = new xpl::function_definition_node(LINE, false, $1, $2, $4, $7, $8); }
      | tPUBLIC type tIDENTIFIER '(' fargs ')' '=' literal block            { $$ = new xpl::function_definition_node(LINE, true, $2, $3, $5, $8, $9); }
      ;
      
literal : tINTEGER                { $$ = new cdk::integer_node(LINE, $1); }
        | lstring                 { $$ = new cdk::string_node(LINE, $1); }
        | tREAL                   { $$ = new cdk::double_node(LINE, $1); }
        | tNULL                   { $$ = new xpl::null_node(LINE);}
        ;
lstring : tSTRING                 { $$ = $1; }
        | lstring tSTRING         { $$ = new std::string(*$1 + *$2); }
        ;

expr : literal                   { $$ = $1;}
     | '-' expr %prec tUNARY     { $$ = new cdk::neg_node(LINE, $2); }
     | '+' expr %prec tUNARY     { $$ = new xpl::identity_node(LINE, $2); }
     | expr '+' expr	         { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	         { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	         { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	         { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	         { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	         { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	         { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr '&' expr             { $$ = new cdk::and_node(LINE, $1, $3); }
     | expr '|' expr             { $$ = new cdk::or_node(LINE, $1, $3); }
     | '~' expr                  { $$ = new cdk::not_node(LINE, $2); }
     | expr tGE expr	         { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr             { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr	         { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr	         { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '@'                       { $$ = new xpl::read_node(LINE);}
     | '(' expr ')'              { $$ = $2; }
     | '[' expr ']'              { $$ = new xpl::malloc_node(LINE, $2); }
     | lval                      { $$ = new cdk::rvalue_node(LINE, $1); }  //FIXME
     | lval '?'                  { $$ = new xpl::address_node(LINE, $1); }
     | lval '=' expr             { $$ = new cdk::assignment_node(LINE, $1, $3); }
     | funcinvoc                 { $$ = $1; }
     ;
     
funcinvoc : tIDENTIFIER '(' fargsinvo ')'   { $$ = new xpl::function_invocation_node(LINE, $1, $3); }
          | tIDENTIFIER '(' ')'             { $$ = new xpl::function_invocation_node(LINE, $1, new cdk::sequence_node(LINE)); }
          ;
fargsinvo : expr                { $$ = new cdk::sequence_node(LINE, $1); }
          | fargsinvo ',' expr  { $$ = new cdk::sequence_node(LINE, $3, $1); }  
          ;

lval : tIDENTIFIER             { $$ = new cdk::identifier_node(LINE, $1); }
     | expr '[' expr ']'       { $$ = new xpl::index_node(LINE, $1, $3);}    
     ;

fargs : args                    { $$ = $1;}
      |                         { $$ = new cdk::sequence_node(LINE);}
      ;
args : arg                     { $$ = new cdk::sequence_node(LINE, $1); }
     | args ',' arg              { $$ = new cdk::sequence_node(LINE, $3, $1); }
     ;
arg : type tIDENTIFIER          { $$ = new xpl::variable_declaration_node(LINE, false, false, $2, $1, nullptr); }
    ;
%%
