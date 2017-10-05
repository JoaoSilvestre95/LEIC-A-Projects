#ifndef __CDK_FUNCTIONINVOCATIONNODE_H__
#define __CDK_FUNCTIONINVOCATIONNODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing function_invocation nodes.
   */
  class function_invocation_node: public cdk::expression_node {
    std::string *_identifier;
    cdk::sequence_node *_sequence;

  public:
    inline function_invocation_node(int lineno, std::string *identifier, cdk::sequence_node *sequence) :
        cdk::expression_node(lineno), _identifier(identifier), _sequence(sequence) {
    }

  public:
    inline std::string *identifier() {
      return _identifier;
    }
    inline cdk::sequence_node *sequence() {
      return _sequence;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_invocation_node(this, level);
    }

  };

} // xpl

#endif
