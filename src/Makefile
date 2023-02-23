all: tictac
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
CXXFLAGS = $(include_dirs)
include_dirs = -I/usr/include/eigen3

tictac: $(OBJS)
	${CXX} $^ -o $@

%.o : %.c
	$(CXX)  -c $(CFLAGS) $<

clean:
	rm -r $(OBJS)
