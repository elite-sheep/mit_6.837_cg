CC = g++
SRCS = $(wildcard ./src/*.cpp)
SRCS += $(wildcard ../vecmath/src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
PROG = a4
CFLAGS = -g -Wall -Wextra
INCFLAGS = -I../vecmath/include

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

clean:
	rm -f *.bak src/*.o core.* $(PROG) 
