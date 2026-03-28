# unit_test_using_unity

A simple unit test sample using [Unity](https://github.com/ThrowTheSwitch/Unity).

## Structure

```
unit_test_using_unity/
├── Makefile              # Build and run tests
├── src/
│   ├── calculator.h      # Header for the module under test
│   └── calculator.c      # Implementation (add, subtract, multiply)
├── test/
│   └── test_calculator.c # Test cases
└── unity/
    ├── unity.h           # Unity test framework
    ├── unity_internals.h
    └── unity.c
```

## Usage

```bash
make
```

or

```bash
make test
```

## Clean

```bash
make clean
```

## Example Output

```
test/test_calculator.c:52:test_add_positive_numbers:PASS
test/test_calculator.c:53:test_add_negative_numbers:PASS
test/test_calculator.c:54:test_add_zero:PASS
test/test_calculator.c:55:test_subtract:PASS
test/test_calculator.c:56:test_subtract_negative_result:PASS
test/test_calculator.c:57:test_multiply:PASS
test/test_calculator.c:58:test_multiply_by_zero:PASS

-----------------------
7 Tests 0 Failures 0 Ignored
OK
```
