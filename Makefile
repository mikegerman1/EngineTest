CC = gcc  #x86_64-w64-mingw32-gcc
EXECNAME = ./bin/main

SCRS = source/main.c source/game.c source/cpugraphics.c source/vector.c
all:
	$(CC) -o $(EXECNAME) $(SCRS) -lSDL3 -I ./include/ -lm 
	#-I ./../SDL3-3.4.8/x86_64-w64-mingw32/include -L ./../SDL3-3.4.8/x86_64-w64-mingw32/lib   


run:
	$(CC) -o $(EXECNAME) $(SCRS) -lSDL3 -I ./include/ -lm 
	$(EXECNAME)

runwin:
	$(CC) -o $(EXECNAME).exe $(SCRS) -lSDL3 -I ./include/ -lm -I ./../SDL3-3.4.8/x86_64-w64-mingw32/include -L ./../SDL3-3.4.8/x86_64-w64-mingw32/lib   
	$(EXECNAME).exe


#./*.c -lSDL3 -I ./../SDL3-3.4.8/x86_64-w64-mingw32/include/ -L ./../SDL3-3.4.8/x86_64-w64-mingw32/lib -pthread

