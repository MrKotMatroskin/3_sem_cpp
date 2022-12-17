CWD := $(subst /,\\, $(abspath $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))))

# test:
#   $(info    DIR is $(CWD))

# Сompiler options
CC = g++
GXX_STANDARD=20
INCLUDE_PATHS = -I$(CWD)\\SDL2\\include -I$(CWD)\\SDL2\\include\\SDL2 -I$(CWD)\\src\\CoreLib\\
LIBS_PATHS = -L$(CWD)\\SDL2\\lib
CXXFLAGS = -O3 -Wall -Wextra -std=c++$(GXX_STANDARD) -fopenmp  -lpthread
CXXFLAGS += -g -lmingw64 -lSDL2main -lSDL2  $(INCLUDE_PATHS) $(LIBS_PATHS)
LXXFLAGS = -fopenmp -lpthread


LIB_PATH = $(CWD)\\SDL2\\
LIB_DEPEND = mingw32 SDL2main SDL2 
CXXFLAGS += $(patsubst %,-I%include,$(LIB_PATH))
LXXFLAGS += $(patsubst %,-L%lib,$(LIB_PATH)) $(addprefix -l, $(LIB_DEPEND))

all:
	$(CC) Julia.cpp -c -o Julia.o $(CXXFLAGS)
	$(CC) Julia.o -o Julia.exe $(LXXFLAGS)
	Julia.exe
