#include "../include/acutest.h"

#include "./test_assign.hpp"
#include "./test_condition.hpp"
#include "./test_declaration.hpp"
#include "./test_expression.hpp"
#include "./test_id.hpp"
#include "./test_if.hpp"
#include "./test_parameter.hpp"
#include "./test_parameter_list.hpp"
#include "./test_primary.hpp"
#include "./test_qualifier.hpp"
#include "./test_relop.hpp"
#include "./test_return.hpp"
#include "./test_term.hpp"
#include "./test_while.hpp"
#include "./test_print.hpp"
#include "./test_scan.hpp"
#include "./test_compound.hpp"
#include "./test_statement.hpp"


TEST_LIST = {
    {"relop", test_relop},
    {"condition", test_condition},
    {"if", test_if},
    {"id", test_id},
    {"qualifier", test_qualifier},
    {"assign", test_assign},
    {"primary", test_primary},
    {"expression", test_expression},
    {"parameters", test_parameter},
    {"term", test_term},
    {"return", test_return},
    {"declaration", test_declaration},
    {"parameter_list", test_Parameterlist},
    {"while", test_while},
    {"print", test_print},
    {"scan", test_scan},
    {"compound", test_compound},
    {},
};
