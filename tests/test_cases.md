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

For Condition, any cases with whitespace in between the tokens are not
evaluated correctly. For example, `a > b` is lexed properly to have whitespaces
in-between the tokens, but the procedure function does not evaluate it
correctly.

For the other test cases:

- `true!=false` wasn't lexed properly: a whitespace was inserted between `true`
  and `!=` for some reason. This evaluates correctly, however.
- `123<345` wasn't lexed properly: the lexer considered `123` and `345` to be
  keyword tokens and not numbers. This appears to evaluate correctly.
	- This is the same for `456>123`.

Conditions with `>=` and `<=` were not included in the tests, because they would
yield similar results to Relop's `>=` and `<=` test cases.
