CPP=clang++
CPPFLAGS=-std=c++17 -pedantic -Wall -Wextra -Werror -g -O0 -c

OBJFILES=lox.o token.o scanner.o

lox: lox.o token.o
	${CPP} -o lox lox.o token.o

lox.o: lox.cc
	${CPP} ${CPPFLAGS} lox.cc -o lox.o

token.o: token.cc
	${CPP} ${CPPFLAGS} token.cc -o token.o

clean:
	rm -f *.o ./lox
