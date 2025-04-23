GCCFLAGS = -g -Wall -Wfatal-errors -fsanitize=address
UNITY_DIR = Unity/src
ALL = comission_test

comission_test: Unity/examples/comission/src/comissao.c Unity/examples/comission/test/test_comissao.c
	$(CC) $(GCCFLAGS) -I$(UNITY_DIR) -IUnity/examples/comission/src $^ -o $@

run_tests: comission_test
	./comission_test

clean:
	rm -f $(ALL) *.o