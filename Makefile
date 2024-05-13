FLAGS= -Wall -g
LIBRARIES= -lcriterion
INCLUDES= -I./
OBJECTS= ./build/logging/hello.o
TESTS= containers/buffer_test.c containers/buffer.c
TARGETS= ./build/targets

build: $(OBJECTS)
	@ cc main.c $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(TARGETS)/main

test: $(TESTS)
	@ cc $(TESTS) $(FLAGS) $(INCLUDES) $(LIBRARIES) -o $(TARGETS)/test
	@ $(TARGETS)/test --fail-fast

run: build
	@ $(TARGETS)/main

clean:
	@ rm $(TARGETS)/main
	@ rm -rf $(OBJECTS)
	@ echo --cleaned--

./build/logging/hello.o: ./logging/hello.c
	@cc ./logging/hello.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/logging/hello.o
