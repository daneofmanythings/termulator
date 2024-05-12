FLAGS= -Wall -g
LIBRARIES= 
INCLUDES= -I./
OBJECTS= ./build/logging/hello.o
TARGETS= ./build/targets

build: $(OBJECTS)
	@ cc main.c $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(TARGETS)/main

run: build
	@ $(TARGETS)/main

clean:
	@ rm $(TARGETS)/main
	@ rm -rf $(OBJECTS)
	@ echo --cleaned--

./build/logging/hello.o: ./logging/hello.c
	@cc ./logging/hello.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/logging/hello.o
