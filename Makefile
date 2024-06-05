FLAGS= -Wall -g
LIBRARIES= -lcriterion -lutil
INCLUDES= -I./

OBJECTS= \
				 ./build/containers/buffer.o \
				 ./build/ttf_loader/ttf_loader.o \
				 ./build/ttf_loader/tables/font_directory.o \
				 ./build/ttf_loader/tables/os2.o \
				 ./build/ttf_loader/tables/font_table.o \

TESTS= \
			 src/containers/buffer_test.c \
			 src/containers/buffer.c \

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

./build/containers/buffer.o: ./src/containers/buffer.c
	@ cc ./src/containers/buffer.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/containers/buffer.o

./build/ttf_loader/ttf_loader.o: ./src/ttf_loader/ttf_loader.c
	@ cc ./src/ttf_loader/ttf_loader.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/ttf_loader.o

./build/ttf_loader/tables/font_directory.o: ./src/ttf_loader/tables/font_directory.c
	@ cc ./src/ttf_loader/tables/font_directory.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/font_directory.o

./build/ttf_loader/tables/os2.o: ./src/ttf_loader/tables/os2.c
	@ cc ./src/ttf_loader/tables/os2.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/os2.o

./build/ttf_loader/tables/font_table.o: ./src/ttf_loader/tables/font_table.c
	@ cc ./src/ttf_loader/tables/font_table.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/font_table.o
