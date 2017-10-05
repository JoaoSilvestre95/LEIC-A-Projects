#ifndef __CDK_MALLOCNODE_H__
#define __CDK_MALLOCNODE_H__

#include <cdk/ast/unary_expression_node.h>
#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing malloc nodes.
   */
  class malloc_node: public cdk::unary_expression_node {   

  public:
    inline malloc_node(int lineno, cdk::expression_node *expression) :
        unary_expression_node(lineno, expression){
    }

  public:   

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_malloc_node(this, level);
    }

  };

} // xpl

#endif
