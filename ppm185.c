#include "ppm185.h"

struct ppm_rgb
{
    uint8_t r, g, b;
};

struct ppm_image
{
    ppm_rgb_t *raster;
    uint32_t width, height;
};

ppm_image_t *ppm_create(uint32_t width, uint32_t height)
{
    ppm_image_t *image = malloc(sizeof(ppm_image_t));
    image->width = width;
    image->height = height;
    image->raster = malloc(sizeof(ppm_rgb_t) * width * height);
    return image;
}