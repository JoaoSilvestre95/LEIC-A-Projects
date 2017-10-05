// $Id: function_definition_node.h,v 1.4 2017/05/13 19:53:37 ist180996 Exp $ -*- c++ -*-
#ifndef __XPL_FUNCTIONDEFINITIONNODE_H__
#define __XPL_FUNCTIONDEFINITIONNODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/basic_type.h>
#include "block_node.h"


namespace xpl {

  /**
   * Class for describing function_definition nodes.
   */
  class function_definition_node: public cdk::basic_node {
    bool _qualifier;
    basic_type *_type;
    std::string *_identifier;
    cdk::sequence_node *_sequence;
    cdk::expression_node *_value;
    block_node *_block;
  
  public:
    inline function_definition_node(int lineno, bool qualifier, basic_type *type, std::string *identifier, cdk::sequence_node *sequence, cdk::expression_node *value, block_node *block) :
        cdk::basic_node(lineno), _qualifier(qualifier), _type(type), _identifier(identifier), _sequence(sequence), _value(value), _block(block) {
    }

  public:
    inline bool qualifier() {
      return _qualifier;
    }
    
    inline basic_type *type(){
      return _type;        
    }
    inline std::string *identifier() {
      return _identifier;
    }
    inline cdk::sequence_node *sequence() {
      return _sequence;
    }
    inline cdk::expression_node *value() {
      return _value;
    }
    inline block_node *block() {
      return _block;
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_definition_node(this, level);
    }

  };

} // xpl

#endif
