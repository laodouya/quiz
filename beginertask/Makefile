hello : hello.o
	g++ -o hello hello.o
hello.o : helloworld.c
	g++ -c helloworld.c -o hello.o

.PHONY : clean
clean :
	-rm hello.o hello

