# Declaration of variables
CXX = g++
CPP_FLAGS = --std=c++17 -Wall -O0 -g -pthread
 
# File names
EXEC = server.x
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CXX) -pthread $(OBJECTS) -o $(EXEC)
 
# To obtain object files
%.o: %.cpp
	$(CXX) -c $(CPP_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
