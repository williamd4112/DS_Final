cc = g++
src = src/main.cpp src/station.cpp src/bike.cpp src/heap.cpp 
std = -std=c++11
out = bin/main.out

all: $(src)
	$(cc) -o $(out) $(src) $(std)
