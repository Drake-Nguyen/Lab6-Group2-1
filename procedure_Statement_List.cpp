#include "procedure_functions.h"
using namespace std;
// R14. <Statement List> -> <Statement> | <Statement> <Statement List>
//---------------------------------------------------------------------------------------------------
bool procedureStatementList(vector<token_323> &all_tokens, int &loc) {
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
  if (procedureStatement(all_tokens, loc)) {
    token_holder = all_tokens[loc];
    if (procedureStatementList(all_tokens, loc)) {

      std::string output_str =
          "<Statement List> -> <Statement> <Statement List>\n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else {
      std::string output_str = "<Statement List> -> <Statement> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}
