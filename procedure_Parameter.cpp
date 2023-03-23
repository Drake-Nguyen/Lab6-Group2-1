#include "procedure_functions.h"
using namespace std;

// procedureIDs for_id2;
// procedureQualifier for_qual2;
// R7. <Parameter> -> <IDs >  <Qualifier>
//---------------------------------------------------------------------------------------------------
bool procedureParameter(vector<token_323> &all_tokens,
                        int &loc) // procedure for <Parameter>
{
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
  if (procedureIDs(all_tokens, loc)) {
    if (procedureQualifier(all_tokens, loc)) {

      std::string output_str = "<Parameter> -> <IDs> <Qualifier> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else {
      throw std::logic_error("error, expecting <Qualifier>");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}