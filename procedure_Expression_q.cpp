#include "procedure_functions.h"
using namespace std;
// R25.1 <Expression'>  -> ϵ | +<Term> <Expression'>  | -<Term> <Expression'>
//---------------------------------------------------------------------------------------------------
bool procedureExpressionq(vector<token_323> &all_tokens, int &loc) {
  // save current location of reading token, and location of rule_holder vector
  // to help push rule if rule is used
  int loc_helper = loc;
  int rule_helper = all_tokens[loc].rule_holder.size();
  std::vector<std::string>::iterator it =
      all_tokens[loc_helper].rule_holder.begin();

  // get token and test rule

  token_323 token_holder;
  token_holder = all_tokens[loc];
  if (token_holder.lexeme() == "+") //+ <Term> <Expression'>
  {

    // token_holder.token_print_helper();
    loc++;
    if (procedureTerm(all_tokens, loc)) {
      // instruction +
      instruction_table temp_ins;
      temp_ins.new_instruction("ADD", "nil");
      all_tokens[0].all_instructions.push_back(temp_ins);

      if (procedureExpressionq(all_tokens, loc)) {

        std::string output_str = "<Expression'>  -> + <Term> <Expression'> \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

      } else {
        throw std::logic_error("error, expecting <Expression'>");
      }
    } else {
      throw std::logic_error("error, expecting <Term>");
    }
  } else if (token_holder.lexeme() == "-") //-<Term> < Expression'>
  {
    // token_holder.token_print_helper();
    loc++;
    if (procedureTerm(all_tokens, loc)) {
      // instruction -
      instruction_table temp_ins;
      temp_ins.new_instruction("SUB", "nil");
      all_tokens[0].all_instructions.push_back(temp_ins);

      if (procedureExpressionq(all_tokens, loc)) {

        std::string output_str = "<Expression'>  -> - <Term> <Expression'> \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

      } else {
        throw std::logic_error("error, expecting <Expression'>");
      }
    } else {
      throw std::logic_error("error, expecting <Term>");
    }
  } else {

    std::string output_str = "<Expression'>  -> ϵ \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;
  }
  return false;
}