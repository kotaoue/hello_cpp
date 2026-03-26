# unittest

A simple unit test sample using [Unity](https://github.com/ThrowTheSwitch/Unity).

## Structure

```
unittest/
├── Makefile              # Build and run tests
├── test_calculator.c     # Test cases
├── src/
│   ├── calculator.h      # Header for the module under test
│   └── calculator.c      # Implementation (add, subtract, multiply)
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
test_calculator.c:51:test_add_positive_numbers:PASS
test_calculator.c:52:test_add_negative_numbers:PASS
test_calculator.c:53:test_add_zero:PASS
test_calculator.c:54:test_subtract:PASS
test_calculator.c:55:test_subtract_negative_result:PASS
test_calculator.c:56:test_multiply:PASS
test_calculator.c:57:test_multiply_by_zero:PASS

-----------------------
7 Tests 0 Failures 0 Ignored
OK
```
