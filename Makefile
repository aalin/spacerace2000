FILES = main game game_state gameplay framebuffer shader
OBJS = $(addsuffix .o, $(FILES))

CC=clang
CFLAGS=-Wall -Wextra -ggdb -std=c++0x -stdlib=libstdc++

LFLAGS=-framework OpenGL -lglfw -lstdc++
CFLAGS+=-I/usr/X11/include/

%.o: %.cpp %.hpp
	$(CC) -c $(CFLAGS) $< -o $@

all: game

run: game
	./game

test: game
	./game test

game: $(OBJS)
	 $(CC) $(OBJS) $(LFLAGS) -o game

clean:
	rm -f *.o game

.PHONY: all run clean
