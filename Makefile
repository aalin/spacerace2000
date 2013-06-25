FILES = main game game_state gameplay framebuffer shader opengl splines track track_model racer racer_model track_info vertex_array track_loader menu
OBJS = $(addsuffix .o, $(FILES))

CC=clang
CFLAGS=-Wall -Wextra -ggdb -std=c++11 -stdlib=libstdc++

ifeq ($(shell uname), Darwin)
LFLAGS=-framework OpenGL -lglfw -lglew -lstdc++
else
LFLAGS=-lglfw -lGLEW -lstdc++ -lGL -lm -lX11 -lpthread -lrt -lXrandr
CFLAGS+=-I/usr/X11/include/
endif

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
