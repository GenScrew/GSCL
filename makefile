CC=g++
CFLAGS=-I.
LDFLAGS=

EXEC=GSCL
SRC=src/main.cpp src/geometric_algebra.cpp src/screw.cpp 
OBJ=$(SRC:%.cpp=build/%.o)

all: $(EXEC)

# Compilation Linux
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: include/main.h

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

# Nettoyage des sources
clean:
	rm -rf build
