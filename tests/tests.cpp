#include "../include/acutest.h"

#include "./test_condition.hpp"
#include "./test_qualifier.hpp"
#include "./test_relop.hpp"

TEST_LIST = {
    {"qualifier_boolean", test_qualifier_boolean},
    {"qualifier_int", test_qualifier_int},
    {"relop", test_relop},
    {"condition", test_condition},
    {},
};
