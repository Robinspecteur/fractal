#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libfractal/fractal.h"
#include <pthread.h>
#include <semaphore.h>

struct fractal **fract_buffer;
struct fractal *bestfract_buffer;
int maxthreads;
int fract_inserted;
int fract_extracted;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

pthread_mutex_t producteur_mutex;
pthread_mutex_t consommateur_mutex;
int producteur_end;
int consommateur_end;



//transforme un string "fract1 800 800 -0.8 0.4" en une fractale avec les
//caractéristiques correspondantes
//si la ligne commence par "#" ou ne contient rien, renvoie un pointeur null
struct fractal* write_fractal(char* str)
{
  if((str[0]=='#') || str[0]=='\n')
    return NULL;

  const char s[2] = " "; //délimiteur
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

//ajoute ".bmp" à la fin d'un string
char* add_bmp(char* str)
{
  char *name_file = (char *)malloc(256);
  strcpy(name_file, str);
  strncat(name_file, ".bmp", 4);
  return;
}

//print les caractéristiques d'une fractale
void read_fractal(struct fractal* f)
{

  char* name = fractal_get_name(f);
  printf("name :\t\t%s\n", name);
  printf("width :\t\t%d\n", fractal_get_width(f));
  printf("height :\t%d\n", fractal_get_height(f));
  printf("a :\t\t%f\n", fractal_get_a(f));
  printf("b :\t\t%f\n", fractal_get_b(f));
}


//Produceur prend les fractal dans les files et les mets dans le buffer
void insert_item(struct fractal *fract_to_insert)
{
  int i;
  for(i=0; i < 2*maxthreads; i ++)//faux !!!!!!
  {
    printf("test enter insert\n");
    if(fract_buffer[i]==NULL)
    {
      fract_buffer[i] = fract_to_insert;
      read_fractal(fract_buffer[i]);
      fract_inserted ++;
    }
  }
}

// Il y aura peut être un problème de mémoire avec le write_fractal, si oui mettre write fractal dans le consommateur
// et changer toutes les fonctions
void * producteur(void* file)
{
  printf("test producteur\n");
   FILE *input = fopen(file, "r");
   char buf_file[256];
   while(fgets(buf_file,sizeof(buf_file),input))
   {
     printf("test enter file\n");
     printf("buf_file : %s\n", buf_file);
     struct fractal* fract_to_send;
     fract_to_send = write_fractal(buf_file);
     read_fractal(fract_to_send);
     sem_wait(&empty);
     printf("empty\n");
     pthread_mutex_lock(&mutex);

     insert_item(fract_to_send);
     printf("insert\n");
     pthread_mutex_unlock(&mutex);
     sem_post(&full);
   }
   fclose(input);
   pthread_mutex_lock(&producteur_mutex);
   producteur_end ++;
   pthread_mutex_unlock(&producteur_mutex);
   return NULL;

}

struct fractal * extract_item()//l'argument sera un buffer
{
  int i;
  for(i = 0; i < 2*maxthreads; i++)//a changer
  {
    if(!fract_buffer[i])
    {
      fract_extracted ++;
      return fract_buffer[i];
    }
  }

}

void * consommateur(void *flagsD)
{
  //int flag = (int)flagsD;
  struct fractal *best_fractal;
  double best_average = 0;
  int current_average;
  while(*fract_buffer)
  {

    struct fractal *fract_to_read;

    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    fract_to_read  = extract_item();
    printf("extract_item");
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    current_average = fractal_get_average(fract_to_read);

    //S'active si on a inclut -d dans les commandes faut gérer l'ajout de .bmp
  /*  if(flag == 1)
    {
      write_bitmap_sdl(fract_to_read, fractal_get_name(fract_to_read));
    }
*/

    if(best_average <= current_average)
    {
      best_fractal = fract_to_read;
      best_average = current_average;
    }

    fractal_free(fract_to_read);

  }
  bestfract_buffer = best_fractal;
  pthread_mutex_lock(&consommateur_mutex);
  consommateur_end ++;
  pthread_mutex_unlock(&consommateur_mutex);
  return NULL;
}

int main(int argv, char *argc[])
{
  int err;
  fract_inserted = 0;
  fract_extracted;
  maxthreads = 1; //à changer par maxthreads d'argument
  int nombre = argv;
  int* flagsD = 0;
  int i = 0;
  int j;
  int count = 1;
  int consommateur_end = 0;

/*  for(i = 0; i < nombre ; i++)
  {
    if(strcmp(argc[i],"-d") == 0)
    {
      flagsD ++;
      //count ++;
    }
    else if(strcmp(argc[i],"--maxthreads") == 0)
    {
      maxthreads = atoi(argc[i+1]);
      //count = count + 2;
    }
  }*/
  fract_buffer =(struct fractal**)malloc(2*maxthreads*sizeof(struct fractal*));
  bestfract_buffer = (struct fractal*)malloc(sizeof(struct fractal));
  pthread_t thread_consomateur[nombre - count];
  pthread_t thread_producteur[maxthreads];

  err = sem_init(&empty, 0, 2*maxthreads); //s'arranger pour faire avec la taille du maxthreads
  err = sem_init(&full, 0, 0);
  if(err != 0)
  {
    printf("Erreur sem_init");
  }

  for(i =1; i<nombre; i ++)
  {
    printf("test 1\n");
    err = pthread_create(&(thread_producteur[i]), NULL, &producteur, (void*)argc[i]);
    if(err != 0)
    {
      printf("Erreur pthread_create");
    }
  }

  for(j = 0; j < maxthreads; j++)
  {
    printf("test 2\n");
    err = pthread_create(&(thread_consomateur[i]), NULL, &consommateur, (void*)flagsD);
    if(err != 0)
    {
      printf("Erreur pthread_create");
    }

  }
  while(1)
  {
    int end;
    if(producteur_end == nombre - count)
    {
      for (i = 1; i< nombre; i++)
      {
        printf("test 3\n");
        err = pthread_join(thread_consomateur[i], NULL);
        if(err != 0)
        {
          printf("Erreur pthread_join");
        }
      }
      end++;
    }

    if(consommateur_end == maxthreads)
    {
      for (j = 0; j< nombre; j++)
      {
        printf("test 4\n");
        err = pthread_join(thread_producteur[i], NULL);
        if(err != 0)
        {
          printf("Erreur pthread_join");
        }

      }
      end++;

      while(1)
      {
          if(end==2);
          {
              printf("on est arrivé au bout\n");
            return(EXIT_SUCCESS);
          }
      }
    }

  }

}
