#ifndef __XPL_SEMANTICS_SYMBOL_H__
#define __XPL_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>
//#include <cdk/ast/expression_node.h>

namespace xpl {

    class symbol {
      basic_type *_type;
      std::string _name;
      
      std::vector<basic_type*> _args; //args of function
      int _offset;
      
      bool _is_function; //if is a function or a variable
      bool _is_defined; //if is function declared or not;
      bool _is_public; //if is public
      bool _is_use; //if is use;
      

    public:
      inline symbol(basic_type *type, const std::string &name) : _type(type), _name(name){}
      inline symbol(basic_type *type, const std::string &name, bool is_function,  bool is_defined, bool is_public, bool is_use, std::vector<basic_type*> args) :
          _type(type), _name(name), _is_function(is_function), _is_defined(is_defined), _is_public(is_public), _is_use(is_use), _args(args) {
      }

      virtual ~symbol() {
        delete _type;
      }

      inline basic_type *type() const {
        return _type;
      }
      inline const std::string &name() const {
        return _name;
      }
      inline bool is_function()
      {
      	return _is_function;
      }
      inline void is_function(bool value)
      {
     	 _is_function = value;
      }
      inline bool  is_defined(){
      	return _is_defined;
      }
      inline void is_defined(bool is_defined)
      {
     	 _is_defined = is_defined;
      }
      inline bool  is_public()
      {
      	return _is_public;
      }
      inline void is_public(bool is_public)
      {
     	 _is_public = is_public;
      }
      
      inline bool  is_use()
      {
      	return _is_use;
      }
      inline void is_use(bool is_use)
      {
     	 _is_use = is_use;
      }
      inline void offset(int o){
        _offset=o;
      }
      inline int offset(){
        return _offset;
      }
      inline std::vector<basic_type*> args() {
	return _args;
      }
      inline void args(basic_type* type) {
	_args.push_back(type);
      }
      /*inline long value() const {
        return _value;
      }
      inline long value(long v) {
        return _value = v;
      }*/
    };

} // xpl

#endif
