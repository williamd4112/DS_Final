cc = g++
src = src/main.cpp src/bike.cpp src/bikebase.cpp src/station.cpp src/bikeheap.cpp src/standard.cpp src/roadmap.cpp
std = -std=c++11
out = bin/main.out

all: $(src)
	$(cc) -o $(out) $(src) $(std)
