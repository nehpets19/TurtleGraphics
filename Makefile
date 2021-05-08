turtleGraphics: main.o
	gcc -o turtleGraphics main.o
main.o: main.c
	gcc -c -Wall main.c
execute: turtleGraphics
	./turtleGraphics
clean:
	rm *.o