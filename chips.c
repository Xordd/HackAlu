#include "gates.h"
#include "chips.h"
#include <stdio.h>


/* Multiplexer
 * s: 1bit, in: 2bit, out: 1bit
 */
void mux(const int s, const int *in, int *out) {
	int notS = gNot(s);
	
	*out = gOr(gAnd(notS, in[0]), gAnd(s, in[1]));
}


/* Demultiplexer
 * s: 1bit, in: 1bit, out 2bit
 */
void demux(const int s, const int *in, int *out) {
	int notS = gNot(s);
	
	out[0] = gAnd(*in, notS);
	out[1] = gAnd(*in, s);
}


/*
 * 16 bitwise AND beween a and b
 */
void and16(const int *a, const int *b, int *out) {
	int i=0;
	for(i=0; i<16; i++) {
		out[i] = gAnd(a[i], b[i]);
	}
}


/*
 * 16 bitwise OR between a and b
 */
void or16(const int *a, const int *b, int *out) {
	int i=0;
	for(i=0; i<16; i++) {
		out[i] = gOr(a[i], b[i]);
	}
}


/*
 * 16bit in is not'ed intou out
 */
void not16(const int *in, int *out) {
	int i=0;
	for(i=0; i<16; i++) {
		out[i] = gNot(in[i]);
	}
}


/*
 * Select either 16bit a or 16bit b to go to out
 */
void mux16(const int s, const int *a, const int *b, int *out) {
	int notS = gNot(s);
	
	int i=0;
	for(i=0; i<16; i++) {
		out[i] = gOr(gAnd(notS, a[i]), gAnd(s, b[i]));
	}
}


/*
 * Select one of 4 16bit inputs
 * selector appear in reverse order so that the MSB is on the left
 */
void mux4Way16(const int s1, const int s0, const int *a, const int *b, const int *c, const int *d, int *out) {
	int notS0 = gNot(s0);
	int notS1 = gNot(s1);
	
	int i=0;
	for(i=0; i<16; i++) {
		int bitA = gAnd(gAnd(notS0, notS1), a[i]);
		int bitB = gAnd(gAnd(s0, notS1), b[i]);
		int bitC = gAnd(gAnd(notS0, s1), c[i]);
		int bitD = gAnd(gAnd(s0, s1), d[i]);
	
		out[i] = gOr4Way(bitA, bitB, bitC, bitD);
	}
}


/*
 * Select from 8 16bit inputs based on 3 selectors
 */
void mux8Way16(const int s2, const int s1, const int s0, const int *a, const int *b, const int *c, const int *d,
 const int *e, const int *f, const int *g, const int *h, int *out) {
	int notS0 = gNot(s0);
	int notS1 = gNot(s1);
	int notS2 = gNot(s2);
	
	int i=0;
	for(i=0; i<16; i++) {
		int bitA = gAnd4Way(notS2, notS1, notS0, a[i]);
		int bitB = gAnd4Way(notS2, notS1, s0, b[i]);
		int bitC = gAnd4Way(notS2, s1, notS0, c[i]);
		int bitD = gAnd4Way(notS2, s1, s0, d[i]);
		int bitE = gAnd4Way(s2, notS1, notS0, e[i]);
		int bitF = gAnd4Way(s2, notS1, s0, f[i]);
		int bitG = gAnd4Way(s2, s1, notS0, g[i]);
		int bitH = gAnd4Way(s2, s1, s0, h[i]);
			
		out[i] = gOr8Way(bitA, bitB, bitC, bitD, bitE, bitF, bitG, bitH);
	}
}


/*
 * Send a 1bit input to one of 4 outputs based on 2 selector bits
 */
void demux4Way(const int s1, const int s0, const int in, int *out1, int *out2, int *out3, int *out4) {
	int notS0 = gNot(s0);
	int notS1 = gNot(s1);
	
	*out1 = gAnd(gAnd(notS1, notS0), in);
	*out2 = gAnd(gAnd(notS1, s0), in);
	*out3 = gAnd(gAnd(s1, notS0), in);
	*out4 = gAnd(gAnd(s1, s0), in);
}

/*
 * Send a 1bit input to one of 8 outputs based on 3 selector bits
 */

void demux8Way(const int s2, const int s1, const int s0, const int in, int *out1, int *out2, int *out3, int *out4, int *out5, int *out6, int *out7, int *out8) {
	int notS0 = gNot(s0);
	int notS1 = gNot(s1);
	int notS2 = gNot(s2);
	
	*out1 = gAnd4Way(notS2, notS1, notS0, in);
	*out2 = gAnd4Way(notS2, notS1, s0, in);
	*out3 = gAnd4Way(notS2, s1, notS0, in);
	*out4 = gAnd4Way(notS2, s1, s0, in);
	*out5 = gAnd4Way(s2, notS1, notS0, in);
	*out6 = gAnd4Way(s2, notS1, s0, in);
	*out7 = gAnd4Way(s2, s1, notS0, in);
	*out8 = gAnd4Way(s2, s1, s0, in);
}


void halfAdder(const int a, const int b, int *sum, int *carry) {
	*sum = gXor(a, b);
	*carry = gAnd(a, b);
}


void fullAdder(const int a, const int b, const int c, int *sum, int *carry) {
	int sumTmp=0, carryTmp1=0, carryTmp2=0;
	halfAdder(a, b, &sumTmp, &carryTmp1);
	halfAdder(sumTmp, c, sum, &carryTmp2);
	*carry = gOr(carryTmp1, carryTmp2);
}


/*
 * Add 2 16bit numbers
 */
void add16(const int *a, const int *b, int *sum) {
	int carry=0;
	int i;
	for(i=15; i>=0; i--) {
		fullAdder(a[i], b[i], carry, &sum[i], &carry);
	}
}

/*
 * Increment in by 1
 */
void inc16(const int *in, int *out) {
	int one[16] = {0};
	one[15] = 1;
	
	add16(in, one, out);
}

