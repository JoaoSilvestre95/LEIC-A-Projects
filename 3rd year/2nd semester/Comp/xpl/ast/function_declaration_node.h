#ifndef __CDK_FUNCTIONDECLARATIONNODE_H__
#define __CDK_FUNCTIONDECLARATIONNODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/basic_type.h>


namespace xpl {

  /**
   * Class for describing function_declaration nodes.
   */
  class function_declaration_node: public cdk::basic_node {
    bool _qualifier;
    bool _use;    
    std::string *_identifier;
    basic_type *_type;
    cdk::sequence_node *_sequence;
    cdk::expression_node *_value;

  public:
    inline function_declaration_node(int lineno, bool qualifier, bool use, std::string *identifier, basic_type *type, cdk::sequence_node *sequence, cdk::expression_node *value) :
        cdk::basic_node(lineno), _qualifier(qualifier), _use(use), _identifier(identifier), _type(type), _sequence(sequence), _value(value) {
    }

  public:
    inline bool qualifier() {
      return _qualifier;
    }
    inline bool use() {
      return _use;
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

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_declaration_node(this, level);
    }

  };

} // xpl

#endif
