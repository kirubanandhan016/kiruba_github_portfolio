#include "steg.h"
#include "bmp.h"
#include <stdlib.h>
#include <string.h>

static int write_bit(unsigned char *byte, int bit)
{
    *byte = (unsigned char)((*byte & 0xFEu) | (unsigned char)(bit & 1));
    return 0;
}

static int encode_u32(FILE *in, FILE *out, uint32_t value)
{
    for (int bit = 31; bit >= 0; --bit)
    {
        int c = fgetc(in);
        if (c == EOF) return 0;
        write_bit((unsigned char *)&c, (value >> bit) & 1);
        if (fputc(c, out) == EOF) return 0;
    }
    return 1;
}

static int encode_bytes(FILE *in, FILE *out, const unsigned char *data, uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
        for (int bit = 7; bit >= 0; --bit)
        {
            int c = fgetc(in);
            if (c == EOF) return 0;
            write_bit((unsigned char *)&c, (data[i] >> bit) & 1);
            if (fputc(c, out) == EOF) return 0;
        }
    return 1;
}

int steg_encode(FILE *in, FILE *out, const unsigned char *msg, uint32_t len)
{
    uint32_t offset, bytes;
    if (!bmp_validate(in, &offset, &bytes)) return 0;
    if (len == 0 || bytes < 32u + len * 8u) return 0;

    rewind(in);
    for (uint32_t i = 0; i < offset; ++i)
    {
        int c = fgetc(in);
        if (c == EOF || fputc(c, out) == EOF) return 0;
    }
    if (!encode_u32(in, out, len)) return 0;
    if (!encode_bytes(in, out, msg, len)) return 0;

    int c;
    while ((c = fgetc(in)) != EOF)
        if (fputc(c, out) == EOF) return 0;
    return 1;
}

static int read_bits(FILE *fp, unsigned int n, uint32_t *value)
{
    uint32_t v = 0;
    for (unsigned int i = 0; i < n; ++i)
    {
        int c = fgetc(fp);
        if (c == EOF) return 0;
        v = (v << 1) | ((unsigned char)c & 1u);
    }
    *value = v;
    return 1;
}

int steg_decode(FILE *in)
{
    uint32_t offset, bytes, len;
    if (!bmp_validate(in, &offset, &bytes)) return 0;
    if (fseek(in, (long)offset, SEEK_SET) != 0) return 0;
    if (!read_bits(in, 32, &len) || len == 0 || len > (bytes - 4u) / 8u)
        return 0;

    unsigned char *msg = malloc((size_t)len + 1u);
    if (!msg) return 0;

    for (uint32_t i = 0; i < len; ++i)
    {
        uint32_t byte;
        if (!read_bits(in, 8, &byte))
        {
            free(msg);
            return 0;
        }
        msg[i] = (unsigned char)byte;
    }
    msg[len] = '\0';
    printf("%s\n", msg);
    free(msg);
    return 1;
}
