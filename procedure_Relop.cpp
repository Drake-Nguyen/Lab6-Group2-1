#include "procedure_functions.h"
using namespace std;
// R24. <Relop> -> ==   |   !=    | > | <    |  <=   | = >
//---------------------------------------------------------------------------------------------------
bool procedureRelop(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "==") {
    instruction_table temp_ins;
    temp_ins.new_instruction("EQU", "exchange next");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;

    std::string output_str = "<Relop> -> == \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (token_holder.lexeme() == "!=") {
    instruction_table temp_ins;
    temp_ins.new_instruction("NEQ", "exchange next");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;

    std::string output_str = "<Relop> -> != \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (token_holder.lexeme() == ">") {
    instruction_table temp_ins;
    temp_ins.new_instruction("GRT", "exchange next");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;

    std::string output_str = "<Relop> -> > \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (token_holder.lexeme() == "<") {
    instruction_table temp_ins;
    temp_ins.new_instruction("LES", "exchange next");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;

    std::string output_str = "<Relop> -> < \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (token_holder.lexeme() == "<=") {
    instruction_table temp_ins;

    temp_ins.new_instruction("EQU", "exchange +3");
    all_tokens[0].all_instructions.push_back(temp_ins);
    temp_ins.new_instruction("GRT", "nil");
    all_tokens[0].all_instructions.push_back(temp_ins);
    temp_ins.new_instruction("PUSHI", "0");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;

    std::string output_str = "<Relop> -> <= \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (token_holder.lexeme() == "=>") {
    instruction_table temp_ins;

    temp_ins.new_instruction("EQU", "exchange +3");
    all_tokens[0].all_instructions.push_back(temp_ins);
    temp_ins.new_instruction("LES", "nil");
    all_tokens[0].all_instructions.push_back(temp_ins);
    temp_ins.new_instruction("PUSHI", "0");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;

    std::string output_str = "<Relop> -> => \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else {
    return_holder = false;
  }
  return return_holder;
}