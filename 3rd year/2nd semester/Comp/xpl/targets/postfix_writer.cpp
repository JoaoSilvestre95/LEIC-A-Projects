#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "targets/stack_counter.h"
#include "ast/all.h"  // all.h is automatically generated

inline basic_type * createType(basic_type * type) {
  basic_type * new_type = new basic_type(type->size(), type->name());
  if (type->subtype())
    new_type->_subtype = createType(type->subtype());
  return new_type;
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  _pf.INT(node->value()); // push an integer
}


void xpl::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
//     _pf.DOUBLE(node->value()); // push an integer
}

void xpl::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.STR(node->value()); // output string characters

  /* leave the address on the stack */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(mklbl(lbl1)); // the string to be printed
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

void xpl::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->left()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->right()->accept(this, lvl);
//   _pf.ALIGN();
  _pf.LABEL(mklbl(lbl1));
}

void xpl::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;  
  node->left()->accept(this, lvl);
  _pf.JNZ(mklbl(lbl1 = ++_lbl));
  node->right()->accept(this, lvl);
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl1));
}

void xpl::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
  _pf.NOT();
}
//---------------------------------------------------------------------------

void xpl::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.ADD();
}
void xpl::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.SUB();
}
void xpl::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MUL();
}
void xpl::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.DIV();
}
void xpl::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void xpl::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void xpl::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void xpl::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void xpl::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void xpl::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void xpl::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  // simplified generation: all variables are global
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(node->name());
  if(symbol->is_function()){
    _pf.LOCAL(symbol->offset());
  }
  else{
    _pf.ADDR(node->name());
    
  }
}

void xpl::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  _pf.LOAD(); // depends on type size
}

void xpl::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->rvalue()->accept(this, lvl); // determine the new value
  _pf.DUP();
  if (new_symbol() == nullptr) {
    node->lvalue()->accept(this, lvl); // where to store the value
  } else {
    _pf.DATA(); // variables are all global and live in DATA
    _pf.ALIGN(); // make sure we are aligned
    _pf.LABEL(new_symbol()->name()); // name variable location
    _pf.CONST(0); // initialize it to 0 (zero)
    _pf.TEXT(); // return to the TEXT segment
    node->lvalue()->accept(this, lvl);  //DAVID: bah!
  }
  _pf.STORE(); // store the value at address
}

//---------------------------------------------------------------------------

/*void xpl::postfix_writer::do_program_node(xpl::program_node * const node, int lvl) {
  // The ProgramNode (representing the whole program) is the
  // main function node.

  // generate the main function (RTS mandates that its name be "_main")
  _pf.TEXT();
  _pf.ALIGN();
  _pf.GLOBAL("_main", _pf.FUNC());
  _pf.LABEL("_main");
  _pf.ENTER(0);  // XPL doesn't implement local variables

  node->statements()->accept(this, lvl);

  // end the main function
  _pf.INT(0);
  _pf.POP();
  _pf.LEAVE();
  _pf.RET();

  // these are just a few library function imports
  _pf.EXTERN("readi");
  _pf.EXTERN("printi");
  _pf.EXTERN("prints");
  _pf.EXTERN("println");
}
*/
//---------------------------------------------------------------------------

void xpl::postfix_writer::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.TRASH(4); // delete the evaluated value
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.TRASH(4); // delete the evaluated value's address
  } else if (node->argument()->type()->name() == basic_type::TYPE_VOID) {
    _pf.TRASH(0); // delete the evaluated value's address
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

void xpl::postfix_writer::do_print_node(xpl::print_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE){
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value's address
  }else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  
  if(node->newline())
    _pf.CALL("println"); // print a newline
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_read_node(xpl::read_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  
  //typechecker
  //check undifined?? thats all? no store?  
  
  if(node->type()->name() == basic_type::TYPE_INT){
    _pf.CALL("readi");
    _pf.PUSH();
  }else if(node->type()->name() == basic_type::TYPE_DOUBLE){
    _pf.CALL("readd");
    _pf.PUSH();
  }  

}


//---------------------------------------------------------------------------

void xpl::postfix_writer::do_while_node(xpl::while_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  _pf.LABEL(mklbl(lbl1 = ++_lbl));
  _next_labels.push_back(mklbl(lbl1));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl2 = ++_lbl));
  _stop_labels.push_back(mklbl(lbl2));
  node->block()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));
  _next_labels.pop_back();
  _stop_labels.pop_back();
}
//---------------------------------------------------------------------------

void xpl::postfix_writer::do_if_node(xpl::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void xpl::postfix_writer::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

//---------------------------------------------------------------------------
void xpl::postfix_writer::do_sweep_plus_node(xpl::sweep_plus_node * const node, int lvl) {
      //CHECK_TYPES
    
    int lbl_cond = ++_lbl;    
    int lbl_inc = ++_lbl;
    _next_labels.push_back(mklbl(_lbl));
    int lbl_end = ++_lbl;
    _stop_labels.push_back(mklbl(_lbl));
    
    cdk::assignment_node *init = new cdk::assignment_node(node->lineno(), node->lvalue(), node->expression1()); 
    init->accept(this, lvl+1);
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(lbl_cond));
    
    cdk::rvalue_node *rv = new cdk::rvalue_node(node->lineno(), node->lvalue());    
    rv->accept(this, lvl+1);
    
    cdk::le_node *le = new cdk::le_node(node->lineno(), rv, node->expression2());    
    le->accept(this, lvl+1);
    
    _pf.JZ(mklbl(lbl_end));
    
    node->block()->accept(this, lvl+1);
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(lbl_inc));
    
    if(node->expression3()){
        cdk::add_node *inc = new cdk::add_node(node->lineno(), rv, node->expression3());
        inc->accept(this, lvl + 1);
        cdk::assignment_node *next = new cdk::assignment_node(node->lineno(), node->lvalue(), inc);
        next->accept(this, lvl+1);
    }
    else{
        cdk::add_node *inc = new cdk::add_node(node->lineno(), rv, new cdk::integer_node(node->lineno(), 1));
        inc->accept(this, lvl+1);
        cdk::assignment_node *next = new cdk::assignment_node(node->lineno(), node->lvalue(), inc);
        next->accept(this, lvl+1);
    }
    
    _pf.JMP(mklbl(lbl_cond));
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(lbl_end));
    
    _stop_labels.pop_back();
    _next_labels.pop_back();
    
    
    
}
void xpl::postfix_writer::do_sweep_minus_node(xpl::sweep_minus_node * const node, int lvl) {
    //CHECK_TYPES
    
    int lbl_cond = ++_lbl;
    int lbl_dec = ++_lbl;
    _next_labels.push_back(mklbl(_lbl));
    int lbl_end = ++_lbl;
    _stop_labels.push_back(mklbl(_lbl));
    
    cdk::assignment_node *init = new cdk::assignment_node(node->lineno(), node->lvalue(), node->expression1()); 
    init->accept(this, lvl+1);
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(lbl_cond));
    
    cdk::rvalue_node *rv = new cdk::rvalue_node(node->lineno(), node->lvalue());    
    rv->accept(this, lvl+1);
    
    cdk::ge_node *ge = new cdk::ge_node(node->lineno(), rv, node->expression2());    
    ge->accept(this, lvl+1);
    
    _pf.JZ(mklbl(lbl_end));
    
    node->block()->accept(this, lvl+1);
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(lbl_dec));
    
    if(node->expression3()){
        cdk::sub_node *dec = new cdk::sub_node(node->lineno(), rv, node->expression3());
        dec->accept(this, lvl + 1);
        cdk::assignment_node *next = new cdk::assignment_node(node->lineno(), node->lvalue(), dec);
        next->accept(this, lvl+1);
    }
    else{
        cdk::sub_node *dec = new cdk::sub_node(node->lineno(), rv, new cdk::integer_node(node->lineno(), 1));
        dec->accept(this, lvl+1);
        cdk::assignment_node *next = new cdk::assignment_node(node->lineno(), node->lvalue(), dec);
        next->accept(this, lvl+1);
    }
    
    _pf.JMP(mklbl(lbl_cond));
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(lbl_end));
    _stop_labels.pop_back();
    _next_labels.pop_back();
    
}
void xpl::postfix_writer::do_function_declaration_node(xpl::function_declaration_node * const node, int lvl) {
   /*std::string identifier;
    if(*(node->identifier()) == "xpl")
        identifier = "_main";
    else if(*(node->identifier()) == "_main")
        identifier = "xpl";
    else    
        identifier = *(node->identifier());
    
    std::shared_ptr<xpl::symbol> symbol = _symtab.find(identifier);
    if(symbol == nullptr){
        for (size_t i = 0; i < node->sequence()->size(); i++) {
	    xpl::var_dec_node *arg = (pwn::var_dec_node*) node->variaveis()->node(i);
	    args.push_back(arg->type());
	   
        }
        std::shared_ptr<xpl::symbol> symbol = std::make_shared<xpl::symbol>(node->type(), identifier);
        _symtab.insert(identifier, symbol);
    }else{
        //Error
    }*/
    
    
    
    
}
void xpl::postfix_writer::do_function_definition_node(xpl::function_definition_node * const node, int lvl) {
    
  //CHECK_TYPES(_compiler, _symtab, node);

 std::string lbl;
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(*node->identifier());
  
  //Stack size
  xpl::stack_counter stackcounter(_compiler);
  node->accept(&stackcounter, lvl);

  size_t localsize = stackcounter.size();

  size_t retsize = node->type()->size();

  _atual_offset = -retsize;
  
  _args_offset = 8;

  if (symbol) {
      symbol->offset(-node->type()->size());
    // Symbol exists
    if (symbol->is_defined())
      throw std::string("symbol already exists");
    else if (!symbol->is_function())
      throw std::string("symbol is not a function");
    else {
      if (symbol->is_use() && !symbol->is_defined()){
        for (std::vector<std::string>::iterator it = _externs.begin(); it != _externs.end(); ++it){
            if (lbl == *it) {
            _externs.erase(it);
            return;
            }
        }
      }
      for (size_t i = 0; i < node->sequence()->size(); i++) {
        xpl::variable_declaration_node *arg = (xpl::variable_declaration_node*) node->sequence()->node(i);
        symbol->args(arg->type());
      }
      symbol->is_defined(true);
      lbl = symbol->name();
    }
  } else {
    lbl = *node->identifier();
    symbol = std::make_shared<xpl::symbol>
      (createType(node->type()),
       *node->identifier(), true, true, node->qualifier(), false, std::vector<basic_type*>());
    for (size_t i = 0; i < node->sequence()->size(); i++) {
        xpl::variable_declaration_node *arg = (xpl::variable_declaration_node*) node->sequence()->node(i);
        symbol->args(arg->type());
    }
    _symtab.insert(*node->identifier(), symbol);

  }

  _current_func = symbol;
  _symtab.push();

  _pf.TEXT();
  _pf.ALIGN();

  if (node->qualifier()) {

    if (*node->identifier() == "xpl") {
      _pf.GLOBAL("_main", _pf.FUNC());
      _pf.LABEL("_main");
      _pf.ALIGN();
    }
    else if (*node->identifier() == "_main")
      throw std::string("invalid name for function, it's reserved");
    else {
      _pf.GLOBAL(lbl, _pf.FUNC());
    }
  }
  _pf.LABEL(lbl);

  _pf.ENTER(localsize + retsize);

  
  if (node->value()) {

    node->value()->accept(this, lvl);
    //d2i_i2d(node->type(), node->value()->type());!!!!!

    _pf.LOCAL(-retsize);
    if (node->type()->name() == basic_type::TYPE_DOUBLE) {
      _pf.DSTORE();
    } else {
      _pf.STORE();
    }
  }

  if (node->sequence()) {
    node->sequence()->accept(this, lvl);
  }

  node->block()->accept(this, lvl);

  if (node->type()->name() != basic_type::TYPE_VOID) {
    _pf.LOCAL(-retsize);
    if (node->type()->name() == basic_type::TYPE_DOUBLE) {
      _pf.DLOAD();
      _pf.DPOP();
    } else {
      _pf.LOAD();
      _pf.POP();
    }
  }

  _pf.LEAVE();
  _pf.RET();

  _symtab.pop();
  //_is_global_context = true;
  _current_func = NULL;


    
    
/*    
    
    
    
   // generate the main function (RTS mandates that its name be "_main")
  
    _pf.TEXT();
    _pf.ALIGN();
    _pf.GLOBAL("_main", _pf.FUNC());
    _pf.LABEL("_main");
    _pf.ENTER(0);  // XPL doesn't implement local variables

    node->block()->accept(this, lvl);

    // end the main function
    _pf.INT(0);
    _pf.POP();
    _pf.LEAVE();
    _pf.RET();
*/
    // these are just a few library function imports
    _pf.EXTERN("readi");
    _pf.EXTERN("printi");
    _pf.EXTERN("prints");
    _pf.EXTERN("println");
  
    
}
void xpl::postfix_writer::do_function_invocation_node(xpl::function_invocation_node * const node, int lvl) {
  std::string id = *node->identifier();
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);
  if (!symbol) 
      throw std::string ("Couldnt find function");

  xpl::stack_counter sc(_compiler);
  node->accept(&sc, lvl);
  
  size_t trash = sc.size();
/*
  std::vector<basic_type*> args_func = symbol->args();
  std::vector<basic_type*> args_call;
  for (size_t i = 0; i < node->sequence()->size(); i++) {
    xpl::variable_declaration_node *arg = (xpl::variable_declaration_node*) node->sequence()->node(i);
    args_call.push_back(arg->type());
  }

  if (args_func && args_call &&
      args_func->size() == call_args->size()) {

    size_t i = args_func->size() - 1; 
    size_t j = 0; 

    for (; j < args_func->size() && i >= 0 ; j++, i--) {

      xpl::variable_declaration_node *param = dynamic_cast<xpl::variable_declaration_node *> (args_func->node(i));
      cdk::expression_node *arg = dynamic_cast<cdk::expression_node *> (call_args->node(j));

      if (!param || !arg) 
          throw std::string("ERROR @ " + node->name() + ": Cast failed, CANNOT HAPPEN!");
      arg->accept(this, lvl);
    }

  }*/

//   if (symbol->is_imported())
//     registerExtern(symbol->name());

  _pf.CALL(symbol->name());

  _pf.TRASH(trash);

  if (node->type()->name() == basic_type::TYPE_DOUBLE)
    _pf.DPUSH();
  else
    _pf.PUSH(); 
  
}
void xpl::postfix_writer::do_stop_node(xpl::stop_node * const node, int lvl) {
    if(_stop_labels.empty())
        throw std::string("Not inside Cycle");
    _pf.JMP(_stop_labels.back());
}
void xpl::postfix_writer::do_next_node(xpl::next_node * const node, int lvl) {
    if(_next_labels.empty())
        throw std::string("Not inside Cycle");
    _pf.JMP(_next_labels.back());
}
void xpl::postfix_writer::do_return_node(xpl::return_node * const node, int lvl) {
  if(_current_func == NULL) {
    throw std::string("Error, return outside function");
  }

  if (_current_func->type()->name() != basic_type::TYPE_VOID) {
    _pf.LOCAL(_atual_offset);
    if (_current_func->type()->name() == basic_type::TYPE_DOUBLE) {
      _pf.DLOAD();
      _pf.DPOP();
    } else {
      _pf.LOAD();
      _pf.POP();
    }
  }

  _pf.LEAVE();
  _pf.RET();
}
void xpl::postfix_writer::do_null_node(xpl::null_node * const node, int lvl) {};
void xpl::postfix_writer::do_variable_declaration_node(xpl::variable_declaration_node * const node, int lvl) {
    
    std::shared_ptr<xpl::symbol> s = _symtab.find(*(node->identifier()));
    if(s.get() != NULL){
      std::cerr << "error: redefinition of '" << *node->identifier() << "'" << std::endl;
      exit(-1);
    }
    symbol *pointer = new symbol(node->type(), *node->identifier());
    std::shared_ptr<xpl::symbol> s3(pointer);
    _symtab.insert(*node->identifier(), s3);
    if(node->value() != NULL){
      _pf.DATA();
      _pf.ALIGN();
      _pf.GLOBAL(*node->identifier(), _pf.OBJ());
      _pf.LABEL(*node->identifier());
      if((node->type()->name() == basic_type::TYPE_INT) &&
         (dynamic_cast<cdk::integer_node*>(node->value()) != NULL)){
          _pf.CONST((dynamic_cast<cdk::integer_node*>(node->value()))->value());
      }
      else if((node->type()->name() == basic_type::TYPE_DOUBLE) && (dynamic_cast<cdk::double_node*>(node->value()) != NULL)){
        _pf.DOUBLE((dynamic_cast<cdk::double_node*>(node->value()))->value());
      }else if((node->type()->name() == basic_type::TYPE_STRING) &&
         (dynamic_cast<cdk::string_node*>(node->value()) != NULL)){
           _pf.RODATA();
           _pf.ALIGN(); 
           _pf.LABEL(mklbl(++_lbl)); 
           _pf.STR((dynamic_cast<cdk::string_node*>(node->value()))->value()); 

           _pf.DATA(); 
           _pf.ALIGN();
           _pf.ID(mklbl(_lbl)); 
           _pf.TEXT();


      }else if(node->type()->name() == basic_type::TYPE_POINTER){
        _pf.INT(0);
      }
      node->value()->accept(this, lvl);
    }else{
      _pf.BSS();
      _pf.ALIGN();
      _pf.GLOBAL(*node->identifier(), _pf.OBJ());
      _pf.LABEL(*node->identifier());
      _pf.BYTE(node->type()->size());
    }

    _pf.TEXT();
    _pf.ALIGN();
    return;

};
void xpl::postfix_writer::do_block_node(xpl::block_node * const node, int lvl) {
    
  _symtab.push();
  
  if(node->declaration() != NULL){
    node->declaration()->accept(this, lvl+1);
  }

  if(node->instruction() != NULL){
    node->instruction()->accept(this, lvl+1);
  }
  
  _symtab.pop();
};
void xpl::postfix_writer::do_identity_node(xpl::identity_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    node->argument()->accept(this, lvl);
};
void xpl::postfix_writer::do_address_node(xpl::address_node * const node, int lvl) {};
void xpl::postfix_writer::do_malloc_node(xpl::malloc_node * const node, int lvl) {};
void xpl::postfix_writer::do_index_node(xpl::index_node * const node, int lvl) {};
//---------------------------------------------------------------------------
