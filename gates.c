#include "gates.h"


/* The NAND gate is our base gate, every subsequent gates are either based on
 NANDs or from gates derived from NANDs  */
int gNand(int a, int b) {
	if(a && b) return 0;
	else return 1;
}

int gNot(int a) {
	return gNand(a, a);
}

int gAnd(int a, int b) {
	return gNot(gNand(a, b));
}

int gOr(int a, int b) {
	return gNot(gAnd(gNot(a), gNot(b)));
}

int gNor(int a, int b) {
	return gNot(gOr(a, b));
}

int gXor(int a, int b) {
	return gOr(gAnd(a, gNot(b)), gAnd(gNot(a), b));
}

int gXnor(int a, int b) {
	return gNot(gXor(a, b));
}

int gOr4Way(int a, int b, int c, int d) {
	return gOr(gOr(a, b), gOr(c, d));
}

int gOr8Way(int a, int b, int c, int d, int e, int f, int g, int h) {
	return gOr(gOr4Way(a, b, c, d), gOr4Way(e, f, g, h));
}

int gAnd4Way(int a, int b, int c, int d) {
	return gAnd(gAnd(a, b), gAnd(c, d));
}

int gAnd8Way(int a, int b, int c, int d, int e, int f, int g, int h) {
	return gAnd(gAnd4Way(a, b, c, d), gAnd4Way(e, f, g, h));
}

