execute: turtleGraphics
	./turtleGraphics
turtleGraphics: main.o
	cc -o turtleGraphics main.o
main.o: main.c
	cc -c -Wall main.c
clean:
	rm *.o