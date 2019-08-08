CPP=clang++
CPPFLAGS=-std=c++17 -pedantic -Wall -Wextra -Werror -g -O0 -c

OBJFILES=lox.o token.o scanner.o

lox: lox.o token.o scanner.o
	${CPP} -o lox lox.o token.o scanner.o

lox.o: lox.cc
	${CPP} ${CPPFLAGS} lox.cc -o lox.o

token.o: token.cc
	${CPP} ${CPPFLAGS} token.cc -o token.o

scanner.o: scanner.cc
	${CPP} ${CPPFLAGS} scanner.cc -o scanner.o


clean:
	rm -f *.o ./lox
