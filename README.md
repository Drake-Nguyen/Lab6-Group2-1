# Lab5-Group2-1

## Building

TBD.

## Testing

To run the tests, run the following command

```bash
make test
```

### Adding Tests

To add tests, first make a file, e.g. `tests/test_thing.hpp`. Within this file,
define a `void test_thing(void) {}`.

Then, go to `tests/tests.cpp`, import the added `.hpp` file and add `{"thing",
test_thing}` into `TEST_LIST`. This should add the test to the test suite.

**Note**: You must keep the last empty test `{}` in `TEST_LIST`.

After that, `make test` should run the test.

A simple test can be written as:

```hpp
test(procedure_Relop, "==", {}, CURRENT_LOCATION);
```

If needed, you can also provide a `std::vector<std::string>` of expected tokens
as the third argument:

```hpp
test(procedure_Relop, "==", {{"Operator", "=="}}, CURRENT_LOCATION);
```

Refer to the existing tests for more examples.

## Cleaning

To clean the project, run the following command

```bash
make clean
```
