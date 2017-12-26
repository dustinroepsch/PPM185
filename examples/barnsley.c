#include "../ppm185.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>

#define IMAGE_WIDTH 500
#define IMAGE_HEIGHT (IMAGE_WIDTH * 2)
#define NUM_PIXELS (IMAGE_HEIGHT * IMAGE_WIDTH)
#define NUM_ITERATIONS 10000000

#define X_WINDOW_MIN -2.1820
#define X_WINDOW_MAX 2.6558
#define Y_WINDOW_MIN 0
#define Y_WINDOW_MAX 9.9983

/*
* Input: double value in range [oldMin, oldMax]
* Output: double in range [newMin, newMax]
*/
double scale(double value, double oldMin, double oldMax, double newMin, double newMax)
{
    return ((newMax - newMin) / (oldMax - oldMin)) * (value - oldMin) + newMin;
}

void f1(double *x, double *y)
{
    *x = 0;
    *y = *y * 0.16;
}

void f2(double *x, double *y)
{
    double old_x = *x;
    double old_y = *y;
    *x = 0.85 * old_x + 0.04 * old_y;
    *y = -0.04 * old_x + 0.85 * old_y + 1.6;
}

void f3(double *x, double *y)
{
    double old_x = *x;
    double old_y = *y;

    *x = 0.2 * old_x - 0.26 * old_y;
    *y = 0.23 * old_x + 0.22 * old_y + 1.6;
}

void f4(double *x, double *y)
{
    double old_x = *x;
    double old_y = *y;

    *x = -0.15 * old_x + 0.28 * old_y;
    *y = 0.26 * old_x + 0.24 * old_y + 0.44;
}

void mutate_point(double *x, double *y)
{
    int roll = rand() % 100;

    if (roll < 1) //1% chance
    {
        f1(x, y);
    }
    else if (roll < 85) //85% chance
    {
        f2(x, y);
    }
    else if (roll < 85 + 7) //7% chance
    {
        f3(x, y);
    }
    else
    {
        f4(x, y);
    }
}

void calc_sd(int *arr, double *mean, double *sd)
{
    double sum = 0;
    double sum_squared = 0;

    for (int i = 0; i < NUM_PIXELS; i++)
    {
        sum += arr[i];
        sum_squared += arr[i] * arr[i];
    }

    *mean = sum / NUM_PIXELS;
    *sd = sqrt(NUM_PIXELS * sum_squared - sum * sum) / NUM_PIXELS;
}

int main()
{
    srand(time(NULL));

    //this array is big so I used calloc to not blow up the stack (with the bonus of initializing every element of the array to zero)
    int *histogram = calloc(NUM_PIXELS, sizeof(int));

    double x = 0;
    double y = 0;

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        mutate_point(&x, &y);
        int screen_x = scale(x, X_WINDOW_MIN, X_WINDOW_MAX, 0, IMAGE_WIDTH);
        int screen_y = scale(y, Y_WINDOW_MIN, Y_WINDOW_MAX, 0, IMAGE_HEIGHT);

        histogram[screen_y * IMAGE_WIDTH + screen_x] += 1;
    }

    double mean, sd;
    calc_sd(histogram, &mean, &sd);

    double gradient_min = mean - sd;
    double gradient_max = mean + sd;

    ppm_image_t *output_image = ppm_create(IMAGE_WIDTH, IMAGE_HEIGHT);

    for (int row = 0; row < IMAGE_HEIGHT; row++)
    {
        for (int col = 0; col < IMAGE_WIDTH; col++)
        {
            int green = histogram[row * IMAGE_WIDTH + col];

            if (green == 0)
                continue;

            if (green < gradient_min)
            {
                green = gradient_min;
            }
            if (green > gradient_max)
            {
                green = gradient_max;
            }
            ppm_set_green(output_image, IMAGE_HEIGHT - row - 1, col, scale(green, gradient_min, gradient_max, 0, 255));
        }
    }

    ppm_write_to_file(output_image, "barnsley.ppm");

    //cleanup
    free(histogram);
    ppm_destory(&output_image);
    return 0;
}
