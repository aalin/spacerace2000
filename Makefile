FILES = main game game_state gameplay framebuffer shader opengl splines track track_model
OBJS = $(addsuffix .o, $(FILES))

CC=clang
CFLAGS=-Wall -Wextra -ggdb -std=c++11 -stdlib=libstdc++

LFLAGS=-framework OpenGL -lglfw -lglew -lstdc++
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
