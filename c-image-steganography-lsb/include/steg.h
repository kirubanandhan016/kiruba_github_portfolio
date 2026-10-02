#ifndef STEG_H
#define STEG_H
#include <stdint.h>
#include <stdio.h>
int steg_encode(FILE *in, FILE *out, const unsigned char *msg, uint32_t len);
int steg_decode(FILE *in);
#endif
