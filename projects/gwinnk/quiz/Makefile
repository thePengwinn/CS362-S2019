CFLAGS= -Wall -fpic -coverage -lm -std=c99 

testme: testme.c
	gcc  -o testme -g  testme.c  $(CFLAGS)


runfasttest: testme
	./testme &> testmeiterations.out

runtest: testme
	./testme

coverage: 
	 gcov testme.c 
	 gcov testme.c >> testmeresult.out
	 cat testme.c.gcov >> testmeresult.out
	
all: runfasttest coverage

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out 
