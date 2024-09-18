GCCFLAGS = -g -Wall -Wfatal-errors 
ALL = identifier
GCC = gcc

all: $(ALL)

identifier: identifier.c
	$(GCC) $(GCCFLAGS) -o $@ $@.c

cov:
	$(GCC) $(GCCFLAGS) -fprofile-arcs -ftest-coverage identifier.c -o identifier
	./identifier
	gcov -b *.gcno

clean:
	rm -fr $(ALL) *.o cov* *.dSYM *.gcda *.gcno *.gcov
