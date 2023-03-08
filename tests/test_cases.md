# Test Cases

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

In the case of Identifiers, the tests besides the ones that had input of whitespace or
empty input successfully lexed. Whitespace or empty inputs would return errors. A
possible example for this situation is identifying a class but the class wouldn't
have a space between two words in its name and leaving behind an error. This can also
be the case when the user cannot name their potential function with an empty input.

As for the other errors,

- `class` was not lexed properly most likely due to it being a reserved word in terms
  of C++.
- `$tring` also returned an error due to the invalid character '$'  being seen as a
  separator while assuming the Identifier was the rest of the string 'tring'.

## Qualifiers

For Qualifiers, it was a really big unsure for why the errors were appearing. This could
be due to the way the inputs were put into the procedure_Qualifier or potentially other
factors. Through an updated test, static would have been a valid input for a qualifier

In terms of the inputs of static, int, and char, those would have been lexed properly
under qualifiers to my knowledge but the tests return errors in those cases.

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
