#include "procedure_functions.h"
using namespace std;
// R19. <Return> -> return; | return <Expression>;
//---------------------------------------------------------------------------------------------------
bool procedureReturn(vector<token_323> &all_tokens, int &loc) {
  // save current location of reading token, and location of rule_holder vector
  // to help push rule if rule is used
  int loc_helper = loc;
  int rule_helper = all_tokens[loc].rule_holder.size();
  std::vector<std::string>::iterator it =
      all_tokens[loc_helper].rule_holder.begin();

  // get token and test rule

  token_323 token_holder;
  token_holder = all_tokens[loc];
  if (token_holder.lexeme() == "return") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == ";") {
      // token_holder.token_print_helper();
      loc++;

      std::string output_str = "<Return> -> return; \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

    } else if (procedureExpression(all_tokens, loc)) {
      token_holder = all_tokens[loc];
      if (token_holder.lexeme() == ";") {
        // token_holder.token_print_helper();
        loc++;

        std::string output_str = "<Return> -> return <Expression>; \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

      } else {
        throw std::logic_error("error, expecting ;");
      }
    } else {
      throw std::logic_error("error, expecting ; or <Expression>");
    }
  }
  return false;
}