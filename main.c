#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libfractal/fractal.h"



//transforme un string "fract1 800 800 -0.8 0.4" en une fractale avec les
//caractéristiques correspondantes
struct fractal* write_fractal(char* str) {
  const char s[2] = " ";
  char* str2= (char *)malloc(256);
  strcpy(str2, str);
  char* name = strtok(str2, s);
  int width = atoi(strtok(NULL, s));
  int height = atoi(strtok(NULL, s));
  double a = atof(strtok(NULL, s));
  double b = atof(strtok(NULL, s));
  free(str2);
  struct fractal *f = fractal_new(name, width, height, a, b);
  return f;
}

//print les caractéristiques d'une fractale
void read_fract(struct fractal* f)
{
  char* name = fractal_get_name(f);
  printf("name :%s\n", name);
  printf("width :%d\n", fractal_get_width(f));
  printf("height :%d\n", fractal_get_height(f));
  printf("a :%f\n", fractal_get_a(f));
  printf("b :%f\n", fractal_get_b(f));
}

//Produceur prend les fractal dans les files et les mets dans le buffer
void insert_item(struct fractal *fract_to_insert)
{
  return EXIT_SUCCESS;
}

// Il y aura peut être un problème de mémoire avec le write_fractal, si oui mettre write fractal dans le consommateur
// et changer toutes les fonctions
void producteur(void* file)
{
   FILE input = (FILE)file;
   char buf_file[256];
   while(fgets(buf,sizeof(buf),input))
   {
     struct fractal* fract_to_send;
     fract_to_send = write_fractal(buf);
     sem_wait(&empty);
     pthread_mutex_lock(&mutex);
     insert_item(fract_to_send);
     pthread_mutex_unlock(&mutex);
     sem_post(&full);
   }
   
}

void extract_item()//l'argument sera un buffer
{
  return EXIT_SUCESS;
}

struct fractal *fract consommateur(void *flagsD)
{
  bool flag = (bool)flagsD;
  struct fractal *best_fractal;
  double best_average = 0;
  while(*buf_fract)
  {
    struct fractal *fract_to_read;

    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    fract_to_read  = extract_item();
    pthread_mutex_unlock(&mutex);

    sem_post(&empty);
    current_average = fractal_get_average(fract_to_read);

    //S'active si on a inclut -d dans les commandes faut gérer l'ajout de .bmp
    if(flagsD)
    {
      write_bitmap_sdl(fract_to_read, fractal_get_name(fract_to_read));
    }


    if(best_average <= current_average)
    {
      best_fractal = fract_to_read;
      best_average = current_average;
    }

    fractal_free(fract_to_read);

  }
  return best_fractal;
}

int main(int argv, char *argc[])
{

  int maxthreads = 1; //à changer par maxthreads d'argument

  pthread_mutex_t mutex;
  sem_init(&empty, 0, 2*maxthreads) //s'arranger pour faire avec la taille du maxthreads
  sem_init(&full, 0, 0);
  struct fractal **buf_fract; //le buffer du fractal mais je sais pas encore comment je vais le gérer
  int nombre = argv;
  bool flagsD = false;
  int i = 0;

  pthread_t = consumer;
  pthread_t = producer;
  /*  for(i = 0; i < nombre ; i++)
  int count = 1;
  {
    if(strcmp(argc[i],"-d") == 0)
    {
      flagsD = true;
      count ++;
    }
    else if(strcmp(argc[i],"--maxthreads") == 0)
    {
      maxthreads = atoi([argc[i+1]);
      count = count + 2;
    }
  }
  nombre = nombre - count;
*/

  for(i =0; i<2; i ++)
  {
    err = pthread_create(&consumer, NULL, &consommateur, (void*)flagsD);
    if(err != 0)
    {
      printf("Erreur pthread_create");
    }

  }


  return(EXIT_SUCCESS);
}
