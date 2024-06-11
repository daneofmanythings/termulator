FLAGS= -Wall -g
LIBRARIES= -lcriterion -lutil -lm
INCLUDES= -I./

OBJECTS= \
				 ./build/lib/io.o \
				 ./build/containers/buffer.o \
				 ./build/ttf_loader/ttf_loader.o \
				 ./build/ttf_loader/tables/font_directory.o \
				 ./build/ttf_loader/tables/font_table.o \
				 ./build/ttf_loader/tables/cmap.o \
				 ./build/ttf_loader/tables/gasp.o \
				 ./build/ttf_loader/tables/head.o \
				 ./build/ttf_loader/tables/hhea.o \
				 ./build/ttf_loader/tables/maxp.o \
				 ./build/ttf_loader/tables/name.o \
				 ./build/ttf_loader/tables/os2.o \
				 ./build/ttf_loader/tables/post.o \

TESTS= \
			 src/containers/buffer_test.c \
			 src/containers/buffer.c \
			 src/ttf_loader/tables/font_table.c \
			 src/ttf_loader/tables/font_table_test.c \

TARGETS= ./build/targets

build: $(OBJECTS)
	@ cc main.c $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBRARIES) -o $(TARGETS)/main

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

./build/lib/io.o: ./src/lib/io.c
	@ cc ./src/lib/io.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/lib/io.o

./build/ttf_loader/ttf_loader.o: ./src/ttf_loader/ttf_loader.c
	@ cc ./src/ttf_loader/ttf_loader.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/ttf_loader.o

./build/ttf_loader/tables/font_directory.o: ./src/ttf_loader/tables/font_directory.c
	@ cc ./src/ttf_loader/tables/font_directory.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/font_directory.o

./build/ttf_loader/tables/cmap.o: ./src/ttf_loader/tables/cmap.c
	@ cc ./src/ttf_loader/tables/cmap.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/cmap.o

./build/ttf_loader/tables/gasp.o: ./src/ttf_loader/tables/gasp.c
	@ cc ./src/ttf_loader/tables/gasp.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/gasp.o

./build/ttf_loader/tables/head.o: ./src/ttf_loader/tables/head.c
	@ cc ./src/ttf_loader/tables/head.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/head.o

./build/ttf_loader/tables/hhea.o: ./src/ttf_loader/tables/hhea.c
	@ cc ./src/ttf_loader/tables/hhea.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/hhea.o

./build/ttf_loader/tables/maxp.o: ./src/ttf_loader/tables/maxp.c
	@ cc ./src/ttf_loader/tables/maxp.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/maxp.o

./build/ttf_loader/tables/name.o: ./src/ttf_loader/tables/name.c
	@ cc ./src/ttf_loader/tables/name.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/name.o

./build/ttf_loader/tables/os2.o: ./src/ttf_loader/tables/os2.c
	@ cc ./src/ttf_loader/tables/os2.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/os2.o

./build/ttf_loader/tables/post.o: ./src/ttf_loader/tables/post.c
	@ cc ./src/ttf_loader/tables/post.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/post.o

./build/ttf_loader/tables/font_table.o: ./src/ttf_loader/tables/font_table.c
	@ cc ./src/ttf_loader/tables/font_table.c $(INCLUDES) $(FLAGS) $(LIBRARIES) -c -o ./build/ttf_loader/tables/font_table.o
