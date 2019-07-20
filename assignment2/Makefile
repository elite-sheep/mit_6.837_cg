#INCFLAGS = -I /mit/6.837/public/include/vecmath
#INCFLAGS += -I /mit/glut/include
#LINKFLAGS = -L /mit/6.837/public/lib -l vecmath
#LINKFLAGS += -L /mit/glut/lib -lGL -lGLU -lglut -lX11 -lXi
INCFLAGS  = -I ./GL
INCFLAGS += -I ./vecmath/include
INCFLAGS += -I ./
#INCFLAGS += -I ~/vecmath/include

LINKFLAGS  = -lglut -lGL -lGLU
LINKFLAGS += -lfltk -lfltk_gl
#LINKFLAGS += -L ~/vecmath/lib -lvecmath
#LINKFLAGS += -lfltk -lfltk_gl

CFLAGS    = -g
CFLAGS    += -DSOLN
CC        = g++
SRCS      =  $(wildcard ./src/*.cpp)
SRCS      += $(wildcard ./vecmath/src/*.cpp)
OBJS      = $(SRCS:.cpp=.o)
PROG      = a2

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)

bitmap.o: ./src/bitmap.h
camera.o: ./src/camera.h
Mesh.o: ./src/Mesh.h
MatrixStack.o: ./src/MatrixStack.h
modelerapp.o: ./src/modelerapp.h ./src/ModelerView.h ./src/modelerui.h ./src/bitmap.h ./src/camera.h
modelerui.o: ./src/modelerui.h ./src/ModelerView.h ./src/bitmap.h ./src/camera.h ./src/modelerapp.h
ModelerView.o: ./src/ModelerView.h ./src/camera.h
SkeletalModel.o: ./src/MatrixStack.h ./src/ModelerView.h ./src/Joint.h ./src/modelerapp.h

