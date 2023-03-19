#include "procedure_functions.h"
using namespace std;
// R4. <Function> -> function  <Identifier>  (  <Opt Parameter List>  )   < Opt
// Declaration List >   <Body>
//---------------------------------------------------------------------------------------------------
// tbf
bool procedure_Function(vector<token_323> &all_tokens, int &loc) {
  // save current location of reading token, and location of rule_holder vector
  // to help push rule if rule is used
  int loc_helper = loc;
  int rule_helper = all_tokens[loc].rule_holder.size();
  std::vector<std::string>::iterator it =
      all_tokens[loc_helper].rule_holder.begin();

  // get token and test rule
  bool return_holder = false;
  token_323 token_holder;
  token_holder = all_tokens[loc];
  if (token_holder.lexeme() == "function") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (identifier_helper(token_holder)) {
      // token_holder.token_print_helper();
      loc++;
      token_holder = all_tokens[loc];
      if (token_holder.lexeme() == "(") {
        // token_holder.token_print_helper();
        loc++;
        token_holder = all_tokens[loc];
        if (procedure_Opt_Parameter_List(all_tokens, loc)) {
          token_holder = all_tokens[loc];
          if (token_holder.lexeme() == ")") {
            // token_holder.token_print_helper();
            loc++;
            token_holder = all_tokens[loc];
            if (procedure_Opt_Declaration_List(all_tokens, loc)) {
              token_holder = all_tokens[loc];
              if (procedure_Body(all_tokens, loc)) {

                std::string output_str =
                    "<Function> -> function <Identifier> ( <Opt Parameter "
                    "List> ) < Opt Declaration List > <Body> \n";
                all_tokens[loc_helper].rule_holder.push_back(output_str);
                // std::cerr << output_str;

                return_holder = true;
              } else {
                throw std::logic_error("error, expecting <Body>");
              }
            } else {
              throw std::logic_error(
                  "error, expecting < Opt Declaration List >");
              return_holder = false;
            }
          } else {
            throw std::logic_error("error, expecting )");
          }
        } else {
          throw std::logic_error("error, expecting <Opt Parameter List>");
        }
      } else {
        throw std::logic_error("error, expecting (");
      }
    } else {
      throw std::logic_error("error, expecting <Identifier>");
    }
  } else {
    return_holder = false;
  }

  if (return_holder == true) {
    throw std::logic_error(
        "Error, Function is not supported by simplified Rat20F");
    return_holder = false;
  }
  return return_holder;
}