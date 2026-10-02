#include "bmp.h"

static int read_u16(FILE *fp, uint16_t *v)
{
    unsigned char b[2];
    if (fread(b, 1, 2, fp) != 2) return 0;
    *v = (uint16_t)b[0] | ((uint16_t)b[1] << 8);
    return 1;
}

static int read_u32(FILE *fp, uint32_t *v)
{
    unsigned char b[4];
    if (fread(b, 1, 4, fp) != 4) return 0;
    *v = (uint32_t)b[0] | ((uint32_t)b[1] << 8) |
         ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
    return 1;
}

int bmp_validate(FILE *fp, uint32_t *pixel_offset, uint32_t *pixel_bytes)
{
    unsigned char sig[2];
    uint32_t dib_size, width, height, compression, image_size;
    uint16_t planes, bpp;

    rewind(fp);
    if (fread(sig, 1, 2, fp) != 2 || sig[0] != 'B' || sig[1] != 'M')
        return 0;

    if (fseek(fp, 10, SEEK_SET) != 0 || !read_u32(fp, pixel_offset))
        return 0;
    if (!read_u32(fp, &dib_size) || dib_size < 40)
        return 0;
    if (!read_u32(fp, &width) || !read_u32(fp, &height))
        return 0;
    if (!read_u16(fp, &planes) || !read_u16(fp, &bpp))
        return 0;
    if (!read_u32(fp, &compression) || !read_u32(fp, &image_size))
        return 0;

    if (width == 0 || height == 0 || planes != 1 || bpp != 24 || compression != 0)
        return 0;

    if (image_size != 0)
        *pixel_bytes = image_size;
    else
    {
        uint64_t row = ((uint64_t)width * 3 + 3) & ~3ULL;
        uint64_t total = row * height;
        if (total > UINT32_MAX) return 0;
        *pixel_bytes = (uint32_t)total;
    }
    return 1;
}
