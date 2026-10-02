#include "steg.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static int encode(const char *input, const char *output, const char *msg)
{
    FILE *in = fopen(input, "rb");
    FILE *out = fopen(output, "wb");
    if (!in || !out)
    {
        if (in) fclose(in);
        if (out) fclose(out);
        perror("file");
        return 1;
    }
    int ok = steg_encode(in, out, (const unsigned char *)msg, (uint32_t)strlen(msg));
    fclose(in);
    fclose(out);
    if (!ok)
    {
        fprintf(stderr, "Encoding failed: invalid BMP or insufficient capacity\n");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 5 && strcmp(argv[1], "encode") == 0)
        return encode(argv[2], argv[3], argv[4]);

    if (argc == 3 && strcmp(argv[1], "decode") == 0)
    {
        FILE *fp = fopen(argv[2], "rb");
        if (!fp) { perror("file"); return 1; }
        int ok = steg_decode(fp);
        fclose(fp);
        return ok ? 0 : 1;
    }

    fprintf(stderr, "Usage:\n  %s encode input.bmp output.bmp message\n  %s decode image.bmp\n",
            argv[0], argv[0]);
    return 2;
}
