#include "procedure_functions.h"
using namespace std;

        // R13. <IDs> -> <Identifier> | <Identifier>, <IDs>
        //---------------------------------------------------------------------------------------------------

    bool procedureIDs(vector<token_323> &all_tokens,
                int &loc) // procedure for <IDs>
    {
        int loc_helper = loc;
        int rule_helper = all_tokens[loc].rule_holder.size();
        std::vector<std::string>::iterator it =
            all_tokens[loc_helper].rule_holder.begin();

        int decider = 0;
        bool return_holder = false;
        token_323 token_holder;
        token_holder = all_tokens[loc]; // get token from collection
        if (identifierHelper(token_holder)) {
            // token_holder.token_print_helper();
            loc++;

            token_holder = all_tokens[loc]; // check what is next token
            if (token_holder.lexeme() ==
                ",") // test if it is case <IDs> -> <Identifier>, <IDs>
            {
            // token_holder.token_print_helper();
            loc++;

            if (procedureIDs(all_tokens, loc)) {
                std::string output_str = "<IDs> -> <Identifier> \n";
                all_tokens[loc_helper].rule_holder.push_back(output_str);
                // std::cerr << output_str;
                return_holder = true;
            } else // test failed, wrong gramma, output error message
            {
                throw std::logic_error("error, expecting <IDs>");
            }
            } else // if it is not, then is case <IDs> -> <Identifier>
            {
            std::string output_str = "<IDs> -> <Identifier>, <IDs> \n";
            all_tokens[loc_helper].rule_holder.push_back(output_str);
            // std::cerr << output_str;
            return_holder = true;
            }
        } else // not this gramma, return false
        {
            return_holder = false;
            {}
        }
        return return_holder;
    }

