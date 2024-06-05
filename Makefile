FLAGS= -Wall -g
LIBRARIES= -lcriterion -lutil
INCLUDES= -I./
OBJECTS= ./build/logging/hello.o ./build/containers/buffer.o
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

./build/containers/buffer.o: ./containers/buffer.c
	@ cc ./containers/buffer.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/containers/buffer.o

./build/logging/hello.o: ./logging/hello.c
	@cc ./logging/hello.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/logging/hello.o
