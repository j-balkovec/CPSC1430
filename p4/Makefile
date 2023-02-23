CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Object files
OBJ_LIST = list.o
OBJ_P4 = p4.o

# Targets
TARGET = prog

all: $(TARGET)

$(TARGET): $(OBJ_LIST) $(OBJ_P4)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile list.o from list.cpp
list.o: list.cpp list.h
	$(CXX) $(CXXFLAGS) -c $<

# Compile p4.o from p4.cpp
p4.o: p4.cpp list.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ_LIST) $(OBJ_P4) $(TARGET)

