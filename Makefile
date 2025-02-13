CFLAGS = -g -Wall #-std=c++11
CC = g++

objects = main.o server.o

server: $(objects)
	$(CC) -o server $(objects) 

main.o: main.cpp

server.o: server.cpp

.PHONY : clean
clean: 
	rm -f server $(objects)
	rm -f server2
	rm -f errReport.txt
	rm -f serverlog.txt
	rm -f serverlog_win.txt