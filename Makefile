compile: update
	make -f qMakeFile

run: compile
	./Mp3Player

update: Mp3Player.pro
	qmake -o qMakeFile Mp3Player.pro

clean:
	rm -f qMakeFile Mp3Player *.o 
	rm -f *.o
	