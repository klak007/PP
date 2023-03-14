#include "functions.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define MAX 800           
#define LINE_LENGTH 1024

int read_file_v2(int **&tab_image_arr_in, int **&tab_image_arr_out, int *width, int*height, int *grey_scale, char *image_file_name) {
  char buf[LINE_LENGTH];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int aux_char;                /* zmienna pomocnicza do czytania komentarzy */
  int end_of_image_data=0;            /* czy napotkano end_of_image_data danych w image_fileu */
  int i,j;
  FILE *image_file;
/* Wczytanie zawartosci wskazanego image_fileu do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s",image_file_name);
  image_file=fopen(image_file_name,"r");
  /*Sprawdzenie czy podano prawidłowy uchwyt image_fileu */
  if (image_file==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(-1);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,LINE_LENGTH,image_file)==NULL)   /* Wczytanie pierwszej linii image_fileu do bufora */
    end_of_image_data=1;                              /* Nie udalo sie? end_of_image_data danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || end_of_image_data) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Błąd: To nie jest plik PGM\n");
    fclose(image_file);
    return(-2);
  }

  /* Pominiecie komentarzy */
  do {
    if ((aux_char=fgetc(image_file))=='#') {         /* Czy linia rozpoczyna sie od aux_charu '#'? */
      if (fgets(buf,LINE_LENGTH,image_file)==NULL)  /* Przeread_file ja do bufora                */
	end_of_image_data=1;                   /* Zapamietaj ewentualny end_of_image_data danych */
    }  else {
      ungetc(aux_char,image_file);                   /* Gdy przeczytany aux_char z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (aux_char=='#' && !end_of_image_data);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil end_of_image_data danych         */

  /* Pobranie wymiarow image_arr i liczby odcieni grey_scale */
  if (fscanf(image_file,"%d %d %d",width,height,grey_scale)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow tablicy lub liczby stopni szarosci\n");
    fclose(image_file);
    return(-3);
  }
  // Alokowanie pamieci dla tablicy dwuwymiarowe
  tab_image_arr_in = new int *[*height];
  tab_image_arr_out = new int *[*height];
  for ( int i = 0; i < *height; ++i )
  {
    tab_image_arr_in[i] = new int [*width];
    tab_image_arr_out[i] = new int [*width];
  }
  /* Pobranie image_arru i zapisanie w tablicy tab_image_arr_in*/
  for (i=0;i<*height;i++) {
    for (j=0;j<*width;j++) {
      if (fscanf(image_file,"%d",&(tab_image_arr_in[i][j]))!=1) {
        fprintf(stderr,"Blad: Niewlasciwe wymiary tablicy\n");
        fclose(image_file);
        return(-4);
      }
    }
  }
  fclose(image_file);
  fprintf(stderr,"width: %d , height: %d",*width,*height);

  return *width**height;
}


int write_file_v2(int **tab_image_arr_in,int *width,int *height, int *grey_scale, char *image_file_name)
{
  int row, column;
  int written=0;
  FILE *image_file;
  

  /* Wczytanie zawartosci wskazanego image_fileu do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s",image_file_name);
  image_file=fopen(image_file_name,"w");
  /*Sprawdzenie czy podano prawidłowy uchwyt image_fileu */
   
  written+=fprintf(image_file,"P2\n#converted file\n");
  written+=fprintf(image_file,"%d %d\n%d\n",*width,*height,*grey_scale);
     
    
  for(row=0;row<*height;row++)
  {
    for(column=0;column<*width;column++)
    {
      written+=fprintf(image_file, "%d ",tab_image_arr_in[row][column]);
    }
    written+=fprintf(image_file, "\n");
  }
  if (!(fclose(image_file))) return written;
  else
    return 0;
}


int negative_v2(int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height, int *grey_scale)
{
  int row, column;
  
  for(row=0;row<*height;row++)
  {
    for(column=0;column<*width;column++)
    {
      tab_image_arr_out[row][column]=*grey_scale-tab_image_arr_in[row][column];
    }
  }
  return 4;
}

int thresholdv2(int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height, int *grey_scale)
{
  int row, column;
  int proc_threshold,value_threshold;

  printf(BLU"Podaj wartosc progowa w procentach, zakres to 0-100: " RESET);
  cin >> proc_threshold;
  

  if(proc_threshold<=100&&proc_threshold>=0)
  {
    value_threshold=(*grey_scale*proc_threshold)/100;

    for(row=0;row<*height;row++)
    {
      for(column=0;column<*width;column++)
      {            
        tab_image_arr_out[row][column]=(tab_image_arr_in[row][column] >= value_threshold)**grey_scale;
      }
    }
    return 5;
  }
  else
  {
    printf(RED"\nWartosc procentowa poza zakresem od 0 do 100\n" RESET);
  }
  return 0;
}

int level_changingv2(int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height, int *grey_scale)
{
  int row, column;
  int proc_level_min,proc_level_max,value_level_min,value_level_max;

  printf(BLU"Podaj wartosc poziomu minimalnego w procentach, zakres to 0-100: \n" RESET);
  cin >> proc_level_min;
  printf(BLU"Podaj wartosc poziomu maksymalnego w procentach, zakres to 0-100: \n" RESET);
  cin >> proc_level_max;    

  if((proc_level_min<=100&&proc_level_min>=0)&&(proc_level_max<=100&&proc_level_max>=0)&&(proc_level_max>proc_level_min))
  {
    value_level_min=(*grey_scale*proc_level_min)/100;
    value_level_max=(*grey_scale*proc_level_max)/100;
    for(row=0;row<*height;row++)
    {
      for(column=0;column<*width;column++)
      {     
      if(tab_image_arr_in[row][column]<=value_level_min)tab_image_arr_out[row][column]=0;
      if(tab_image_arr_in[row][column]>=value_level_max)tab_image_arr_out[row][column]=*grey_scale;  
      if((tab_image_arr_in[row][column]>value_level_min)&&(tab_image_arr_in[row][column]<value_level_max))
      tab_image_arr_out[row][column]=((tab_image_arr_in[row][column]-value_level_min)**grey_scale)/(value_level_max-value_level_min);
      }
    }
    return 6;
  }
  else
  {
    printf(RED"\nWartosc procentowa poza zakresem od 0 do 100\n" RESET);
  }
  return 0;  
}

int blurv2(int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height)
{
  int row, column;
  int blur_radius;
  int current_radius;
  int aux;

  printf(BLU"Podaj wartosc promienia poziomego rozmycia zakres to 1-10: " RESET);
  cin >> blur_radius;

  if(blur_radius>0&&blur_radius<11)
  {
    for(row=0;row<*height;row++)
    {
      for(column=blur_radius;column<*width-blur_radius;column++)
      {
        aux=0;
        for(current_radius=-blur_radius;current_radius<blur_radius+1;current_radius++)aux+=tab_image_arr_in[row][column+current_radius];
        
        tab_image_arr_out[row][column]=aux/(2*blur_radius+1);
      }
    }
    return 7;
  }
  else
  {
    printf(RED"\nWartosc promienia poza zakresem od 1 do 10\n" RESET);
    return 0;
  }
}

int normalizev2(int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height, int *grey_scale)
{
  int row, column;
  int proc_level_min,proc_level_max,value_level_min,value_level_max;
  int lowest_point=*grey_scale, highest_point=0;
  int aux;

  for(row=0;row<*height;row++)
  {
    for(column=0;column<*width;column++)
    {
      if (tab_image_arr_in[row][column]<lowest_point)
      {
        lowest_point=tab_image_arr_in[row][column];
      }
      if (tab_image_arr_in[row][column]>highest_point)
      {
        highest_point=tab_image_arr_in[row][column];
      }
    }
  }
  for(row=0;row<*height;row++)
  {
    for(column=0;column<*width;column++)
    {
      tab_image_arr_out[row][column]=((tab_image_arr_in[row][column]-lowest_point)**grey_scale)/(highest_point-lowest_point);
    }
  }
  return 8;
}

int conversion (int **tab_image_arr_in,int *width,int *height, int *grey_scale, char *image_file_name)
{
  int i,j;
  printf("weszlo");
  

  int row, column;
  int written=0;
  FILE *image_file;
  /* wczytanie nazwy imagefileu do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s",image_file_name);
  image_file=fopen(image_file_name,"w");
   
  written+=fprintf(image_file,"P3\n#converted file\n");
  written+=fprintf(image_file,"%d %d\n%d\n",*width,*height,*grey_scale);
  
  for(row=0;row<*height;row++)
  {
    for(column=0;column<*width;column++)
    {
      written+=fprintf(image_file, "%d %d %d ",tab_image_arr_in[row][column],tab_image_arr_in[row][column],tab_image_arr_in[row][column]);
    }
    written+=fprintf(image_file, "\n");
  }
  return 9;
}

/* image_displayenie image_arru o zadanej nazwie za pomoca programu "display"   */
void image_display(char *image_file_name) {
  char order[LINE_LENGTH];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(order,"display ");  /* konstrukcja polecenia postaci */
  strcat(order,image_file_name);     /* display "file_name_image_fileu" &       */
  strcat(order," &");
  printf("%s\n",order);      /* wydruk kontrolny polecenia */
  system(order);             /* wykonanie polecenia        */
}