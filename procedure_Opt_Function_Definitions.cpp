#include "procedure_functions.h"
using namespace std;
// R2. <Opt Function Definitions> -> <Function Definitions> | <Empty>
//---------------------------------------------------------------------------------------------------
bool procedureOptFunctionDefinitions(vector<token_323> &all_tokens, int &loc) {
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
  if (procedureFunctionDefinitions(all_tokens, loc)) {

    std::string output_str =
        "<Opt Function Definitions> -> <Function Definitions> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else {

    std::string output_str = "<Opt Function Definitions> -> <Empty> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  }

  return return_holder;
}