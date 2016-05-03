#include <stdlib.h>
#include <stdio.h>
#include "fractal.h"

struct fractal *fractal_new(int width, int height, double a, double b)
{
    fractal *newFract = (fractal*)malloc(sizeof(fractal));
    if(newFract)
    {
			int **ptr;
      newFract->width = width;
      newFract->height = height;
      newFract->a = a;
      newFract->b = b;
      newFract->pixel = (int**)malloc(height *sizeof(*ptr));//Un bug peut peut-être venir de la
      int i;
      for(i=0; i < height ; i++)
      {
        (newFract->pixel)[i]= (int*)malloc(width*sizeof(**ptr));
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
      for (int i = 0; i < fractal_get_height(f); i++)
      {
        free((f->pixel)[i]);
      }
      free(f->pixel);
      free(f);
    }
}

/*int fractal_get_value(const struct fractal *f, int x, int y)
{

  int width = fractal_get_width(f);
  int height = fractal_get_height(f);
  if (x > width)
  {
    printf("%s\n","x too big");
  }

  else if (y > height)
  {
    printf("%s\n","y too big");
  }

  else
  {
    int **tab = f->pixel;
    if (tab[x][y] == 0)
    {
      return EXIT_FAILURE;
    }
    else
    {
      return tab[x][y];
    }
  }
  return EXIT_FAILURE;
}
*/
void fractal_set_value(struct fractal *f, int x, int y, int val)
{
    int width = fractal_get_width(f);
    int height = fractal_get_height(f);

    if (x > width)
    {
      printf("%s\n","x too big");
    }

    else if (y > height)
    {
      printf("%s\n","y too big");
    }

    else
    {
      int **tab = f->pixel;
      tab[x][y]=val;
    }
}


int fractal_get_value(const struct fractal *f, int x, int y)
{
    return (f->pixel)[x][y];
}

/*void fractal_set_value(struct fractal *f, int x, int y, int val)
{
  printf("test6\n");
    (f->pixel)[x][y] = val;
    ptintf("test6bis\n");
}
*/

int fractal_get_width(const struct fractal *f)
{
    int x = f->width;
    return x;
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
