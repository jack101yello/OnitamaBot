# A simple Makefile for compiling small SDL projects

# set the compiler
CC := g++

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lSDL2_ttf -lm
# add header files here
HDRS := Board/board.h Piece/piece.h Button/button.h Textbox/textbox.h Card/card.h Card/deck.h Game/game.h Player/player.h Player/human_player.h Types/types.h

# add source files here
SRCS := main.cpp Board/board.cpp Piece/piece.cpp Button/button.cpp Textbox/textbox.cpp Card/card.cpp Card/deck.cpp Game/game.cpp Player/player.cpp Player/human_player.cpp

# generate names of object files
OBJS := $(SRCS:.cpp=.o)

# name of executable
EXEC := onitama.exe

# default recipe
all: $(EXEC)

run: $(EXEC)
	./$(EXEC)
 
showfont: showfont.c Makefile
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

glfont: glfont.c Makefile
	$(CC) -o $@ $@.cpp $(CFLAGS) $(LIBS)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.cpp) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all run clean