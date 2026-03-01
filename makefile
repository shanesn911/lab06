all: stats2 rhymes

stats2: stats2.cpp
	g++ --std=c++17 -Wall -o stats2 stats2.cpp

rhymes: rhymes.cpp
	g++ --std=c++17 -Wall -o rhymes rhymes.cpp

clean:
	rm -f stats2 rhymes