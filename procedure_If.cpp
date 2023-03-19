#include "procedure_functions.h"
using namespace std;

// R18. <If> -> if (<Condition>) < Statement > fi | if (<Condition>) < Statement
// > else  <Statement>  fi
//---------------------------------------------------------------------------------------------------
bool procedure_If(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "if") // if
  {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "(") //  (
    {
      // token_holder.token_print_helper();
      loc++;
      token_holder = all_tokens[loc];
      if (procedure_Condition(all_tokens, loc)) //<Condition>
      {
        token_holder = all_tokens[loc];
        if (token_holder.lexeme() == ")") //  )
        {
          instruction_table temp_ins;
          temp_ins.new_instruction("JUMPZ", "next label");
          all_tokens[0].all_instructions.push_back(temp_ins);

          // token_holder.token_print_helper();
          loc++;
          if (procedure_Statement(all_tokens, loc)) // < Statement >
          {
            instruction_table temp_ins;
            temp_ins.new_instruction("LABEL", "nil");
            all_tokens[0].all_instructions.push_back(temp_ins);

            token_holder = all_tokens[loc];
            if (token_holder.lexeme() == "fi") // fi
            {
              // token_holder.token_print_helper();
              loc++;

              std::string output_str =
                  "<If> -> if (<Condition>) < Statement > fi\n";
              all_tokens[loc_helper].rule_holder.push_back(output_str);
              // std::cerr << output_str;

              return_holder = true;
            } else if (token_holder.lexeme() ==
                       "else") // | if (<Condition>) < Statement >.  else
                               // <Statement>  fi , testing if lexeme is else
            {
              // token_holder.token_print_helper();
              loc++;
              if (procedure_Statement(all_tokens, loc)) //<Statement>
              {
                token_holder = all_tokens[loc];
                if (token_holder.lexeme() == "fi") // fi
                {
                  // token_holder.token_print_helper();
                  loc++;

                  std::string output_str =
                      "if (<Condition>) < Statement > else  <Statement>  fi \n";
                  all_tokens[loc_helper].rule_holder.push_back(output_str);
                  // std::cerr << output_str;

                  return_holder = true;
                } else {
                  throw std::logic_error("error, expecting fi");
                }
              } else {
                throw std::logic_error("error, expecting < Statement > ");
              }
            } else {
              throw std::logic_error("error, expecting fi or else ");
            }
          } else {
            throw std::logic_error("error, expecting < Statement > ");
          }
        } else {
          throw std::logic_error("error, expecting ) ");
        }
      } else {
        throw std::logic_error("error, expecting <Condition> ");
      }
    } else {
      throw std::logic_error("error, expecting (");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}