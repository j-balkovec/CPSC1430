all: rpn

rpn: queue.o stack.o p5.o
	g++ queue.o stack.o p5.o -o rpn

queue.o: queue.cpp queue.h
	g++ -c queue.cpp

stack.o: stack.cpp stack.h
	g++ -c stack.cpp

p5.o: p5.cpp stack.h queue.h
	g++ -c p5.cpp

clean:
	rm -f *.o rpn


#makes samo wet