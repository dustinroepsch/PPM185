#include "../ppm185.h"

#include <math.h>

//image constants
#define WIDTH 500
#define HEIGHT 500

//circle constants
#define RADIUS 200
#define CENTER_X (WIDTH / 2)
#define CENTER_Y (HEIGHT / 2)
#define CIRCLE_COLOR_R 255
#define CIRCLE_COLOR_G 0
#define CIRCLE_COLOR_B 0

double distance(double x1, double y1, double x2, double y2)
{
    double y_diff = y2 - y1;
    double x_diff = x2 - x1;
    return sqrt(y_diff * y_diff + x_diff * x_diff);
}

int main()
{
    ppm_image_t *output_image = ppm_create(WIDTH, HEIGHT);

    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            if (distance(col, row, CENTER_X, CENTER_Y) < RADIUS)
            {
                ppm_set_rgb(output_image, row, col, CIRCLE_COLOR_R, CIRCLE_COLOR_G, CIRCLE_COLOR_B);
            }
        }
    }

    ppm_write_to_file(output_image, "circle.ppm");

    ppm_destory(&output_image);
    return 0;
}