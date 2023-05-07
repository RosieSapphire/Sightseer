CC=cc
CFLAGS=-Wall -Wextra -Og -g3
INC=-Iinclude -Ideps/rmath/include
LIB=-lm -Ldeps/rmath -lrmath
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, %.o, $(SRC))
TEST=camera_test
LIB_OUT=libsightseer.a

lib: $(LIB_OUT)
test: $(TEST)
default: lib

$(TEST): $(LIB_OUT)
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LIB) -L. -lsightseer
	rm -f *.o
	@echo Success!

$(LIB_OUT): $(OBJ)
	make -C deps/rmath/
	ar rcs $@ $^
	rm -rf *.o

%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ $(INC)

clean:
	@rm -f $(BIN) $(OBJ) $(TEST) $(LIB_OUT)
	@echo Cleaned up build files.
