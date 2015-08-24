#include <stdlib.h>
#include <stdio.h>

#include "chips.h"
#include "alu.h"

int main() {
	
	int a[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	int b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	int out[16];
	int zx = 0;
	int nx = 0;
	int zy = 0;
	int ny = 0;
	int f = 1;
	int no = 0;
	int zr = 0;
	int ng = 0;

	alu(a, b, zx, nx, zy, ny, f, no, out, &zr, &ng);
	
	
	int i=0;
	for(i=0; i<16; i++) {
		printf("%d", out[i]);
	}
	printf("\n");
	
	return 0;
}
