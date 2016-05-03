#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libfractal/fractal.h"


int main(int argv, char *argc[])
{
 int i = 0;
  int j = 0;
  const char *image = "image";
  struct fractal* fract_test = (struct fractal *)fractal_new(800,800,-0.6,0.6);
  int width = fractal_get_width(fract_test);
  int height = fractal_get_height(fract_test);

  for (i=0; i< width; i++)
  {
    for (j=0; j < height; j++)
    {
    fractal_compute_value(fract_test,i,j);
    }
  }
  printf("Largeur de l'image : %d\n", fract_test->width);
  printf("fractal_get_width : %d\n", fractal_get_width(fract_test));
  int x = write_bitmap_sdl(fract_test, image);
  printf("Valeur de write_bitmap_sdl : %d\n", x);
  fractal_free(fract_test);
  return(EXIT_SUCCESS);
}
