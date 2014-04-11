CC = g++
CFLAGS = -c -I /usr/local/include/openbabel-2.0/ -I /software/boost_1_52_0/ -std=c++11 -Wall
LDFLAGS = -l openbabel -L /usr/local/lib/openbabel/2.3.1/ -L /software/boost_1_52_0/stage/lib/

all: tanimoto_search

tanimoto_search: tanimoto_search.o
	$(CC) $(LDFLAGS) tanimoto_search.o -o ./tanimoto_search

tanimoto_search.o: tanimoto_search.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) tanimoto_search.cpp
	
clean:
	rm -v tanimoto_search.o tanimoto_search
