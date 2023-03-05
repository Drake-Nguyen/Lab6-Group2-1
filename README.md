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

After that, `make test` should run the test.

Several functions are provided to assert test conditions:

- `TEST_CHECK(true)` - Asserts that the condition is true
- `TEST_EQUAL(1, 1)` - Asserts that the two values are equal

For more information, refer to [acutest](https://github.com/mity/acutest).

## Cleaning

To clean the project, run the following command

```bash
make clean
```
