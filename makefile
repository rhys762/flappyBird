EXEC_NAME=flappyBird
C_FLAGS=-Wall
L_FLAGS=-lSDL2 -lSDL2_image

$(EXEC_NAME): Bird.o main.o misc.o Pipe.o ShittyFont.o Sun.o Window.o
	g++ Bird.o main.o misc.o Pipe.o ShittyFont.o Sun.o Window.o -o $(EXEC_NAME) $(L_FLAGS)

Bird.o: Bird.cpp
	g++ $(C_FLAGS) -c Bird.cpp

main.o: main.cpp
	g++ $(C_FLAGS) -c main.cpp

misc.o: misc.cpp
	g++ $(C_FLAGS) -c misc.cpp

Pipe.o: Pipe.cpp
	g++ $(C_FLAGS) -c Pipe.cpp

ShittyFont.o: ShittyFont.cpp
	g++ $(C_FLAGS) -c ShittyFont.cpp

Sun.o: Sun.cpp
	g++ $(C_FLAGS) -c Sun.cpp

Window.o: Window.cpp
	g++ $(C_FLAGS) -c Window.cpp

clean:
	rm *.o $(EXEC_NAME)
