#include "procedure_functions.h"
using namespace std;

//procedureIDs for_id3;

bool procedurePrimary(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.token() == "Identifier") //<Identifier>
  {

    // instruction pushm
    instruction_table temp_ins;
    temp_ins.new_instruction("PUSHM", token_holder.lexeme());
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "(") //(
    {
      // token_holder.token_print_helper();
      loc++;
      if (procedureIDs(all_tokens, loc)) //<IDs>
      {
        token_holder = all_tokens[loc];
        if (token_holder.lexeme() == ")") //)
        {
          // token_holder.token_print_helper();
          loc++;

          std::string output_str = "<Primary> -> <Identifier> ( <IDs> )\n";
          all_tokens[loc_helper].rule_holder.push_back(output_str);
          // std::cerr << output_str;

          return_holder = true;
        } else {
          throw std::logic_error("error, expecting )");
        }
      } else {
        throw std::logic_error("error, expecting <IDs>");
      }
    } else {

      std::string output_str = "<Primary> -> <Identifier> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;
      return_holder = true;
    }
  } else if (token_holder.token() == "Integer") // <Integer>
  {
    // instruction pushi
    instruction_table temp_ins;
    temp_ins.new_instruction("PUSHI", token_holder.lexeme());
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;
    std::string output_str = "<Primary> -> <Integer>  \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (token_holder.lexeme() == "(") //( <Expression> )
  {

    // token_holder.token_print_helper();
    loc++;
    if (procedureExpression(all_tokens, loc)) //<Expression>
    {
      token_holder = all_tokens[loc];
      if (token_holder.lexeme() == ")") // )
      {
        // token_holder.token_print_helper();
        loc++;

        std::string output_str = "<Primary> -> ( <Expression> ) \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting )");
      }
    } else {
      throw std::logic_error("error, expecting <Expression>");
    }
  } else if (token_holder.token() == "Real") // <Real>
  {
    // token_holder.token_print_helper();
    loc++;

    std::string output_str = "<Primary> -> <Real> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (token_holder.lexeme() == "true") // True
  {
    // instruction push true
    instruction_table temp_ins;
    temp_ins.new_instruction("PUSHI", "1");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;

    std::string output_str = "<Primary> -> true \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (token_holder.lexeme() == "false") // false
  {

    // instruction push true
    instruction_table temp_ins;
    temp_ins.new_instruction("PUSHI", "0");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;

    std::string output_str = "<Primary> -> false \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else {
    return_holder = false;
  }
  return return_holder;
}