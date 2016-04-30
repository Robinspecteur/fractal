#include <stdlib.h>
#include "fractal.h"

struct fractal *fractal_new(int width, int height, double a, double b)
{
    fractal *newFract = (fractal*)malloc(sizeof(fractal));
    if(newFract)
    {
      newFract->width = width;
      newFract->height = height;
      newFract->a = a;
      newFract->b = b;
      /*
      Problème pour gérer le nom du fractal
      Problème pour gérer le tableau pixel

      */
      return newFract;


    }
     else
     {
       return NULL;
     }
}

void fractal_free(struct fractal *f)
{
    if (f)
    {
      free(f)
    }
}

int fractal_get_value(const struct fractal *f, int x, int y)
{
    /* TODO */
    return 0;
}

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
    /* TODO */
}

int fractal_get_width(const struct fractal *f)
{
    /* TODO */
    return 0;
}

int fractal_get_height(const struct fractal *f)
{
    /* TODO */
    return 0;
}

double fractal_get_a(const struct fractal *f)
{
    /* TODO */
    return 0;
}

double fractal_get_b(const struct fractal *f)
{
    /* TODO */
    return 0;
}
