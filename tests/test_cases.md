# Test Cases

## Primary

For Primary, the empty string '' and " " tests are expected to fail based on the grammar rule. However, there was one case that was not expected to fail. The test case "1.0E-5" is used to test real numbers. The lexer read the token size as 3 instead of 1. The token was read as "1.0", "E" and "-5". Overall, the primary test cases are working as intended, with the exception of real numbers that involve characters.

## Term

For Term, the program fails when the testing `3z/4`. It seems that the Lexer is recognizing 3z as an ivalid token rahter than a term itself. It seems the it needs to be separated with a `*` to be recognized as a term. 

`3zz z / 4` failed as beacause `3zz` is not considered a term rather an invalid token.

## Return
The test cases for the return statement have failed. The first test case "return" expects an expression or `;` after the keyword, but since there is none, it expectably failed. In the second test case `return x > 0;`, the parser fails to recognize it as a valid return statement due to a syntax error near the operator ">" and expects a semicolon instead, there is probably something wrong with the procedure_condition function. Finally, the third test case `return x+1, y*2, z;` also encounters a syntax error due to the unexpected comma separator, which causes the parser to expect a semicolon instead.

## Relop

For Relop, there's not many notable cases.

The two cases that stood out are `!=` and `>=`:

- `!=` got lexed to have an "Other Separators" token in front of it, which is
  unexpected. I'm not sure why this happens.
- `>=` got lexed to be two tokens instead of one: `>` and `=`. This is also
  unexpected. This does not happen for `<=` or `==`.

Both of these cases are evaluated by the procedure function just fine, implying
that they might be expected behavior.

## Condition

Some of Condition's test cases failed:

- `true != false` wasn't lexed properly: a whitespace was inserted between
  `true` and `!=` for some reason. This evaluates correctly, however.
- `123 < 345` wasn't lexed properly: the lexer considered `123` and `345` to be
  keyword tokens and not numbers. This appears to evaluate correctly.
	- This is the same for `456 > 123`.

Conditions with `>=` and `<=` were not included in the tests, because they would
yield similar results to Relop's `>=` and `<=` test cases.

## If

For If, I split all test inputs into two categories: ones that don't have
`else`, and ones that do. Within each of these categories, I tested all
combinations of `<Statement>` tokens within an `<If>` token. I also tested
nested `<If>`s.

This is the first test suite that actually passes all of its tests! 🎉

## Identifier

These test cases would be enough as it includes the potential inputs that could be applied
to the Identifier token. It went through the possible names whether it be a single character
or even a whole string like the word apple to make sure it would be able to run properly. 
There were still some failed cases that were expected however:

- `class` as an input failed due to it being a reserved word for C++ so it cannot be used

- `empty` or an empty input would also fail due to it not being able to be used as 
  the function would not be able to lex properly.
  
- `whitespace` or just a space input would not lex properly for a similar reason to `empty`

A possible example for the situation regarding the empty and whitespaceis identifying 
a class but the class wouldn't have a space between two words in its name and leaving 
behind an error. This can also be the case when the user cannot name their potential 
function with an empty input.

## Qualifiers

For Qualifiers, the inputs `int`, `boolean`, and `real` lexed properly through the tests. Outside of
these three tests, there were issues outside of that with: 

-`static` should be able to successfully lex as a qualifier but most likely failed due to not being
included inside of the possible inputs inside the original procedure.

-`char` would be in a similar situation as static in this case on why it failed to lex properly.

## Expression
Uncertian of the failure of the test cases. Although the test cases were a failure,
there was a single test case that passed alone, but did not show if combined with other
test cases.

For the tests cases, it should have been lexed properly as there was no expected fail test
cases.

## Parameter
Similar to Expression test cases. Uncertain of failure clause with no expected failure test
cases. Test cases should have been lexed properly. No successful test case unlike Expression.

## Parameter List

For the parameter list, all tests were returned with an error expecting the `<Qualifier>` when
all statements should be correct. The error could be due to my own input using `a()` to create
the parameter list with inputs as arguments or that parameter list input clashing with something
inside the procedure_Parameter_List.

## While
For While, test cases were valid when all required categories were inputted.
As long as they were in the correct order the then they were accepted, even when
there are multiple `<Statement>`s involved. Also tested nested while loops, if
statements, and other `<Statement>` categories which works as long as there as
all the previous categories are accepted.

## Statement
Testing all cases for statement (compound, assign, if, return, print, scan, while).
As long as test cases fall within the categories for each statement cases will
be passed.

## Assign
The first test case is testing a valid assignment statement, where the variable "a" is assigned the value of 123. This is a basic test case to ensure that the procedure_Assign function is working as expected when given valid input. The next five test cases are testing various scenarios that would result in an invalid assignment statement. 

## Declaration
The first three test cases are testing valid variable declarations in C++. The first test case is declaring an integer variable "x". The second test case is declaring three floating-point variables "x", "y", and "z". The third test case is declaring two character variables "c" and "d". These test cases ensure that the procedure_Declaration function is working as expected when given valid input.

## Print
For this procedure the valid tests have proper notation for printing. using "put();". The first test case checks for the proper printing of one variable. The second function checks for the correct way to print two variables. The third function checks for the right printing of an expression. The fail test checks for correct notation.

## Scan
The scan procedure checks for the proper notation for scanning for variables. The proper function used it "get();". Similiar to the print procedure the the test functions in scan check the right notatoin for the get functions. The fail tests check for proper notation.

## Compound
This procedure checks for the right notation for having a compound of statements inside "{}". The first test checks a compound that initializes a and b, conatins an if else statement that return true and false. The second test checks for a compound that contains a while loop with a condition, a get function, and a put function. The third procedure has an if statement with a condition that returns a bool. The fail tests check for correct notation.