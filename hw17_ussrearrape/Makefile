CXX = g++
CXXFLAGS = -std=c++20
SRCS = comisionist.cpp shpionen.cpp
OBJS = $(SRCS:.cpp=.o)
TARGETS = $(SRCS:.cpp=)

all: $(TARGETS)

%: %.o
	$(CXX) $(CXXFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
	rm -f postman.txt
