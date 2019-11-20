all: 
	$(error "make to target 'proc' or 'thread'")

proc: searchtest.c multitest_proc.o
	gcc searchtest.c multitest_proc.o

thread: searchtest.c multitest_thread.o
	gcc -lpthread searchtest.c multitest_thread.o

multitest_proc.o: multitest_proc.c
	gcc -c multitest_proc.c

multitest_thread.o: multitest_thread.c
	gcc -c multitest_thread.c

clean:
	rm a.out; rm multitest*.o
