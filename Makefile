FILES = $(basename $(wildcard *.cpp))
OBJS = $(addsuffix .o, $(FILES))

CC=clang
CFLAGS=-Wall -Wextra -ggdb -std=c++11 -stdlib=libc++

ifeq ($(shell uname), Darwin)
  LFLAGS=-framework OpenGL -lglfw -lglew -lstdc++ -stdlib=libc++
else
  LFLAGS=-lglfw -lGLEW -lstdc++ -lGL -lm -lX11 -lpthread -lrt -lXrandr
  CFLAGS+=-I/usr/X11/include/
endif

%.o: %.cpp %.hpp
	@echo "Compiling $< => $@"
	@$(CC) -c $(CFLAGS) $< -o $@

all: game

run: game
	./game

test: game
	./game test

info:
	@echo "CC: $(CC)"
	@echo "LFLAGS: $(LFLAGS)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo

game: $(OBJS)
	@echo
	@echo "Linking $(OBJS) => game"
	@$(CC) $(OBJS) $(LFLAGS) -o game

clean:
	rm -f *.o game

.PHONY: info all demo clean
