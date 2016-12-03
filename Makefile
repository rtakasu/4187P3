CC=g++
LDLIBS=-lm -lcrypto
CXXFLAGS=-g --std=c++0x

OBJ=hwcopy.o 

build: rgt2108.3

rgt2108.3: $(OBJ) copyfile
	$(CC) $(CXXFLAGS) -o $@ $(OBJ) 

copyfile: copyfile.o
	$(CC) $(CXXFLAGS) -o $@ copyfile.o

test: build
	./rgt2108.3 < ./tests/test1/test1.txt
	./rgt2108.3 < ./tests/test2/test2.txt


exec: build
	./rgt2108.3 $(ARGS)

.PHONY: clean
clean:
	rm -rf rgt2108.3 *.o *.core
