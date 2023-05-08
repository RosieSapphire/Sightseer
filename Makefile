RMATH_DIR=deps/rmath

CC=cc
CFLAGS=-Wall -Wextra -O2
INC=-Iinclude -I$(RMATH_DIR)/include
LIB=-lm -L$(RMATH_DIR) -lrmath
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,%.o,$(SRC))
LIB_OUT=libsightseer.a
TEST=libsightseer_test

default: $(LIB_OUT)

test: $(LIB_OUT)
	$(CC) $(CFLAGS) $^ -o $(TEST) $(INC) $(LIB) -L. -l:$<
	rm -rf *.o

$(LIB_OUT): $(OBJ)
	make -C $(RMATH_DIR)
	ar rcs $@ $^
	rm -rf *.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< $(INC)

clean:
	rm -f $(LIB_OUT) $(TEST) $(OBJ)
	make clean -C $(RMATH_DIR)
