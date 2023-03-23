#include "procedure_functions.h"
using namespace std;
// R26.1 <Term'> -> * <Factor> <Term>' | / <Factor> <Term>' | ϵ
//---------------------------------------------------------------------------------------------------
bool procedureTermq(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "*") //* <Factor> <Term>'
  {

    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (procedureFactor(all_tokens, loc)) {
      // instruction *
      instruction_table temp_ins;
      temp_ins.new_instruction("MUL", "nil");
      all_tokens[0].all_instructions.push_back(temp_ins);

      if (procedureTermq(all_tokens, loc)) {
        std::string output_str = "<Term'> -> * <Factor> <Term>' \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting <Term>'");
      }
    } else {
      throw std::logic_error("error, expecting <Factor>");
    }
  } else if (token_holder.lexeme() == "/") //* <Factor> <Term>'
  {

    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (procedureFactor(all_tokens, loc)) {
      // instruction  /
      instruction_table temp_ins;
      temp_ins.new_instruction("DIV", "nil");
      all_tokens[0].all_instructions.push_back(temp_ins);

      if (procedureTermq(all_tokens, loc)) {
        std::string output_str = "<Term'> -> / <Factor> <Term>' \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting <Term>'");
      }
    } else {
      throw std::logic_error("error, expecting <Factor>");
    }
  } else // ϵ
  {
    std::string output_str = "<Term'>  -> ϵ \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  }
  return return_holder;
}