CC=cc
CFLAGS=-Wall -Wextra -O2
INC=-Iinclude -Ideps/rmath/include
LIB=-lm -Ldeps/rmath -lrmath
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,%.o,$(SRC))
LIB_OUT=libsightseer.a
TEST=libsightseer_test

RMATH_DIR=deps/rmath

default: $(LIB_OUT)

test: $(LIB_OUT)
	make -C $(RMATH_DIR)
	$(CC) $(CFLAGS) $^ -o $(TEST) $(INC) $(LIB) -L. -l:$<
	rm -rf *.o

$(LIB_OUT): $(OBJ)
	ar rcs $@ $^
	rm -rf *.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< $(INC)

clean:
	make clean -C deps/rmath
	rm -f $(LIB_OUT) $(TEST) $(OBJ)
