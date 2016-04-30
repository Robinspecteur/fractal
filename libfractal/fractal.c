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
      newFract->pixel = malloc(a *sizeof(*pixel));//Un bug peut peut-être venir de la
      int i;
      for(i=0; i < a; i++)
      {
        newFract->pixel[i]= malloc(b*sizeof(*(pixel[i])));
      }

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
      free(f); //Peut être changer le free si il y a une couille dans notre libèrations
      //de mêmoire https://openclassrooms.com/courses/tableaux-pointeurs-et-allocation-dynamique
    }
}

int fractal_get_value(const struct fractal *f, int x, int y)
{
    /* TODO */
    return 0;
}

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
    int *width;
    int *height;
    &width = &(f->
}

int fractal_get_width(const struct fractal *f)
{
    return f->width;
}

int fractal_get_height(const struct fractal *f)
{
    return f->height;
}

double fractal_get_a(const struct fractal *f)
{
    return f->a;
}

double fractal_get_b(const struct fractal *f)
{
    return f->b;
}
