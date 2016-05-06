#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libfractal/fractal.h"
#include <pthread.h>
#include <semaphore.h>

struct fractal **fract_buffer;        // Le buffer faisant le lien entre producteur et consommateur
struct fractal *bestfract_buffer;     // Le buffer où est placée la meilleure fractale de chaque consommateur
int maxthreads;                       // Nombre maximal de thread
int fract_inserted;                   // Nombre de fractale insérée dans fract_buffer
int fract_extracted;                  // Nombre de fractale extraite de fract_buffer
int position_prod;                    // place du prod dans le buffer
int position_cons;                    // place du cons dans le buffer
int producteur_end;
int consommateur_end;
int boucle;
int prod_actif;                       // nombre de producteurs actifs
int nb_buffer;                        // nombre d'éléments à traiter dans le buffer

pthread_mutex_t mutex;
sem_t empty;
sem_t full;
pthread_mutex_t producteur_mutex;
pthread_mutex_t consommateur_mutex;


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
  return name_file;
}

//print les caractéristiques d'une fractale
void read_fractal(struct fractal* f)
{
  if(f==NULL)
    printf("Null fractal\n");
  else {
  char* name = fractal_get_name(f);
  printf("name :\t\t%s\n", name);
  printf("width :\t\t%d\n", fractal_get_width(f));
  printf("height :\t%d\n", fractal_get_height(f));
  printf("a :\t\t%f\n", fractal_get_a(f));
  printf("b :\t\t%f\n", fractal_get_b(f));
}
}

void read_fractal_buffer(struct fractal** fract_buffer){
  printf("==============\n");
  printf("Fractal buffer\n");
  printf("==============\n");
  for(int i=0; i<2*maxthreads; i++){
    read_fractal(fract_buffer[i]);
  }
  printf("\n");
}



// Il y aura peut être un problème de mémoire avec le write_fractal, si oui mettre write fractal dans le consommateur
// et changer toutes les fonctions
void * producteur(void* file)
{
   int i = 1;
   FILE *input = fopen(file, "r");
   char buf_file[256];
   while(fgets(buf_file,sizeof(buf_file),input))
   {
     struct fractal* fract_to_send = (struct fractal *) malloc(sizeof(fract_to_send));
     fract_to_send = write_fractal(buf_file);

     sem_wait(&empty);
     pthread_mutex_lock(&mutex);

     position_prod = position_prod % (2*maxthreads);
     if(fract_buffer[position_prod]==NULL){
       fract_buffer[position_prod] = fract_to_send;
       nb_buffer++;
     }
     position_prod++;

     pthread_mutex_unlock(&mutex);
     sem_post(&full);
     printf("producteur %d\n", i);
     //free(fract_to_send);
     i ++;
   }
   fclose(input);
   pthread_mutex_lock(&producteur_mutex);
   producteur_end ++;
   pthread_mutex_unlock(&producteur_mutex);
   return NULL;

}


void * consommateur()
{
  int i = 1;
  double best_average = 0;
  struct fractal *best_fractal;
  double current_average;
  //printf("position_cons : %d\n", position_cons);
  //read_fractal(fract_buffer[position_cons]);
  printf("nb_buffer : %d\tprod_actif : %d", nb_buffer, prod_actif);
  while(nb_buffer>0 || prod_actif>0)
  {
    struct fractal *fract_to_read;
    printf("consommateur\n");
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    printf("consommateur mutex\n");
    position_cons = position_cons % (2*maxthreads);
    if(fract_buffer[position_cons]!=NULL)
    {
      printf("\nfract_buffer[%d] :\n", position_cons);
      read_fractal(fract_buffer[position_cons]);
      fract_to_read = fract_buffer[position_cons];
      fract_buffer[position_cons] = NULL;
      nb_buffer--;
    }

    position_cons++;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    current_average = fractal_get_average(fract_to_read);
    printf("current average %f\n", current_average );
    i++;
    //S'active si on a inclut -d dans les commandes faut gérer l'ajout de .bmp
  /*  if(flag == 1)
    {
      write_bitmap_sdl(fract_to_read, fractal_get_name(fract_to_read));
    }
  */
    if(best_average < current_average)
    {
      best_fractal = fract_to_read;
      best_average = current_average;
      printf("new best average %f\n", best_average);
    }

  //fractal_free(fract_to_read);

  }
  bestfract_buffer = best_fractal;
  pthread_mutex_lock(&consommateur_mutex);
  consommateur_end ++;
  pthread_mutex_unlock(&consommateur_mutex);
  read_fractal(best_fractal);
  return NULL;
}

int main(int argv, char *argc[])
{
  boucle = 0;
  int err;
  fract_inserted = 0;
  fract_extracted = 0;
  maxthreads = 1;    //à changer par maxthreads d'argument
  int* flagsD = 0;   // 0 si l'option -d est désactivée, 1 si activée
  int i = 0;
  int j;
  int count = 1;
  int consommateur_end = 0;
  int position_cons =0;                    // place du cons dans le buffer
  int position_prod = 0;
  consommateur_end = 0;
  producteur_end = 0;
  prod_actif = 0;                       // nombre de producteurs actifs
  nb_buffer = 0;

/*  for(i = 0; i < argv ; i++)
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
  fract_buffer = (struct fractal**)malloc(2*maxthreads*sizeof(struct fractal*));
  bestfract_buffer = (struct fractal*)malloc(sizeof(struct fractal));
  pthread_t thread_consommateur[argv - count];
  pthread_t thread_producteur[maxthreads];
  struct fractal *fract_buffer[2*maxthreads];

  err = sem_init(&empty, 0, 2*maxthreads); //s'arranger pour faire avec la taille du maxthreads
  if(err != 0)
    printf("Erreur sem_init");
  err = sem_init(&full, 0, 0);
  if(err != 0)
    printf("Erreur sem_init");

  // Création des threads producteurs, égal au nombre de fichiers d'entrée
  for(i =1; i<argv; i ++)
  {
    printf("Création producteur %x\n", i);
    prod_actif++;
    err = pthread_create(&(thread_producteur[i]), NULL, &producteur, (void*)argc[i]);
    if(err != 0)
      printf("Erreur pthread_create producteur");
  }

  // Création des threads consommateurs, égal au nombre maximal de threads
  for(j = 0; j < maxthreads; j++)
  {
    printf("Création consommateur %x\n", j);
    err = pthread_create(&(thread_consommateur[j]), NULL, &consommateur,(void*)flagsD);
    if(err != 0)
      printf("Erreur pthread_create consommateur");
  }


  while(1)
  {
    int end;

    // Lorsque tous les threads producteurs ont fini, on les termine
    if(producteur_end == argv - count)
    {
      err = pthread_mutex_destroy(&producteur_mutex);
      if(err != 0)
        printf("Erreur mutex_destroy producteur");
      producteur_end --;
      for (i = 1; i< argv; i++)
      {
        printf("fin thread producteur\n");
        err = pthread_join(thread_producteur[i], NULL);
        prod_actif--;
        if(err != 0)
          printf("Erreur pthread_join producteur");
      }

      sem_wait(&empty);
      pthread_mutex_lock(&mutex);

      //read_fractal_buffer(fract_buffer);
      pthread_mutex_unlock(&mutex);
      sem_post(&full);

      end++;
    }

    // Lorsque tous les threads consommateurs ont fini, on les termine
    if(consommateur_end == maxthreads)
    {
      err = pthread_mutex_destroy(&consommateur_mutex);
      if(err != 0)
        printf("Erreur mutex_destroy consommateur");
      for (j = 0; j< maxthreads; j++)
      {
        printf("fin thread consommateur\n");
        err = pthread_join(thread_consommateur[j], NULL);
        printf("test 5\n");
        if(err != 0)
          printf("Erreur pthread_join consommateur");
      }
      end++;

      if(end==2);
        {
          printf("on est arrivé au bout\n");
          return(EXIT_SUCCESS);
       }
    }
  }

}
