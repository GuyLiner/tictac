all: tictac
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

tictac: $(OBJS)
	${CXX} $^ -o $@

%.o : %.c
	$(CXX) -c $< 

clean:
	rm -r $(OBJS)
