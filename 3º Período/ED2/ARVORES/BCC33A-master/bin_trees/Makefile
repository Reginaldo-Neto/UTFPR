all: ab arn
	#gcc -g -c -DAVLDEBUG ab.c

ab:
	gcc -g -c ab.c
	gcc -o abteste abteste.c ab.o

arn:
	gcc -g -c arn.c
	gcc -g -o arntest arntest.c arn.o
