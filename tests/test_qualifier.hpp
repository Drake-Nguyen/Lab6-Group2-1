#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_qualifier (void) {

procedureQualifier qual;

test ([&qual](std::vector<token_323>& tokens, int& index) {return qual.procedure_Qualifier(tokens, index);}, "int", {{"Keyword", "int"}}, CURRENT_LOCATION);
test ([&qual](std::vector<token_323>& tokens, int& index) {return qual.procedure_Qualifier(tokens, index);}, "boolean", {{"Keyword", "boolean"}}, CURRENT_LOCATION);
test ([&qual](std::vector<token_323>& tokens, int& index) {return qual.procedure_Qualifier(tokens, index);}, "real", {{"Keyword", "real"}}, CURRENT_LOCATION);

test_fail ([&qual](std::vector<token_323>& tokens, int& index) {return qual.procedure_Qualifier(tokens, index);}, "static", {{"Keyword", "static"}}, CURRENT_LOCATION);
test_fail ([&qual](std::vector<token_323>& tokens, int& index) {return qual.procedure_Qualifier(tokens, index);}, "char", {{"Keyword", "char"}}, CURRENT_LOCATION);

}

