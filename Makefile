GCCFLAGS = -g -Wall -Wfatal-errors 
ALL = identifier
GCC = gcc

all: $(ALL)

identifier: identifier.c
	$(GCC) $(GCCFLAGS) -o $@ $@.c

clean:
	rm -fr $(ALL) *.o cov* *.dSYM *.gcda *.gcno *.gcov

