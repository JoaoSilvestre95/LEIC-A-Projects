
#ifndef __XPL_INDEXNODE_H__
#define __XPL_INDEXNODE_H__


#include <cdk/ast/lvalue_node.h>
#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing index nodes.
   */
  class index_node: public cdk::lvalue_node {
    cdk::expression_node *_left_value;
    cdk::expression_node *_value;
    
  public:
    inline index_node(int lineno, cdk::expression_node *left_value, cdk::expression_node *value) : cdk::lvalue_node(lineno), _left_value(left_value), _value(value) {}

  public:
    inline cdk::expression_node *left_value() {
      return _left_value;
    }
    inline cdk::expression_node *value() {
      return _value;
    }
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_index_node(this, level);
    }

  };

} // xpl

#endif