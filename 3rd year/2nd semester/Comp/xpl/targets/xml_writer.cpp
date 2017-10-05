#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated
//---------------------------------------------------------------------------
inline std::string typeToString(basic_type *type){
    switch(type->name()){
        case basic_type::TYPE_INT:
            return "integer";
            break;
        case basic_type::TYPE_STRING:
            return "string";
            break;
        case basic_type::TYPE_DOUBLE:
            return "real";
            break;
        case basic_type::TYPE_VOID:
            return "procedure";
            break;
        case basic_type::TYPE_POINTER:
            return "pointer";
        default: 
            return "undifinied";
    }
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  process_literal(node, lvl);
}
void xpl::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  process_literal(node, lvl);
}

void xpl::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  process_literal(node, lvl);
}
void xpl::xml_writer::do_and_node(cdk::and_node * const node, int lvl) {
}
void xpl::xml_writer::do_not_node(cdk::not_node * const node, int lvl) {
}
void xpl::xml_writer::do_or_node(cdk::or_node * const node, int lvl) {
}
//---------------------------------------------------------------------------

inline void xpl::xml_writer::do_unary_expression(cdk::unary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

//---------------------------------------------------------------------------

inline void xpl::xml_writer::do_binary_expression(cdk::binary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void xpl::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "<" << node->label() << ">" << node->name() << "</" << node->label() << ">" << std::endl;
}

void xpl::xml_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);

  node->lvalue()->accept(this, lvl);
  reset_new_symbol();

  node->rvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

/*void xpl::xml_writer::do_program_node(xpl::program_node * const node, int lvl) {
  openTag(node, lvl);
  node->statements()->accept(this, lvl + 4);
  closeTag(node, lvl);
}*/

//---------------------------------------------------------------------------

void xpl::xml_writer::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_print_node(xpl::print_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "<" << node->label() << " newline='" << node->newline() << "'" << ">" << std::endl;  
  openTag("argument", lvl + 2);  
  node->argument()->accept(this, lvl + 4);
  closeTag("argument", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

/*void xpl::xml_writer::do_read_node(xpl::read_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}*/


//---------------------------------------------------------------------------
void xpl::xml_writer::do_while_node(xpl::while_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::xml_writer::do_if_node(xpl::if_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void xpl::xml_writer::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------
void xpl::xml_writer::do_read_node(xpl::read_node * const node, int lvl) {
    openTag(node, lvl);    
    closeTag(node, lvl);
}
void xpl::xml_writer::do_stop_node(xpl::stop_node * const node, int lvl) {
    openTag(node, lvl);
    closeTag(node, lvl);
}
void xpl::xml_writer::do_sweep_plus_node(xpl::sweep_plus_node * const node, int lvl) {
    openTag(node, lvl);
    openTag("lvalue", lvl + 2);
    node->lvalue()->accept(this, lvl + 4);
    closeTag("lvalue", lvl + 2);
    openTag("expression1", lvl + 2);
    node->expression1()->accept(this, lvl + 4);
    closeTag("expression1", lvl + 2);
    openTag("expression2", lvl + 2);
    node->expression2()->accept(this, lvl + 4);
    closeTag("expression2", lvl + 2);
    openTag("expression3", lvl + 2);
    if(node->expression3() != nullptr){        
        node->expression3()->accept(this, lvl + 4);        
    }   
    closeTag("expression3", lvl + 2);
    openTag("block", lvl + 2);
    node->block()->accept(this, lvl + 4);
    closeTag("block", lvl + 2);
    closeTag(node, lvl);
}
void xpl::xml_writer::do_sweep_minus_node(xpl::sweep_minus_node * const node, int lvl) {
    openTag(node, lvl);
    openTag("lvalue", lvl + 2);
    node->lvalue()->accept(this, lvl + 4);
    closeTag("lvalue", lvl + 2);
    openTag("expression1", lvl + 2);
    node->expression1()->accept(this, lvl + 4);
    closeTag("expression1", lvl + 2);
    openTag("expression2", lvl + 2);
    node->expression2()->accept(this, lvl + 4);
    closeTag("expression2", lvl + 2);
     openTag("expression3", lvl + 2);
    if(node->expression3() != nullptr){       
        node->expression3()->accept(this, lvl + 4);        
    }  
    closeTag("expression3", lvl + 2);
    openTag("block", lvl + 2);
    node->block()->accept(this, lvl + 4);
    closeTag("block", lvl + 2);
    closeTag(node, lvl);    
}
void xpl::xml_writer::do_next_node(xpl::next_node * const node, int lvl) {
    openTag(node, lvl);
    closeTag(node, lvl);    
}
void xpl::xml_writer::do_return_node(xpl::return_node * const node, int lvl) {
    openTag(node, lvl);
    closeTag(node, lvl);
}
void xpl::xml_writer::do_function_declaration_node(xpl::function_declaration_node * const node, int lvl) {
    os() << std::string(lvl, ' ') << "<" << node->label() \
        << " qualifier='" << node->qualifier() << "'" \
        << " use='" << node->use() << "'" \
        << " identifier='" << *(node->identifier()) << "'" \
        << " type='" << typeToString(node->type()) << "'" \
        << ">" << std::endl;
    
    openTag("sequence", lvl + 2);
    node->sequence()->accept(this, lvl + 4);
    closeTag("sequence", lvl + 2);
    openTag("value", lvl + 2);
    if(node->value() != nullptr)
        node->value()->accept(this, lvl + 4);
    closeTag("value", lvl + 2);
    closeTag(node, lvl);
}
void xpl::xml_writer::do_function_definition_node(xpl::function_definition_node * const node, int lvl) {
    os() << std::string(lvl, ' ') << "<" << node->label() \
        << " qualifier='" << node->qualifier() << "'" \
        << " identifier='" << *(node->identifier()) << "'" \
        << " type='" << typeToString(node->type()) << "'" \
        << ">" << std::endl;
    openTag("sequence", lvl + 2);
    node->sequence()->accept(this, lvl + 4);
    closeTag("sequence", lvl + 2);
    openTag("value", lvl + 2);
    if(node->value() != nullptr)
        node->value()->accept(this, lvl + 4);
    closeTag("value", lvl + 2);
    openTag("block", lvl + 2);
    node->block()->accept(this, lvl + 4);
    closeTag("block", lvl + 2);
    closeTag(node, lvl);
}
void xpl::xml_writer::do_function_invocation_node(xpl::function_invocation_node * const node, int lvl) {
    os() << std::string(lvl, ' ') << "<" << node->label() \
        << " identifier='" << *(node->identifier()) << "'" \
        << ">" << std::endl;
    openTag("sequence", lvl + 2);
    node->sequence()->accept(this, lvl + 4);
    closeTag("sequence", lvl + 2);
    closeTag(node, lvl);
    
}
        
void xpl::xml_writer::do_null_node(xpl::null_node * const node, int lvl) {
    openTag(node, lvl);
    closeTag(node, lvl);
};
void xpl::xml_writer::do_variable_declaration_node(xpl::variable_declaration_node * const node, int lvl) {
    os() << std::string(lvl, ' ') << "<" << node->label() \
        << " qualifier='" << node->qualifier() << "'" \
        << " use='" << node->use() << "'" \
        << " type='" << typeToString(node->type()) << "'" \
        << " identifier='" << *(node->identifier()) << "'" \
        << ">" << std::endl;
    openTag("value", lvl + 2);
    if(node->value() != nullptr)
        node->value()->accept(this, lvl + 4);
    closeTag("value", lvl + 2);
    closeTag(node, lvl);
};
void xpl::xml_writer::do_block_node(xpl::block_node * const node, int lvl) {
    openTag(node, lvl);
    openTag("declaration", lvl + 2);
    if(node->declaration() != nullptr){       
        node->declaration()->accept(this, lvl + 4);        
    }   
    closeTag("declaration", lvl + 2);
    openTag("instruction", lvl + 2);
    if(node->instruction() != nullptr){        
        node->instruction()->accept(this, lvl + 4);        
    }   
    closeTag("instruction", lvl + 2);
    closeTag(node, lvl);
};
void xpl::xml_writer::do_identity_node(xpl::identity_node * const node, int lvl) {
    do_unary_expression(node, lvl); 
};
void xpl::xml_writer::do_address_node(xpl::address_node * const node, int lvl) {
    do_unary_expression(node, lvl); 
};
void xpl::xml_writer::do_malloc_node(xpl::malloc_node * const node, int lvl) {
    do_unary_expression(node, lvl);
};
void xpl::xml_writer::do_index_node(xpl::index_node * const node, int lvl) {
    openTag(node, lvl);
    openTag("left_value", lvl + 2);
    node->left_value()->accept(this, lvl + 4);
    closeTag("left_value", lvl + 2);   
    openTag("value", lvl + 2);
    node->value()->accept(this, lvl + 4);
    closeTag("value", lvl + 2);       
    closeTag(node, lvl);
};