#include "procedure_functions.h"
using namespace std;
// R22. <While> -> while (<Condition>) < Statement >
//---------------------------------------------------------------------------------------------------
bool procedure_While(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "while") {
    // label
    instruction_table temp_ins;
    temp_ins.new_instruction("LABEL", "nil");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "(") {
      // token_holder.token_print_helper();
      loc++;
      token_holder = all_tokens[loc];
      if (procedure_Condition(all_tokens, loc)) {
        token_holder = all_tokens[loc];
        if (token_holder.lexeme() == ")") {
          // jump after cmp
          instruction_table temp_ins;
          temp_ins.new_instruction("JUMPZ", "next jump");
          all_tokens[0].all_instructions.push_back(temp_ins);

          // token_holder.token_print_helper();
          loc++;
          if (procedure_Statement(all_tokens, loc)) {
            // jmp
            instruction_table temp_ins;
            temp_ins.new_instruction("JUMP", "last label");
            all_tokens[0].all_instructions.push_back(temp_ins);

            std::string output_str =
                "<While> -> while (<Condition>) < Statement > \n";
            all_tokens[loc_helper].rule_holder.push_back(output_str);
            // std::cerr << output_str;

            return_holder = true;
          } else {
            throw std::logic_error("error, expecting < Statement >");
          }
        } else {
          throw std::logic_error("error, expecting )");
        }
      } else {
        throw std::logic_error("error, expecting <Condition>");
      }
    } else {
      throw std::logic_error("error, expecting (");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}
