PHONY := clean
CXXFLAGS := -O3 -Wall -Wextra -pedantic
LDFLAGS := -pthread
CXX := g++
CC := g++

all: future_call shared_call state_call async_call async_graph

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c -o $@ $<

future_call: future_call.o

shared_call: shared_call.o

state_call: state_call.o

async_call: async_call.o

async_graph: async_graph.o

clean:
	@rm -f future_call future_call.o \
		shared_call shared_call.o \
		state_call state_call.o \
		async_call async_call.o \
		async_graph async_graph.o >/dev/null 2>&1
