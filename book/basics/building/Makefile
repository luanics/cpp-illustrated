CC=g++
DEPS = Car.hpp
OBJ = Main.cpp Car.cpp 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

building_main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
