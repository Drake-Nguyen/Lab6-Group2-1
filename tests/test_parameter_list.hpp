#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_parameter_list(void) {

  procedureParameterList paramlist;

  test(
      [&paramlist](std::vector<token_323> &tokens, int &index) {
        return paramlist.procedure_Parameter_List(tokens, index);
      },
      "a()", {{"Identifier", "a"}, {"Separator", "("}, {"Separator", ")"}},
      CURRENT_LOCATION);
  test(
      [&paramlist](std::vector<token_323> &tokens, int &index) {
        return paramlist.procedure_Parameter_List(tokens, index);
      },
      "a(1001)",
      {{"Identifier", "a"},
       {"Separator", "("},
       {"Integer", "1001"},
       {"Separator", ")"}},
      CURRENT_LOCATION);
  test(
      [&paramlist](std::vector<token_323> &tokens, int &index) {
        return paramlist.procedure_Parameter_List(tokens, index);
      },
      "a(boo)",
      {{"Identifier", "a"},
       {"Separator", "("},
       {"Identifier", "boo"},
       {"Separator", ")"}},
      CURRENT_LOCATION);
  test(
      [&paramlist](std::vector<token_323> &tokens, int &index) {
        return paramlist.procedure_Parameter_List(tokens, index);
      },
      "a($)",
      {{"Identifier", "a"},
       {"Separator", "("},
       {"Other Separators", "$"},
       {"Separator", ")"}},
      CURRENT_LOCATION);
  test(
      [&paramlist](std::vector<token_323> &tokens, int &index) {
        return paramlist.procedure_Parameter_List(tokens, index);
      },
      "a(int,char)",
      {{"Identifier", "a"},
       {"Separator", "("},
       {"Keyword", "int"},
       {"Separator", ","},
       {"Keyword", "char"},
       {"Separator", ")"}},
      CURRENT_LOCATION);
  test(
      [&paramlist](std::vector<token_323> &tokens, int &index) {
        return paramlist.procedure_Parameter_List(tokens, index);
      },
      "a(204,string)",
      {{"Identifier", "a"},
       {"Separator", "("},
       {"Integer", "204"},
       {"Separator", ","},
       {"Identifier", "string"},
       {"Separator", ")"}},
      CURRENT_LOCATION);

  // test (procedure_Parameter_List, "x,", {{"Identifier", "x"}},
  // CURRENT_LOCATION);
  test(
      [&paramlist](std::vector<token_323> &tokens, int &index) {
        return paramlist.procedure_Parameter_List(tokens, index);
      },
      "int x,int y",
      {{"Keyword", "int"},
       {"Other Separators", " "},
       {"Identifier", "x"},
       {"Separator", ","},
       {"Keyword", "int"},
       {"Other Separators", " "},
       {"Identifier", "y"}},
      CURRENT_LOCATION);
  test(
      [&paramlist](std::vector<token_323> &tokens, int &index) {
        return paramlist.procedure_Parameter_List(tokens, index);
      },
      "boolean x,real y",
      {{"Keyword", "boolean"},
       {"Other Separators", " "},
       {"Identifier", "x"},
       {"Separator", ","},
       {"Keyword", "real"},
       {"Other Separators", " "},
       {"Identifier", "y"}},
      CURRENT_LOCATION);
}