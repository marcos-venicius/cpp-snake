CXX = g++
CXXFLAGS = -Wall -std=c++11
LIBFLAGS = -lglut -lGLU -lGL

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LIBFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< $(LIBFLAGS)

clean:
	rm -rf $(OBJ) $(TARGET)