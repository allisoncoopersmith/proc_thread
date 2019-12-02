#ifndef _multitest_h_
#define _multitest_h_
#include <stdio.h>
#include <stdlib.h>

//in the header, specify parameters --> ???? macros???

#define doStuff(x, y, z, arr) search(x, y, z, arr)//fix this -- need to pass the array in last spot
	int search(int, int, int, int*);

#endif
