#include "procedure_functions.h"
using namespace std;

// procedureIDs for_id4;
//  R21. <Scan> -> get( <IDs> );
//---------------------------------------------------------------------------------------------------
bool procedureScan(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "get") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "(") {
      // token_holder.token_print_helper();
      loc++;
      token_holder = all_tokens[loc];
      int j = loc;
      if (procedureIDs(all_tokens, loc)) {
        // instruction for scan
        instruction_table temp;
        temp.new_instruction("STDIN", "nil");
        all_tokens[0].all_instructions.push_back(temp);
        string temp_id = all_tokens[j].lexeme();
        temp.new_instruction("POPM", temp_id);
        all_tokens[0].all_instructions.push_back(temp);
        j++;
        if (all_tokens[j].lexeme() == ",") {
          while (all_tokens[j].lexeme() == ",") {
            j++;
            temp.new_instruction("STDIN", "nil");
            all_tokens[0].all_instructions.push_back(temp);
            string temp_id = all_tokens[j].lexeme();
            temp.new_instruction("POPM", temp_id);
            all_tokens[0].all_instructions.push_back(temp);
            j++;
          }
        }

        token_holder = all_tokens[loc];
        if (token_holder.lexeme() == ")") {
          // token_holder.token_print_helper();
          loc++;
          token_holder = all_tokens[loc];
          if (token_holder.lexeme() == ";") {
            // token_holder.token_print_helper();
            loc++;

            std::string output_str = "<Scan> -> get(<IDs>); \n";
            all_tokens[loc_helper].rule_holder.push_back(output_str);
            // std::cerr << output_str;

            return_holder = true;
          } else {
            throw std::logic_error("error, expecting ;");
          }
        } else {
          throw std::logic_error("error, expecting )");
        }
      } else {
        throw std::logic_error("error, expecting <IDs>");
      }
    } else {
      throw std::logic_error("error, expecting (");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}