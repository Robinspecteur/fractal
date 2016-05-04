/*  int i;
  for(i =0; i<10000; i++)
  {
    struct fractal *fract = write_fractal("fractal 2 800 800 -0.5 -0.5");
    printf("Adresse 2:\t%p\n", &fract);
    free(fract);
  }
  */
/*  FILE *input = fopen(argc[1], "r");
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
    compute(current_fract);
    printf("Average n°%d :\t%f\n", i, fractal_get_average(current_fract));
    char* name = (char*)fractal_get_name(current_fract);
    write_bitmap_sdl(current_fract, name);
    if(fractal_get_average(current_fract)>best_average)
    {
      best_fract = current_fract;
      best_average = fractal_get_average(best_fract);
    }

    fractal_free(current_fract);
    i++;
  }
  read_fract(best_fract);
*/

/*
//transforme un fichier de caract de fractales en tableau de fractal
struct fractal** file_to_fract(FILE *input) {
  char buf[256];
  //printf("Test 1\n");
  fractal** fract_array = (fractal**) malloc(sizeof(**fract_array));
  //printf("Test 2\n");
  fgets(buf, sizeof(buf), input);
  printf("buf : %s", buf);

  for (int i = 0; fgets(buf, sizeof(buf), input); i++) {mais
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

/*
//prend un fichier contenant une liste de fractale, donne la fractale à la plus
//grande moyenne
struct fractal* best_fractal(FILE *input){
  char buf[1024];
  struct fractal* best_fractal; //la fractale avec la plus grande valeur moyenne
  int i = 0;
  double best_average = 0;

  while (fgets(buf, sizeof(buf), input))
  {
    struct fractal* current_fract; //la fractale qu'on calcule
    current_fract = write_fractal(buf);
    read_fractal(current_fract);
    double current_average = fractal_get_average(current_fract);
    printf("current average :\t%f\n", current_average);
    if(current_average>best_average)
    {
      best_fractal = current_fract;
      best_average = current_average;
      printf("new best average :\t%f\n", best_average);
    }
    i++;
  }
  return best_fractal
}
*/
