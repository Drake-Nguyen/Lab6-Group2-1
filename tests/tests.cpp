#include "../include/acutest.h"

#include "./test_condition.hpp"
#include "./test_id.hpp"
#include "./test_qualifier.hpp"
#include "./test_relop.hpp"
#include "./test_assign.hpp"
#include "./test_primary.hpp"
#include "./test_expression.hpp"
#include "./test_parameter.hpp"
#include "./test_term.hpp"
#include "./test_return.hpp"

TEST_LIST = {
    {"relop", test_relop},
    {"condition", test_condition},
    {"id", test_id},
    {"qualifier", test_qualifier},
    {"assign", test_assign},
    {"primary", test_primary},
    {"expression", test_expression},
    {"parameters", test_parameter},
    {"term", test_term},
    {"return", test_return},
    {},
};
