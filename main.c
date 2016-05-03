#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libfractal/fractal.h"

//transforme un string "fract1 800 800 -0.8 0.4" en une fractale avec les
//caractéristiques correspondantes
fractal* write_fract(char* str) {
  const char s[2] = " "; //délimiteur
  char* str2= (char *)malloc(sizeof(*str2));
  strcpy(str2, str);
  char* name = strtok(str2, s);
  //printf("%s\n", name);
  int width = atoi(strtok(NULL, s));
  int height = atoi(strtok(NULL, s));
  double a = atof(strtok(NULL, s));
  double b = atof(strtok(NULL, s));
  free(str2);
  struct fractal *f  = (struct fractal *)fractal_new(name,width,height,a,b);
  return f;
}

//transforme un fichier de caract de fractales en tableau de fractal
struct fractal** file_to_fract(FILE *input) {
  char buf[256];
  printf("Test 1\n");
  fractal** fract_array = (fractal**) malloc(sizeof(**fract_array));
  printf("Test 2\n");
  fprintf("buf : ")
  //for (size_t i = 0; fgets(buf, sizeof(buf), input); i++) {
    fract_array[0]=write_fract(buf);
    printf("Test 3\n");
  //}

  if (ferror(input)) {
    fprintf(stderr,"Oops, error reading stdin\n");
    abort();
  }
  return fract_array;
}

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
  //FILE *input = fopen(argc[1], "r");
  //struct fractal *fract_test = file_to_fract(input)[0];
  /*

  struct fract** fract_table = file_to_fract(input);
  char* str = "fract1 800 400 -0.8 0.5";
  struct fractal* fract_test = write_fract(str);
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
