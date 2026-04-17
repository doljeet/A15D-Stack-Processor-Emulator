CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET   = stos
SRCDIR   = src
SRC      = $(wildcard $(SRCDIR)/*.cpp)
OBJ      = $(SRC:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
