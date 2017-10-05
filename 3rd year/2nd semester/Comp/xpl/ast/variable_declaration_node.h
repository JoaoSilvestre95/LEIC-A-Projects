
#ifndef __CDK_VARIABLE_DECLARATION_NODE_H__
#define __CDK_VARIABLE_DECLARATION_NODE_H__

#include <cdk/ast/expression_node.h>

namespace xpl {

  /**
   * Class for describing variable_declaration nodes.
   */
  class variable_declaration_node: public cdk::basic_node {
    bool _qualifier;
    bool _use;
    basic_type *_type;
    std::string *_identifier;
    cdk::expression_node *_value;

  public:
    inline variable_declaration_node(int lineno, bool qualifier, bool use, std::string *identifier, basic_type *type, cdk::expression_node *value) :
        cdk::basic_node(lineno), _qualifier(qualifier), _use(use), _type(type), _identifier(identifier), _value(value) {
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
    
    inline cdk::expression_node *value() {
      return _value;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_declaration_node(this, level);
    }

  };

} // xpl

#endif
