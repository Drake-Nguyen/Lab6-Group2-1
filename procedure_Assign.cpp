#include "procedure_functions.h"
using namespace std;
// R17. <Assign> -> <Identifier> = <Expression>;
//---------------------------------------------------------------------------------------------------
bool procedure_Assign(vector<token_323> &all_tokens, int &loc) {
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
  if (identifier_helper(token_holder)) {
    // id saved
    string temp_token = token_holder.lexeme();

    // token_holder.token_print_helper();
    loc++;

    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "=") {
      // token_holder.token_print_helper();
      loc++;
      if (procedure_Expression(all_tokens, loc)) {
        token_holder = all_tokens[loc];
        // add popm instruction
        instruction_table temp_ins;
        temp_ins.new_instruction("POPM", temp_token);
        all_tokens[0].all_instructions.push_back(temp_ins);

        if (token_holder.lexeme() == ";") {
          // token_holder.token_print_helper();
          loc++;

          std::string output_str = "<Identifier> = <Expression>; \n";
          all_tokens[loc_helper].rule_holder.push_back(output_str);
          // std::cerr << output_str;

          return_holder = true;
        } else {
          throw std::logic_error("error, expecting ;");
        }

      } else {
        throw std::logic_error("error, expecting <Expression>");
      }
    } else {

      throw std::logic_error("error, expecting =");
      std::cerr << token_holder.lexeme() << "\n";
      token_holder = all_tokens[loc + 1];
      std::cerr << token_holder.lexeme() << "\n";
      token_holder = all_tokens[loc - 1];
      std::cerr << token_holder.lexeme() << "\n";
      return_holder = false;
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}