#include "procedure_functions.h"
using namespace std;
// R20. <Print> -> put(<Expression>);
//---------------------------------------------------------------------------------------------------
bool procedure_Print(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "put") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "(") {
      // token_holder.token_print_helper();
      loc++;

      token_holder = all_tokens[loc];
      if (procedure_Expression(all_tokens, loc)) {
        token_holder = all_tokens[loc];
        if (token_holder.lexeme() == ")") {

          // token_holder.token_print_helper();
          loc++;

          instruction_table temp_ins;
          temp_ins.new_instruction("STDOUT", "nil");
          all_tokens[0].all_instructions.push_back(temp_ins);

          token_holder = all_tokens[loc];
          if (token_holder.lexeme() == ";") {
            // token_holder.token_print_helper();
            loc++;

            std::string output_str = "<Print> -> put(<Expression>); \n";
            all_tokens[loc_helper].rule_holder.push_back(output_str);
            // std::cerr << output_str;

            return_holder = true;
          } else {
            throw std::logic_error("error, expecting ;");
          }
        } else {
          throw std::logic_error("error, expecting )");
        }
      } else {
        throw std::logic_error("error, expecting <Expression>");
      }
    } else {
      throw std::logic_error("error, expecting (");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}
