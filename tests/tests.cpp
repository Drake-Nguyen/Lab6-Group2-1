#include "../include/acutest.h"

#include "./test_condition.hpp"
#include "./test_id.hpp"
#include "./test_qualifier.hpp"
#include "./test_relop.hpp"
#include "./test_assign.hpp"

TEST_LIST = {
    {"relop", test_relop},
    {"condition", test_condition},
    {"id", test_id},
    {"qualifier", test_qualifier},
    {"assign", test_assign},
    {},
};
