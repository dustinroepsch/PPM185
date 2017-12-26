#ifndef PPM185_H
#define PPM185_H

#include <stdint.h>

typedef struct
{
    uint8_t r, g, b;
} ppm_rgb_t;

typedef struct
{
    ppm_rgb_t *raster;
    uint32_t width, height;
} ppm_image_t;

ppm_image_t *ppm_create(uint32_t width, uint32_t height);

void ppm_destory(ppm_image_t **c);

void ppm_set_red(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t red);

void ppm_set_green(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t green);

void ppm_set_blue(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t red);

void ppm_set_rgb(ppm_image_t *image, uint32_t row, uint32_t col, ppm_rgb_t rgb);

ppm_rgb_t ppm_get_rgb(ppm_image_t *image, uint32_t row, uint32_t col);

void ppm_write_to_file(char* filename);

#endif