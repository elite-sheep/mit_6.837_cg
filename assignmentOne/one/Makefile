INCFLAGS  = -I ../../GL/
INCFLAGS += -I ../../vecmath/include

LINKFLAGS = -lglut -lGL -lGLU
#LINKFLAGS += -L ./vecmath/src 

CFLAGS    = -O2 -Wall -ansi -DSOLN
CC        = g++
SRCS      = $(wildcard src/*.cpp)
SRCS += $(wildcard ../../vecmath/src/*.cpp)
OBJS      = $(SRCS:.cpp=.o)
PROG      = a1

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)
