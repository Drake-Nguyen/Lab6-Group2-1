#include "procedure_functions.h"
using namespace std;

procedureIDs for_id3;

bool is_identifier(const token_323& token) {
  return token.token() == "Identifier";
}

bool is_integer(const token_323& token) {
  return token.token() == "Integer";
}

bool is_real(const token_323& token) {
  return token.token() == "Real";
}

bool is_true(const token_323& token) {
  return token.lexeme() == "true";
}

bool is_false(const token_323& token) {
  return token.lexeme() == "false";
}

void push_instruction(const string& op, const string& operand,
                      vector<instruction_table>& instructions) {
  instruction_table temp_ins;
  temp_ins.new_instruction(op, operand);
  instructions.push_back(temp_ins);
}

bool procedurePrimary(vector<token_323>& all_tokens, int& loc) {
  int loc_helper = loc;
  int rule_helper = all_tokens[loc].rule_holder.size();
  auto& rule_holder = all_tokens[loc_helper].rule_holder;
  auto& instructions = all_tokens[0].all_instructions;

  token_323 token_holder = all_tokens[loc];
  bool return_holder = false;

  if (is_identifier(token_holder)) {
    push_instruction("PUSHM", token_holder.lexeme(), instructions);

    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "(") {
      loc++;
      if (for_id3.procedureIDs(all_tokens, loc)) {
        token_holder = all_tokens[loc];
        if (token_holder.lexeme() == ")") {
          loc++;
          rule_holder.push_back("<Primary> -> <Identifier> ( <IDs> )\n");
          return_holder = true;
        } else {
          throw std::logic_error("error, expecting )");
        }
      } else {
        throw std::logic_error("error, expecting <IDs>");
      }
    } else {
      rule_holder.push_back("<Primary> -> <Identifier> \n");
      return_holder = true;
    }
  } else if (is_integer(token_holder)) {
    push_instruction("PUSHI", token_holder.lexeme(), instructions);

    loc++;
    rule_holder.push_back("<Primary> -> <Integer>  \n");
    return_holder = true;
  } else if (token_holder.lexeme() == "(") {
    loc++;
    if (procedureExpression(all_tokens, loc)) {
      token_holder = all_tokens[loc];
      if (token_holder.lexeme() == ")") {
        loc++;
        rule_holder.push_back("<Primary> -> ( <Expression> ) \n");
        return_holder = true;
      } else {
        throw std::logic_error("error, expecting )");
      }
    } else {
      throw std::logic_error("error, expecting <Expression>");
    }
  } else if (is_real(token_holder)) {
    loc++;
    rule_holder.push_back("<Primary> -> <Real> \n");
    return_holder = true;
  } else if (is_true(token_holder)) {
    push_instruction("PUSHI", "1", instructions);

    loc++;
    rule_holder.push_back("<Primary> -> true \n");
    return_holder = true;
  } else if (is_false(token_holder)) {
    push_instruction("PUSHI", "0", instructions);

    loc++;
    rule_holder.push_back("<Primary> -> false \n");
    return_holder = true;
  } else {
    return_holder = false;
  }

  return return_holder;
}
