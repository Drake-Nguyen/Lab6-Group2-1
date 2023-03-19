#include "procedure_functions.h"
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class procedureQualifier {

  private:

  public: 
    
    // R8. <Qualifier> -> int | boolean | real
    //---------------------------------------------------------------------------------------------------
    bool procedure_Qualifier(vector<token_323> &all_tokens,
                         int &loc) // procedure for <Qualifier>
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

      if (token_holder.lexeme() == "int") {
        // token_holder.token_print_helper();
        loc++;

        std::string output_str = "<Qualifier> -> int \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else if (token_holder.lexeme() == "boolean") {
        // token_holder.token_print_helper();
        loc++;

        std::string output_str = "<Qualifier> -> boolean \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else if (token_holder.lexeme() == "real") {
        // token_holder.token_print_helper();
        loc++;

        std::string output_str = "<Qualifier> -> real \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        return_holder = false;
      }

      return return_holder;
    }

};


