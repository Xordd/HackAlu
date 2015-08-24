#include <string.h>
#include <stdio.h>

#include "alu.h"
#include "gates.h"
#include "chips.h"

/*
 * The HACK ALU
 *
 * x and y: 16bit data inputs
 * zx: zero out x
 * nx: negate x
 * zy: zero y
 * ny: negate y
 * f: 0 for AND 1 for Add
 * no: negate output
 *
 * out: 16bit result
 * zr: true if out = 0
 * nr: true is out < 0
 */
void alu(const int *x, const int *y, const int zx, const int nx, const int zy, const int ny, const int f, const int no, int *out, int *zr, int *ng) {
	// Lets make a local copy of the input data
	int xTmp[16];
	int yTmp[16];
	memcpy(xTmp, x, 16 * sizeof(int));
	memcpy(yTmp, y, 16 * sizeof(int));
	
	
	// Pre-compute the inverse of the control bits
	int notZx = gNot(zx);
	int notNx = gNot(nx);
	int notZy = gNot(zy);
	int notNy = gNot(ny);
	int notF = gNot(f);
	int notNo = gNot(no);
	
	int i;
	for(i=0; i<16; i++) {
		
		// Zero x
		xTmp[i] = gAnd(notZx, xTmp[i]);
		
		// Not x
		xTmp[i] = gOr(gAnd(nx, gNot(xTmp[i])), gAnd(notNx, xTmp[i]));
		
		// Zero y
		yTmp[i] = gAnd(notZy, yTmp[i]);
		
		// Not y
		yTmp[i] = gOr(gAnd(ny, gNot(yTmp[i])), gAnd(notNy, yTmp[i]));
		
	}
	
	// Apply operation
	int outAnd[16];
	int outAdd[16];
	and16(xTmp, yTmp, outAnd);
	add16(xTmp, yTmp, outAdd);
	
	for(i=0; i<16; i++) {
		out[i] = gOr(gAnd(notF, outAnd[i]), gAnd(f, outAdd[i]));
	
		// negate output
		out[i] = gOr(gAnd(no, gNot(out[i])), gAnd(notNo, out[i]));
	}
	
	// Set output flags
	*zr = gNot(gOr(gOr8Way(out[0], out[1], out[2], out[3], out[4], out[5], out[6], out[7]), gOr8Way(out[8], out[9], out[10], out[11], out[12], out[13], out[14], out[15])));
	*ng = out[0];
}

