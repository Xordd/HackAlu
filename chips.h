#ifndef CHIPS_H
#define CHIPS_H

void mux(const int s, const int *in, int *out);

void demux(const int s, const int *in, int *out);

void and16(const int *a, const int *b, int *out);

void or16(const int *a, const int *b, int *out);

void not16(const int *in, int *out);

void mux16(const int s, const int *a, const int *b, int *out);

void mux4Way16(const int s1, const int s0, const int *a, const int *b, const int *c, const int *d, int *out);

void mux8Way16(const int s2, const int s1, const int s3, const int *a, const int *b, const int *c, const int *d,
 const int *e, const int *f, const int *g, const int *h, int *out);

void demux4Way(const int s1, const int s0, const int in, int *out1, int *out2, int *out3, int *out4);

void demux8Way(const int s2, const int s1, const int s0, const int in, int *out1, int *out2, int *out3, int *out4, int *out5, int *out6, int *out7, int *out8);

void halfAdder(int a, int b, int *sum, int *carry);

void fullAdder(const int a, const int b, const int c, int *sum, int *carry);

void add16(const int *a, const int *b, int *out);

void inc16(const int *in, int *out);

#endif
