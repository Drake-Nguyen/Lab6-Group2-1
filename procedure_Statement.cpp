#include "procedure_functions.h"
using namespace std;
// R15. <Statement> -> <Compound> | <Assign> | <If> | <Return> | <Print> |
// <Scan> | <While>
//---------------------------------------------------------------------------------------------------
bool procedureStatement(vector<token_323> &all_tokens, int &loc) {
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
  if (procedureCompound(all_tokens, loc)) //<Compound>
  {

    std::string output_str = "<Statement> -> <Compound> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedureAssign(all_tokens, loc)) // <Assign>
  {

    std::string output_str = "<Statement> -> <Assign> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedureIf(all_tokens, loc)) // <If>
  {

    std::string output_str = "<Statement> -> <If>  \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedureReturn(all_tokens, loc)) // <Return>
  {

    std::string output_str = "<Statement> -> <Return> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedurePrint(all_tokens, loc)) //<Print>
  {

    std::string output_str = "<Statement> -> <Print> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedureScan(all_tokens, loc)) // <Scan>
  {

    std::string output_str = "<Statement> -> <Scan> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedureWhile(all_tokens, loc)) //<While>
  {
    std::string output_str = "<Statement> -> <While> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else {
    return_holder = false;
  }
  return return_holder;
}