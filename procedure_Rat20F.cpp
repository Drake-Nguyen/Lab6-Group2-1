#include "procedure_functions.h"
using namespace std;
// R1. <Rat20F>  -> <Opt Function Definitions>   $$  <Opt Declaration List>
// <Statement List>  $$
//---------------------------------------------------------------------------------------------------
bool procedureRat20F(vector<token_323> &all_tokens, int &loc) {
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
  if (procedureOptFunctionDefinitions(all_tokens, loc)) {
    // throw std::logic_error("" << "test seg 1" << "");
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "$$") {
      // throw std::logic_error("" << "$$" << "");
      // throw std::logic_error("" << "test seg 2" << "");
      // token_holder.token_print_helper();
      loc++;
      if (procedureOptDeclarationList(all_tokens, loc)) {
        // throw std::logic_error("" << "test seg 3" << "");
        // std::cerr << "\n" << all_tokens[loc].lexeme() << all_tokens[loc -
        // 1].lexeme() << "\n" << all_tokens[loc + 1].lexeme() << "\n" <<
        // "\n\n";
        if (procedureStatementList(all_tokens, loc)) {
          // throw std::logic_error("" << "test seg 4" << "");
          token_holder = all_tokens[loc];
          if (token_holder.lexeme() == "$$") {
            // throw std::logic_error("" << "test seg 5" << "");
            // token_holder.token_print_helper();
            loc++;
            if (loc >= all_tokens.size()) {

              std::string output_str =
                  "<Rat20F> -> <Opt Function Definitions>   $$  <Opt "
                  "Declaration List>  <Statement List>  $$ \n";
              all_tokens[loc_helper].rule_holder.push_back(output_str);
              // std::cerr << output_str;

              return true;
            } else {
              std::cerr << "\n"
                        << "should end here"
                        << "\n\n";
              procedureRat20F(all_tokens, loc);
            }
          } else {
            throw std::logic_error("error, expecting $$");
            // std::cerr << "\n" << all_tokens[loc].lexeme() << "\n" <<
            // all_tokens[loc -1].lexeme() << "\n"<< all_tokens[loc+1].lexeme()
            // << "\n" << "\n\n";
          }
        } else {
          throw std::logic_error("error, expecting <Statement List>");
        }
      } else {
        throw std::logic_error("error, expecting <Opt Declaration List>");
      }
    } else {
      throw std::logic_error("error, expecting $$");
    }
  } else {
    throw std::logic_error("error, expecting <Opt Function Definitions>");
  }

  return return_holder;
}