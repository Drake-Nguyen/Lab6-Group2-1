#include "procedure_functions.h"
using namespace std;

// procedureIDs for_id1;
// procedureQualifier for_qual1;
// R12. <Declaration> -> <Qualifier > <IDs>
//---------------------------------------------------------------------------------------------------
bool procedureDeclaration(vector<token_323> &all_tokens, int &loc) {
  // save current location of reading token, and location of rule_holder vector
  // to help push rule if rule is used
  int loc_helper = loc;
  int rule_helper = all_tokens[loc].rule_holder.size();
  std::vector<std::string>::iterator it =
      all_tokens[loc_helper].rule_holder.begin();

  // get token and test rule

  token_323 token_holder;
  token_holder = all_tokens[loc];
  if (procedureQualifier(all_tokens, loc)) {
    token_holder = all_tokens[loc];
    if (procedureIDs(all_tokens, loc)) {

      std::string output_str = "<Declaration> -> <Qualifier > <IDs> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

    } else {
      throw std::logic_error("error, expecting <IDs>");
    }
  } else {
  }
  return false;
}