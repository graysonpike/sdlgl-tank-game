.DEFAULT_GOAL := main.out

CC = g++
FLAGS = -std=c++11 -g
LIBS  = -lsdlgl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


OBJ_FILES = main.o \
			entities/tank/tank.o \
			entities/tank/tiger/tiger.o


clean:
	rm -f *.out *.o
	rm -f entities/*.out entities/*.o
	rm -f entities/tank/*.out entities/tank/*.o
	rm -f entities/tank/tiger/*.out entities/tank/tiger/*.o

main.out: $(OBJ_FILES)
	$(CC) $(FLAGS) -o main.out $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@
