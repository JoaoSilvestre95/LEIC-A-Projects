// $Id: block_node.h,v 1.4 2017/03/24 14:33:55 ist180996 Exp $ -*- c++ -*-
#ifndef __CDK_BLOCKNODE_H__
#define __CDK_BLOCKNODE_H__

#include <cdk/ast/sequence_node.h>

namespace xpl {

  /**
   * Class for describing block-then nodes.
   */
  class block_node: public cdk::basic_node {
   cdk::sequence_node *_declaration, *_instruction;
   
  public:
    inline block_node(int lineno, cdk::sequence_node *declaration, cdk::sequence_node *instruction) :
        cdk::basic_node(lineno), _declaration(declaration), _instruction(instruction){
    }

  public:   
    inline cdk::sequence_node *declaration() {
      return _declaration;
    }
    inline cdk::sequence_node *instruction() {
      return _instruction;
    }
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_block_node(this, level);
    }

  };

} // xpl

#endif
