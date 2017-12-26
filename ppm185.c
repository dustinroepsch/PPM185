#include "ppm185.h"

#include <stdlib.h>

typedef struct
{
    uint8_t r, g, b;
} ppm_rgb_t;

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
    //raster is calloc'd to 0 (all black pixels)
    image->raster = calloc(width * height, sizeof(ppm_rgb_t));
    ;
    return image;
}

void ppm_destory(ppm_image_t **image)
{
    free((*image)->raster);
    free(*image);
    *image = NULL; //so students seg fault if they try to keep using image
}

void ppm_set_red(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t red)
{
    image->raster[row * image->width + col].r = red;
}

void ppm_set_green(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t green)
{
    image->raster[row * image->width + col].g = green;
}

void ppm_set_blue(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t blue)
{
    image->raster[row * image->width + col].b = blue;
}

void ppm_set_rgb(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t red, uint8_t green, uint8_t blue)
{
    ppm_rgb_t *pixel = &(image->raster[row * image->width + col]);
    pixel->r = red;
    pixel->g = green;
    pixel->b = blue;
}