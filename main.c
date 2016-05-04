#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libfractal/fractal.h"

//transforme un string "fract1 800 800 -0.8 0.4" en une fractale avec les
//caractéristiques correspondantes
struct fractal* write_fractal(char* str) {
  const char s[2] = " "; //délimiteur
  char* str2= (char *)malloc(sizeof(*str2));
  strcpy(str2, str);
  char* name = strtok(str2, s);
  int width = atoi(strtok(NULL, s));
  int height = atoi(strtok(NULL, s));
  double a = atof(strtok(NULL, s));
  double b = atof(strtok(NULL, s));
  printf("width :\t'%d' height :\t'%d'\na :\t'%f' b :\t'%f'\n", width, height, a, b);
  //free(str2);
  //printf("free str2\n");
  struct fractal *f = fractal_new(name,width,height,a,b);
  return f;
}

/*
//transforme un fichier de caract de fractales en tableau de fractal
struct fractal** file_to_fract(FILE *input) {
  char buf[256];
  //printf("Test 1\n");
  fractal** fract_array = (fractal**) malloc(sizeof(**fract_array));
  //printf("Test 2\n");
  fgets(buf, sizeof(buf), input);
  printf("buf : %s", buf);

  for (int i = 0; fgets(buf, sizeof(buf), input); i++) {
    printf("Ligne n°%d\n",i);
    fract_array[i]=write_fractal(buf);
    printf("Test\n");
  }

  if (ferror(input)) {
    fprintf(stderr,"Oops, error reading stdin\n");
    abort();
  }
  return fract_array;
}
*/

//print les caractéristiques d'une fractale
void read_fract(struct fractal* f) {
  char* name = fractal_get_name(f);
  printf("name :%s\n", name);
  printf("width :%d\n", fractal_get_width(f));
  printf("height :%d\n", fractal_get_height(f));
  printf("a :%f\n", fractal_get_a(f));
  printf("b :%f\n", fractal_get_b(f));
}

/*
 * compute: met à jour les valeurs d'une fractale h
 *
 * @f: fractale
 */
void compute(struct fractal *f)
{
  int i = 0;
  int j = 0;
  int width = fractal_get_width(f);
  int height = fractal_get_height(f);

  for (i=0; i< width; i++)
  {
    for (j=0; j < height; j++)
    {
    fractal_compute_value(f,i,j);
    }
  }
}

int main(int argv, char *argc[])
{
  struct fractal* fract = write_fractal("fractal1 800 800 0 0");
  printf("Adresse 1:\t%p\n", &fract);
  free(fract);
  fract = write_fractal("fractal2 800 800 -0.5 -0.5");
  printf("Adresse 2:\t%p\n", &fract);

  /*
  FILE *input = fopen(argc[1], "r");
  char buf[1000000];
  //fgets(buf, sizeof(buf), input);
  //printf("Test\n");
  struct fractal* best_fract; //la fractale avec la plus grande valeur moyenne
  int i = 0;
  double best_average = 0;
  //printf("Test\n");
  while (fgets(buf, sizeof(buf), input))
 {
    struct fractal* current_fract; //la fractale qu'on calcule
    printf("Ligne n°%d :\t%s", i, buf);
    current_fract = write_fractal(buf);
    printf("Average n°%d :\t%f\n", i, fractal_get_average(current_fract));

    if(fractal_get_average(current_fract)>best_average)
    {
      best_fract = current_fract;
      printf("Testt\n");
      best_average = fractal_get_average(best_fract);
    }

    fractal_free(current_fract);
    i++;
  }
  read_fract(best_fract);
  */




  //free(fract_test);
  /*

  struct fract** fract_table = file_to_fract(input);
  char* str = "fract1 800 400 -0.8 0.5";
  struct fractal* fract_test = write_fractal(str);
  read_fract(fract_test);
  printf("%s", fract_test->name);
  struct fractal* fract_test = (struct fractal *)fractal_new("au top",800,800,-0.6,0.6);
  compute(fract_test);
  const char *image = fract_test->name;
  int x = write_bitmap_sdl(fract_test, image);
  printf("Valeur de write_bitmap_sdl : %d\n", x);
  fractal_free(fract_test);
*/
  return(EXIT_SUCCESS);
}
