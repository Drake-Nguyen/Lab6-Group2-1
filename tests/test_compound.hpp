#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_compound(void) {
test(procedureCompound, "{int a=1;int b=1;if(a==b){return true;}else{return false;}", 
{{"Compound Seperator","{"},{"Declaration", "int"},{"Another Seperator", " "}, 
{"Identifier", "a"},{"Operator", "="}, {"Integer", "1"}, {"Seperator", ";"}, 
{"Declaration", "int"}, {"Another Seperator", " "}, {"Identifier", "b"},
{"Operator", "="}, {"Integer", "1"}, {"Seperator", ";"}, {"Statement", "if"},
{"Seperator", "("}, {"Identifier", "a"}, {"Operator", "=="}, {"Identifier", "b"},
 {"Seperator", ")"}, {"Seperator", "{"},{"Keyword", "return"},{"Seperator", " "}, 
{"Bool", "true"}, {"Seperator", "}"}, {"Statement", "else"},{"Seperator", "{"}, 
{"Keyword", "return"}, {"Seperator", " "}, {"Bool", "true"}, {"Seperator", ";"},
{"Seperator", "}"}}, CURRENT_LOCATION);
test(procedureCompound, "{while(a!=b){get(a);put(b);}", {{"Seperator", "{"}, 
{"Statement", "while"}, {"Seperator", "("}, {"Identifier", "a"},{"Operator", "!="}, 
{"Identifier", "b"}, {"Seperator", ")"}, {"Seperator", "{"}, {"Function", "get"},
{"Seperator", "("}, {"Identifier", "a"},{"Seperator", ")"},{"Seperator", ";"},
{"Function", "put"},{"Seperator", "("}, {"Identifier", "b"},{"Seperator", ")"}, 
{"Seperator", ";"}, {"Seperator", ";"} }, CURRENT_LOCATION);
test(procedureCompound, "{if(a<b){a=a+1;return true;}", {{"Statemment", "if"},
{"Seperator", "("}, {"Identifier", "a"}, {"Operator", "<"}, {"Identifier", "b"},
{"Seperator", ")"}, {"Seperator", "{"}, {"Identifier", "a"}, {"Operator", "="}, 
{"Identifier", "a"}, {"Operator", "+"},{"Integer", "1"},{"Seperator", ";"},
{"Keyword", "return"}, {"Seperator", " "}, {"Bool", "true"},{"Seperator", ";"},
{"Seperator", "}"}}, CURRENT_LOCATION);


test_fail(procedureCompound, "{if(a==3) return true;", {}, CURRENT_LOCATION);
test_fail(procedureCompound, "{int a=1 int b=2; while(a<b)return true}", {}, CURRENT_LOCATION);
test_fail(procedureCompound, "if(a==3) return true;}", {}, CURRENT_LOCATION);

}