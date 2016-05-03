#include <stdlib.h>
#include <stdio.h>
#include "fractal.h"

struct fractal *fractal_new(char *name, int width, int height, double a, double b)
{
    fractal *newFract = (fractal*)malloc(sizeof(fractal));
    if(newFract)
    {
			int **ptr;
      char *string = (char*)malloc(sizeof(*name));
      string = name;
      newFract->name = string;
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

int fractal_get_average(struct fractal *f)
{
  int i;
  int j;
  int width = fractal_get_width(f);
  int height = fractal_get_height(f);
  int sum = 0;
  for (i=0; i< width; i++)
  {
    for (j=0; j < height; j++)
    {
    sum = sum + fractal_get_value(f,i,j);
    }
  }
  double average = (double) (sum/(width*height));
  return average;
}

int fractal_get_value(const struct fractal *f, int x, int y)
{

  int width = fractal_get_width(f);
  int height = fractal_get_height(f);
  if (x > width || x < 0)
  {
    printf("%s\n","x out of bound");
  }

  else if (y > height || x < 0)
  {
    printf("%s\n","y out of bound");
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

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
    int width = fractal_get_width(f);
    int height = fractal_get_height(f);

    if (x > width || x < 0)
    {
      printf("%s\n","x out of bound");
    }

    else if (y > height || x < 0)
    {
      printf("%s\n","y out of bound");
    }


    else
    {
      int **tab = f->pixel;
      tab[x][y]=val;
    }
}

char *fractal_get_name(const struct fractal *f)
{
  return f->name;
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
