#include "procedure_functions.h"
using namespace std;
// a helper function to help recognize identifier
bool identifierHelper(token_323 input_token) {
  if (input_token.token() == "Identifier") {
    return true;
  } else {
    return false;
  }
}