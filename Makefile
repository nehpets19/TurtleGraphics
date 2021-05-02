turtleGraphics: main.o
	cc -o turtleGraphics main.o
main.o: main.c
	cc -c -Wall main.c
execute: turtleGraphics
	./turtleGraphics
clean:
	rm *.o