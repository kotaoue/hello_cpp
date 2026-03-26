CC      = gcc
CFLAGS  = -Wall -Wextra -I. -Isrc -Iunity

UNITY_SRC = unity/unity.c
SRC       = src/calculator.c
TEST_SRC  = test_calculator.c

TARGET = test_runner

.PHONY: all test clean

all: test

$(TARGET): $(TEST_SRC) $(SRC) $(UNITY_SRC)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
