
/*
This file contains implementation of all recursive functions for parser.
        one helper function (identifier_helper) is also here. It accepts a
token, and returns true if token string = Identifier. False otherwise. There are
some codes use for debugging that was left undeleted inside this file. Some of
then was commented, some of them are not.

All recursive functions are in this form:

        bool procedure_XXX(vector<token_323>& all_tokens, int& loc)

vector all_tokens is a token_323 class vector that stores all tokens LA read
from input file. loc is used to help recursive functions to determine which
token it should read now. These functions test if certain gramma is used. They
return true if this gramma is used, false other wise.

The logic of all recursive functions is in this form:

        1: save current loc into an int (loc_helper) for later use.
        2: call recursive functions of other procedure, or test functions for
terminals according to its gramma and determine if those rules are true. 3:
whenever a terminal is read, loc increase by one. 4: whenever a terminal is read
but the gramma is not used, loc decrease to the loc at the beginning of the
function. (That is, loc = loc_helper. However, actural implementation uses
several loc-- due to the debugging process) 5: if the rule the function
represents is test true (this rule is used), push string of this rule to the
location represented by loc_helper of vector all_tokens (push into rule_holder
string vector of class token_323). to output rule in correct sequence, push
front is needed. But for coding convenience, push_back and print out backwordly
are used.
*/

#include "procedure_functions.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// a helper function to help recognize identifier
bool identifier_helper(token_323 input_token) {
  if (input_token.token() == "Identifier") {
    return true;
  } else {
    return false;
  }
}

// R13. <IDs> -> <Identifier> | <Identifier>, <IDs>
//---------------------------------------------------------------------------------------------------
bool procedure_IDs(vector<token_323> &all_tokens,
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
  if (identifier_helper(token_holder)) {
    // token_holder.token_print_helper();
    loc++;

    token_holder = all_tokens[loc]; // check what is next token
    if (token_holder.lexeme() ==
        ",") // test if it is case <IDs> -> <Identifier>, <IDs>
    {
      // token_holder.token_print_helper();
      loc++;

      if (procedure_IDs(all_tokens, loc)) {
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

// R28. <Primary> -> <Identifier> | <Integer> | <Identifier>  (<IDs>) |
// (<Expression>) | <Real> | true | false
//---------------------------------------------------------------------------------------------------
bool procedure_Primary(vector<token_323> &all_tokens, int &loc) {
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
      if (procedure_IDs(all_tokens, loc)) //<IDs>
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
    if (procedure_Expression(all_tokens, loc)) //<Expression>
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

// R27. <Factor> -> -<Primary> | <Primary>
//---------------------------------------------------------------------------------------------------
bool procedure_Factor(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "-") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (procedure_Primary(all_tokens, loc)) {

      std::string output_str = "<Factor> -> -<Primary> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else {
      throw std::logic_error("error, expecting <Primary>");
    }
  } else if (procedure_Primary(all_tokens, loc)) {

    std::string output_str = "<Factor> -> <Primary> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R26.1 <Term'> -> * <Factor> <Term>' | / <Factor> <Term>' | ϵ
//---------------------------------------------------------------------------------------------------
bool procedure_Term_q(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "*") //* <Factor> <Term>'
  {

    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (procedure_Factor(all_tokens, loc)) {
      // instruction *
      instruction_table temp_ins;
      temp_ins.new_instruction("MUL", "nil");
      all_tokens[0].all_instructions.push_back(temp_ins);

      if (procedure_Term_q(all_tokens, loc)) {
        std::string output_str = "<Term'> -> * <Factor> <Term>' \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting <Term>'");
      }
    } else {
      throw std::logic_error("error, expecting <Factor>");
    }
  } else if (token_holder.lexeme() == "/") //* <Factor> <Term>'
  {

    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (procedure_Factor(all_tokens, loc)) {
      // instruction  /
      instruction_table temp_ins;
      temp_ins.new_instruction("DIV", "nil");
      all_tokens[0].all_instructions.push_back(temp_ins);

      if (procedure_Term_q(all_tokens, loc)) {
        std::string output_str = "<Term'> -> / <Factor> <Term>' \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting <Term>'");
      }
    } else {
      throw std::logic_error("error, expecting <Factor>");
    }
  } else // ϵ
  {
    std::string output_str = "<Term'>  -> ϵ \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  }
  return return_holder;
}

// R26. <Term>    -> <Factor> <Term>'
//---------------------------------------------------------------------------------------------------
bool procedure_Term(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Factor(all_tokens, loc)) {
    if (procedure_Term_q(all_tokens, loc)) {

      std::string output_str = "<Term> -> <Factor> <Term>' \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else {
      throw std::logic_error("error, expecting <Term>'");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R25. <Expression>  -> <Term> <Expression'>
//---------------------------------------------------------------------------------------------------
bool procedure_Expression(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Term(all_tokens, loc)) {
    if (procedure_Expression_q(all_tokens, loc)) {

      std::string output_str = "<Expression>  -> <Term> <Expression'> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else {
      throw std::logic_error("error, expecting <Expression'>");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R25.1 <Expression'>  -> ϵ | +<Term> <Expression'>  | -<Term> <Expression'>
//---------------------------------------------------------------------------------------------------
bool procedure_Expression_q(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "+") //+ <Term> <Expression'>
  {

    // token_holder.token_print_helper();
    loc++;
    if (procedure_Term(all_tokens, loc)) {
      // instruction +
      instruction_table temp_ins;
      temp_ins.new_instruction("ADD", "nil");
      all_tokens[0].all_instructions.push_back(temp_ins);

      if (procedure_Expression_q(all_tokens, loc)) {

        std::string output_str = "<Expression'>  -> + <Term> <Expression'> \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting <Expression'>");
      }
    } else {
      throw std::logic_error("error, expecting <Term>");
    }
  } else if (token_holder.lexeme() == "-") //-<Term> < Expression'>
  {
    // token_holder.token_print_helper();
    loc++;
    if (procedure_Term(all_tokens, loc)) {
      // instruction -
      instruction_table temp_ins;
      temp_ins.new_instruction("SUB", "nil");
      all_tokens[0].all_instructions.push_back(temp_ins);

      if (procedure_Expression_q(all_tokens, loc)) {

        std::string output_str = "<Expression'>  -> - <Term> <Expression'> \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting <Expression'>");
      }
    } else {
      throw std::logic_error("error, expecting <Term>");
    }
  } else {

    std::string output_str = "<Expression'>  -> ϵ \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  }
  return return_holder;
}

// R24. <Relop> -> ==   |   !=    | > | <    |  <=   | = >
//---------------------------------------------------------------------------------------------------
bool procedure_Relop(vector<token_323> &all_tokens, int &loc) {
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

// R23. <Condition> -> <Expression>  <Relop>   <Expression>
//---------------------------------------------------------------------------------------------------
bool procedure_Condition(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Expression(all_tokens, loc)) {
    if (procedure_Relop(all_tokens, loc)) {
      if (procedure_Expression(all_tokens, loc)) {

        std::string output_str =
            "<Condition> -> <Expression> <Relop> <Expression> \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting <Expression>");
      }
    } else {
      throw std::logic_error("error, expecting <Relop>");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R22. <While> -> while (<Condition>) < Statement >
//---------------------------------------------------------------------------------------------------
bool procedure_While(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "while") {
    // label
    instruction_table temp_ins;
    temp_ins.new_instruction("LABEL", "nil");
    all_tokens[0].all_instructions.push_back(temp_ins);

    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "(") {
      // token_holder.token_print_helper();
      loc++;
      token_holder = all_tokens[loc];
      if (procedure_Condition(all_tokens, loc)) {
        token_holder = all_tokens[loc];
        if (token_holder.lexeme() == ")") {
          // jump after cmp
          instruction_table temp_ins;
          temp_ins.new_instruction("JUMPZ", "next jump");
          all_tokens[0].all_instructions.push_back(temp_ins);

          // token_holder.token_print_helper();
          loc++;
          if (procedure_Statement(all_tokens, loc)) {
            // jmp
            instruction_table temp_ins;
            temp_ins.new_instruction("JUMP", "last label");
            all_tokens[0].all_instructions.push_back(temp_ins);

            std::string output_str =
                "<While> -> while (<Condition>) < Statement > \n";
            all_tokens[loc_helper].rule_holder.push_back(output_str);
            // std::cerr << output_str;

            return_holder = true;
          } else {
            throw std::logic_error("error, expecting < Statement >");
          }
        } else {
          throw std::logic_error("error, expecting )");
        }
      } else {
        throw std::logic_error("error, expecting <Condition>");
      }
    } else {
      throw std::logic_error("error, expecting (");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R21. <Scan> -> get( <IDs> );
//---------------------------------------------------------------------------------------------------
bool procedure_Scan(vector<token_323> &all_tokens, int &loc) {
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
      if (procedure_IDs(all_tokens, loc)) {
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

// R20. <Print> -> put(<Expression>);
//---------------------------------------------------------------------------------------------------
bool procedure_Print(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "put") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "(") {
      // token_holder.token_print_helper();
      loc++;

      token_holder = all_tokens[loc];
      if (procedure_Expression(all_tokens, loc)) {
        token_holder = all_tokens[loc];
        if (token_holder.lexeme() == ")") {

          // token_holder.token_print_helper();
          loc++;

          instruction_table temp_ins;
          temp_ins.new_instruction("STDOUT", "nil");
          all_tokens[0].all_instructions.push_back(temp_ins);

          token_holder = all_tokens[loc];
          if (token_holder.lexeme() == ";") {
            // token_holder.token_print_helper();
            loc++;

            std::string output_str = "<Print> -> put(<Expression>); \n";
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
        throw std::logic_error("error, expecting <Expression>");
      }
    } else {
      throw std::logic_error("error, expecting (");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R19. <Return> -> return; | return <Expression>;
//---------------------------------------------------------------------------------------------------
bool procedure_Return(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "return") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == ";") {
      // token_holder.token_print_helper();
      loc++;

      std::string output_str = "<Return> -> return; \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else if (procedure_Expression(all_tokens, loc)) {
      token_holder = all_tokens[loc];
      if (token_holder.lexeme() == ";") {
        // token_holder.token_print_helper();
        loc++;

        std::string output_str = "<Return> -> return <Expression>; \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting ;");
      }
    } else {
      throw std::logic_error("error, expecting ; or <Expression>");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

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

// R17. <Assign> -> <Identifier> = <Expression>;
//---------------------------------------------------------------------------------------------------
bool procedure_Assign(vector<token_323> &all_tokens, int &loc) {
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
  if (identifier_helper(token_holder)) {
    // id saved
    string temp_token = token_holder.lexeme();

    // token_holder.token_print_helper();
    loc++;

    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "=") {
      // token_holder.token_print_helper();
      loc++;
      if (procedure_Expression(all_tokens, loc)) {
        token_holder = all_tokens[loc];
        // add popm instruction
        instruction_table temp_ins;
        temp_ins.new_instruction("POPM", temp_token);
        all_tokens[0].all_instructions.push_back(temp_ins);

        if (token_holder.lexeme() == ";") {
          // token_holder.token_print_helper();
          loc++;

          std::string output_str = "<Identifier> = <Expression>; \n";
          all_tokens[loc_helper].rule_holder.push_back(output_str);
          // std::cerr << output_str;

          return_holder = true;
        } else {
          throw std::logic_error("error, expecting ;");
        }

      } else {
        throw std::logic_error("error, expecting <Expression>");
      }
    } else {

      throw std::logic_error("error, expecting =");
      std::cerr << token_holder.lexeme() << "\n";
      token_holder = all_tokens[loc + 1];
      std::cerr << token_holder.lexeme() << "\n";
      token_holder = all_tokens[loc - 1];
      std::cerr << token_holder.lexeme() << "\n";
      return_holder = false;
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R16. <Compound> -> { <Statement List> }
//---------------------------------------------------------------------------------------------------
bool procedure_Compound(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "{") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (procedure_Statement_List(all_tokens, loc)) {
      token_holder = all_tokens[loc];
      if (token_holder.lexeme() == "}") {
        // token_holder.token_print_helper();
        loc++;

        std::string output_str = "<Compound> -> { < Statement List> } \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting }");
      }
    } else {
      throw std::logic_error("error, expecting < Statement List>");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R15. <Statement> -> <Compound> | <Assign> | <If> | <Return> | <Print> |
// <Scan> | <While>
//---------------------------------------------------------------------------------------------------
bool procedure_Statement(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Compound(all_tokens, loc)) //<Compound>
  {

    std::string output_str = "<Statement> -> <Compound> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedure_Assign(all_tokens, loc)) // <Assign>
  {

    std::string output_str = "<Statement> -> <Assign> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedure_If(all_tokens, loc)) // <If>
  {

    std::string output_str = "<Statement> -> <If>  \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedure_Return(all_tokens, loc)) // <Return>
  {

    std::string output_str = "<Statement> -> <Return> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedure_Print(all_tokens, loc)) //<Print>
  {

    std::string output_str = "<Statement> -> <Print> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedure_Scan(all_tokens, loc)) // <Scan>
  {

    std::string output_str = "<Statement> -> <Scan> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else if (procedure_While(all_tokens, loc)) //<While>
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

// R14. <Statement List> -> <Statement> | <Statement> <Statement List>
//---------------------------------------------------------------------------------------------------
bool procedure_Statement_List(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Statement(all_tokens, loc)) {
    token_holder = all_tokens[loc];
    if (procedure_Statement_List(all_tokens, loc)) {

      std::string output_str =
          "<Statement List> -> <Statement> <Statement List>\n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else {
      std::string output_str = "<Statement List> -> <Statement> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R12. <Declaration> -> <Qualifier > <IDs>
//---------------------------------------------------------------------------------------------------
bool procedure_Declaration(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Qualifier(all_tokens, loc)) {
    token_holder = all_tokens[loc];
    if (procedure_IDs(all_tokens, loc)) {

      std::string output_str = "<Declaration> -> <Qualifier > <IDs> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else {
      throw std::logic_error("error, expecting <IDs>");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R11. <Declaration List>  : = <Declaration>; | <Declaration>; <Declaration
// List>
//---------------------------------------------------------------------------------------------------
bool procedure_Declaration_List(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Declaration(all_tokens, loc)) {
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == ";") {
      // token_holder.token_print_helper();
      loc++;
      token_holder = all_tokens[loc];
      if (procedure_Declaration_List(all_tokens, loc)) {

        std::string output_str =
            "<Declaration List> -> <Declaration>; <Declaration List> \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {

        std::string output_str = "<Declaration List> -> <Declaration>; \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      }
    } else {
      throw std::logic_error("error, expecting ;");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R10. <Opt Declaration List> -> <Declaration List> | <Empty>
//---------------------------------------------------------------------------------------------------
bool procedure_Opt_Declaration_List(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Declaration_List(all_tokens, loc)) {

    std::string output_str = "<Opt Declaration List> -> <Declaration List> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else {
    std::string output_str = "<Opt Declaration List> -> <Empty> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  }
  return return_holder;
}

// R9. <Body>  -> { < Statement List> }
//---------------------------------------------------------------------------------------------------
bool procedure_Body(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "{") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (procedure_Statement_List(all_tokens, loc)) {
      token_holder = all_tokens[loc];
      if (token_holder.lexeme() == "}") {
        // token_holder.token_print_helper();
        loc++;

        std::string output_str = "<Body> -> { < Statement List> } \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting }");
      }
    } else {
      throw std::logic_error("error, expecting < Statement List>");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

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

// R7. <Parameter> -> <IDs >  <Qualifier>
//---------------------------------------------------------------------------------------------------
bool procedure_Parameter(vector<token_323> &all_tokens,
                         int &loc) // procedure for <Parameter>
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
  if (procedure_IDs(all_tokens, loc)) {
    if (procedure_Qualifier(all_tokens, loc)) {

      std::string output_str = "<Parameter> -> <IDs> <Qualifier> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else {
      throw std::logic_error("error, expecting <Qualifier>");
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R6. <Parameter List>  -> <Parameter> | <Parameter>, <Parameter List>
//---------------------------------------------------------------------------------------------------
bool procedure_Parameter_List(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Parameter(all_tokens, loc)) {
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == ",") {
      // token_holder.token_print_helper();
      loc++;
      if (procedure_Parameter_List(all_tokens, loc)) {

        std::string output_str =
            "<Parameter List> -> <Parameter>, <Parameter List> \n";
        all_tokens[loc_helper].rule_holder.push_back(output_str);
        // std::cerr << output_str;

        return_holder = true;
      } else {
        throw std::logic_error("error, expecting <Parameter List>");
      }
    } else {
      std::string output_str = "<Parameter List> -> <Parameter> \n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    }
  } else {
    return_holder = false;
  }
  return return_holder;
}

// R5. <Opt Parameter List> -> <Parameter List> | <Empty>
//---------------------------------------------------------------------------------------------------
bool procedure_Opt_Parameter_List(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Parameter_List(all_tokens, loc)) {
    std::string output_str = "<Opt Parameter List> -> <Parameter List> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  } else {
    std::string output_str = "<Opt Parameter List> -> <Empty> \n";
    all_tokens[loc_helper].rule_holder.push_back(output_str);
    // std::cerr << output_str;

    return_holder = true;
  }
  return return_holder;
}

// R4. <Function> -> function  <Identifier>  (  <Opt Parameter List>  )   < Opt
// Declaration List >   <Body>
//---------------------------------------------------------------------------------------------------
// tbf
bool procedure_Function(vector<token_323> &all_tokens, int &loc) {
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
  if (token_holder.lexeme() == "function") {
    // token_holder.token_print_helper();
    loc++;
    token_holder = all_tokens[loc];
    if (identifier_helper(token_holder)) {
      // token_holder.token_print_helper();
      loc++;
      token_holder = all_tokens[loc];
      if (token_holder.lexeme() == "(") {
        // token_holder.token_print_helper();
        loc++;
        token_holder = all_tokens[loc];
        if (procedure_Opt_Parameter_List(all_tokens, loc)) {
          token_holder = all_tokens[loc];
          if (token_holder.lexeme() == ")") {
            // token_holder.token_print_helper();
            loc++;
            token_holder = all_tokens[loc];
            if (procedure_Opt_Declaration_List(all_tokens, loc)) {
              token_holder = all_tokens[loc];
              if (procedure_Body(all_tokens, loc)) {

                std::string output_str =
                    "<Function> -> function <Identifier> ( <Opt Parameter "
                    "List> ) < Opt Declaration List > <Body> \n";
                all_tokens[loc_helper].rule_holder.push_back(output_str);
                // std::cerr << output_str;

                return_holder = true;
              } else {
                throw std::logic_error("error, expecting <Body>");
              }
            } else {
              throw std::logic_error(
                  "error, expecting < Opt Declaration List >");
              return_holder = false;
            }
          } else {
            throw std::logic_error("error, expecting )");
          }
        } else {
          throw std::logic_error("error, expecting <Opt Parameter List>");
        }
      } else {
        throw std::logic_error("error, expecting (");
      }
    } else {
      throw std::logic_error("error, expecting <Identifier>");
    }
  } else {
    return_holder = false;
  }

  if (return_holder == true) {
    throw std::logic_error(
        "Error, Function is not supported by simplified Rat20F");
    return_holder = false;
  }
  return return_holder;
}

// R3. <Function Definitions>  -> <Function> | <Function> <Function Definitions>
//---------------------------------------------------------------------------------------------------
bool procedure_Function_Definitions(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Function(all_tokens, loc)) // if <function>?
  {
    if (procedure_Function_Definitions(all_tokens, loc)) {

      std::string output_str =
          "<Function Definitions> -> <Function Definitions>\n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    } else {

      std::string output_str = "<Function Definitions> -> <Function>\n";
      all_tokens[loc_helper].rule_holder.push_back(output_str);
      // std::cerr << output_str;

      return_holder = true;
    }
  } else // not this rule
  {
    return_holder = false;
  }

  return return_holder;
}

// R2. <Opt Function Definitions> -> <Function Definitions> | <Empty>
//---------------------------------------------------------------------------------------------------
bool procedure_Opt_Function_Definitions(vector<token_323> &all_tokens,
                                        int &loc) {
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
  if (procedure_Function_Definitions(all_tokens, loc)) {

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

// R1. <Rat20F>  -> <Opt Function Definitions>   $$  <Opt Declaration List>
// <Statement List>  $$
//---------------------------------------------------------------------------------------------------
bool procedure_Rat20F(vector<token_323> &all_tokens, int &loc) {
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
  if (procedure_Opt_Function_Definitions(all_tokens, loc)) {
    // throw std::logic_error("" << "test seg 1" << "");
    token_holder = all_tokens[loc];
    if (token_holder.lexeme() == "$$") {
      // throw std::logic_error("" << "$$" << "");
      // throw std::logic_error("" << "test seg 2" << "");
      // token_holder.token_print_helper();
      loc++;
      if (procedure_Opt_Declaration_List(all_tokens, loc)) {
        // throw std::logic_error("" << "test seg 3" << "");
        // std::cerr << "\n" << all_tokens[loc].lexeme() << all_tokens[loc -
        // 1].lexeme() << "\n" << all_tokens[loc + 1].lexeme() << "\n" <<
        // "\n\n";
        if (procedure_Statement_List(all_tokens, loc)) {
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
              procedure_Rat20F(all_tokens, loc);
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
