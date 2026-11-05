CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: rainfall

rainfall: main.cpp
	$(CXX) $(CXXFLAGS) -o rainfall main.cpp

clean:
	rm -f rainfall vector_out.txt sorted_by_rain.txt

.PHONY: all clean
