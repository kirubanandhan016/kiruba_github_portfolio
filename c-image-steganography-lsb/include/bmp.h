#ifndef BMP_H
#define BMP_H
#include <stdint.h>
#include <stdio.h>
int bmp_validate(FILE *fp, uint32_t *pixel_offset, uint32_t *pixel_bytes);
#endif
