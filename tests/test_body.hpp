#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

#include <map>
#include <sstream>

static void test_body(void){
    test(procedure_Body, "{",{{"Separators","{"}}, CURRENT_LOCATION );
    test(procedure_Body, "}",{{"Separators","}"}}, CURRENT_LOCATION );
    test(procedure_Body, "void main() {int x = 0; }" , {}, CURRENT_LOCATION);
    test(procedure_Body, "void addNum(){ return(a+b); }", {} , CURRENT_LOCATION);
}