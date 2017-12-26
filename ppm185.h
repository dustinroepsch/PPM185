#ifndef PPM185_H
#define PPM185_H

#include <stdint.h>

typedef struct ppm_image ppm_image_t;

/*
* Creates an image with dimensions `width` and `height`
* and returns a pointer to it.
*
*EXAMPLE USE:
* ppm_image_t *my_image = ppm_create(300, 400);
*IMPORTANT NOTES: 
* It is good practice to call `ppm_destroy` on images when you are done 
* with them. Failure to do this may introduce "Memory Leaks" into your program.
*/
ppm_image_t *ppm_create(uint32_t width, uint32_t height);

/*
* Destroys an image. This function should be called when you are absolutely sure
* you do not need to use `image` again in your program. Attempting to use a destroyed image
* will cause a "segmentation fault" error.
*
*EXAMPLE USE:
* ppm_image_t *my_image = ppm_create(300, 400);
* //do everything I'll ever want to do with this image, ever.
* ppm_destroy(&my_image);
* //never allowed to use my_image again
*
*IMPORTANT NOTES:
* Destroying the same image twice will cause a segmentation fault.
*
* The parameter `image` has type ppm_image_t**, notice that there are two asteriks.
* This is called a "double pointer". Because of this, when using this function you will want
* to pass in the `address` of an `ppm_image_t*`
*
*/
void ppm_destory(ppm_image_t **image);

/*
* Colors are represented by three numbers in the range 0-255. (unsigned 8-bit numbers)
* We call these numbers `channels` and use them to say how much red, green, and blue color is at a given pixel in the image.
* If want to say that a channel doesn't contribute to the color of an image at a pixel, we set that channels number
* value to 0. Conversely, if we want that channel to contribute as much as possible to the pixel, we set it to 255.
* Hence, the color (0, 0, 0) is black and the color (255, 255, 255) is white.
*
*EXAMPLE USE:
* ppm_image_t *my_image = ppm_create(300, 400);
* ppm_set_red(my_image, 4, 15, 180); //sets the red value for the pixel at row 4, col 15 to 180
* ppm_set_rgb(my_image, 10, 20, 255, 255, 255); //sets pixel (10, 20) to white by setting red, green, and blue to 255
*
*IMPORTANT NOTES:
* A nice tool to help you pick RGB values can be found by googling `color picker`
* https://www.google.com/search?q=color+picker
*
* This tool is made by Google and let's you easily find r, g, and b values for the color you want.
*/
void ppm_set_red(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t red);
void ppm_set_green(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t green);
void ppm_set_blue(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t blue);
void ppm_set_rgb(ppm_image_t *image, uint32_t row, uint32_t col, uint8_t red, uint8_t green, uint8_t blue);

/*
* Saves the ppm to a file named `filename`
*
*EXAMPLE USE:
* ppm_write_to_file(my_image, "output_image.ppm");
*
*IMPORTANT NOTES:
* the filename may include a path, example "c:\\example_folder\output.ppm"
*/
void ppm_write_to_file(ppm_image_t* image, char *filename);

#endif