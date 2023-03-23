#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

#include <map>
#include <sstream>

static void test_body(void){
    test(procedureBody, "{",{{"Separators","{"}}, CURRENT_LOCATION );
    test(procedureBody, "}",{{"Separators","}"}}, CURRENT_LOCATION );
    test(procedureBody, "void main() {int x = 0; }" , {}, CURRENT_LOCATION);
    test(procedureBody, "void addNum(){ return(a+b); }", {} , CURRENT_LOCATION);
}