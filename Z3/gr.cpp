#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
// deklaracja kolorów użytych do menu, wartości i długości linii
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define MAX 800           
#define LINE_LENGTH 1024


int read_file(int image_arr_pgm[MAX][MAX],int *width,int *height, int *grey_scale, char *image_file_name) {
  char buf[LINE_LENGTH];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int aux_char;                /* zmienna pomocnicza do czytania komentarzy */
  int end_of_image_data=0;            /* czy napotkano koniec danych w pliku */
  int i,j;
  FILE *image_file;
  

  /* Wczytanie zawartosci wskazanego pliku do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s",image_file_name);
  image_file=fopen(image_file_name,"r");
  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (image_file==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(-1);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,LINE_LENGTH,image_file)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    end_of_image_data=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || end_of_image_data) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Błąd: To nie jest plik PGM\n");
    fclose(image_file);
    return(-2);
  }

  /* Pominiecie komentarzy */
  do {
    if ((aux_char=fgetc(image_file))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,LINE_LENGTH,image_file)==NULL)  /* Przeczytaj ja do bufora                */
	end_of_image_data=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(aux_char,image_file);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (aux_char=='#' && !end_of_image_data);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow tablicy i liczby odcieni szarości */
  if (fscanf(image_file,"%d %d %d",width,height,grey_scale)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow tablicy lub liczby stopni szarosci\n");
    fclose(image_file);
    return(-3);
  }
  /* Pobranie pliku i zapisanie w tablicy obrazu*/
  for (i=0;i<*height;i++) {
    for (j=0;j<*width;j++) {
      if (fscanf(image_file,"%d",&(image_arr_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary tablicy\n");
    fclose(image_file);
	return(-4);
      }
    }
  }
  fclose(image_file);
  return *width**height;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

int write_file(int image_arr_pgm[MAX][MAX],int *width,int *height, int *grey_scale, char *image_file_name)
{
  int row, column;
  int written=0; // potrzebne do poprawnego kolorowania pierwszej opcji w menu
  FILE *image_file;
  

  /* Wczytanie zawartosci wskazanego pliku do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s",image_file_name);
  image_file=fopen(image_file_name,"w");
  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
   
  written+=fprintf(image_file,"P2\n#converted file\n");           // zapis posiadający napis magiczny P2 i plik przekonwertowany
  written+=fprintf(image_file,"%d %d\n%d\n",*width,*height,*grey_scale); // zapis szerokości, wysokości i skali szarości
     
  // dwie pętle potrzebne do przejścia całej tablicy obrazy
  for(row=0;row<*height;row++)
  {
    for(column=0;column<*width;column++)
    {
      written+=fprintf(image_file, "%d ",image_arr_pgm[row][column]);
    }
    written+=fprintf(image_file, "\n");
  }
  if (!(fclose(image_file))) return written;
  else
    return 0;
}
// funkcja tworząca negatyw obrazu
int negative( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height, int *grey_scale)
{
  int row, column;
  
  for(row=0;row<*height;row++)
  {
    for(column=0;column<*width;column++)
    {
      image_arr_out[row][column]=*grey_scale-image_arr_in[row][column];  // formuła negatywu
    }
  }
  return 4;
}
// funkcja tworząca progowanie obrazu
int threshold( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height, int *grey_scale)
{
  int row, column;
  int proc_threshold,value_threshold;

  printf(BLU"Podaj wartosc progowa w procentach, zakres to 0-100: "RESET);
  cin >> proc_threshold;
  

  if(proc_threshold<=100&&proc_threshold>=0)
  {
    value_threshold=(*grey_scale*proc_threshold)/100;

    for(row=0;row<*height;row++)
    {
      for(column=0;column<*width;column++)
      {            
        image_arr_out[row][column]=(image_arr_in[row][column] >= value_threshold)**grey_scale;
      }
    }
    return 5;
  }
  else
  {
    printf(RED"\nWartosc procentowa poza zakresem od 0 do 100\n"RESET);
  }
  return 0;
}
// funkcja zmieniająca poziom obrazu
int level_changing( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height, int *grey_scale)
{
  int row, column;
  int proc_level_min,proc_level_max,value_level_min,value_level_max;

  printf(BLU"Podaj wartosc poziomu minimalnego w procentach, zakres to 0-100: \n"RESET);
  cin >> proc_level_min;
  printf(BLU"Podaj wartosc poziomu maksymalnego w procentach, zakres to 0-100: \n"RESET);
  cin >> proc_level_max;    

  if((proc_level_min<=100&&proc_level_min>=0)&&(proc_level_max<=100&&proc_level_max>=0)&&(proc_level_max>proc_level_min))
  {
    value_level_min=(*grey_scale*proc_level_min)/100;
    value_level_max=(*grey_scale*proc_level_max)/100;
    for(row=0;row<*height;row++)
    {
      for(column=0;column<*width;column++)
      {     
      if(image_arr_in[row][column]<=value_level_min)image_arr_out[row][column]=0;
      if(image_arr_in[row][column]>=value_level_max)image_arr_out[row][column]=*grey_scale;  
      if((image_arr_in[row][column]>value_level_min)&&(image_arr_in[row][column]<value_level_max))
      image_arr_out[row][column]=((image_arr_in[row][column]-value_level_min)**grey_scale)/(value_level_max-value_level_min);
      }
    }
    return 6;
  }
  else
  {
    printf(RED"\nWartosc procentowa poza zakresem od 0 do 100\n"RESET);
  }
  return 0;  
}
// funkcja rozmywająca obraz
int blur( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height)
{
  int row, column;
  int blur_radius;
  int current_radius;
  int aux;

  printf(BLU"Podaj wartosc promienia poziomego rozmycia zakres to 1-10: "RESET);
  cin >> blur_radius;

  if(blur_radius>0&&blur_radius<11)
  {
    for(row=0;row<*height;row++)
    {
      for(column=blur_radius;column<*width-blur_radius;column++)
      {
        aux=0;
        for(current_radius=-blur_radius;current_radius<blur_radius+1;current_radius++)aux+=image_arr_in[row][column+current_radius];
        
        image_arr_out[row][column]=aux/(2*blur_radius+1);
      }
    }
    return 7;
  }
  else
  {
    printf(RED"\nWartosc promienia poza zakresem od 1 do 10\n"RESET);
    return 0;
  }
}
// funkcja rozciągająca histogram obrazu
int normalize( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height, int *grey_scale)
{
  int row, column;
  int proc_level_min,proc_level_max,value_level_min,value_level_max;
  int lowest_point=*grey_scale, highest_point=0;
  int aux;

  for(row=0;row<*height;row++)
  {
    for(column=0;column<*width;column++)
    {
      if (image_arr_in[row][column]<lowest_point)
      {
        lowest_point=image_arr_in[row][column]; // szukanie punktu o najniższym poziomie szarości
      }
      if (image_arr_in[row][column]>highest_point)
      {
        highest_point=image_arr_in[row][column]; // szukanie punktu o najwyższym poziomie szarości
      }
    }
  }
  for(row=0;row<*height;row++)
  {
    for(column=0;column<*width;column++)
    {
      image_arr_out[row][column]=((image_arr_in[row][column]-lowest_point)**grey_scale)/(highest_point-lowest_point); // formuła normalizacji obrazu
    }
  }
  return 8;
}

/* wyświetlenie  pliku o zadanej nazwie za pomoca programu "display"   */
void image_display(char *image_file_name) {
  char order[LINE_LENGTH];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(order,"display ");  /* konstrukcja polecenia postaci */
  strcat(order,image_file_name);     /* wyświetl nazwe pliku */
  strcat(order," &");
  printf("%s\n",order);      /* wydruk kontrolny polecenia */
  system(order);             /* wykonanie polecenia        */
}

int main() {
  int image_arr_in[MAX][MAX], image_arr_out[MAX][MAX] ;
  int width,height,grey_scale_depth;
  int file_input_status=-1;
  int file_output_status=-1;
  int conversion_done=0;
  int ret_value;  // wartość zwracana przez operację graficzną
  int conversion_done_arr[10]={0,0,0,0,0,0,0,0,0,0}; // tablica operacji dokonanych przez użytkownika
  int menu_item;
  // nazwy wykorzystane do czytania i zapisywania i wyświetlania plików
  char file_name_input[100];
  char file_name_output[100];

  do
  {
  // wybór operacji obróbki graficznej
    printf(BLU"Wybierz operacje:\n"RESET);
    if(conversion_done_arr[1])(printf(GRN"1: Otwórz plik źródłowy\n"RESET)); else(printf(WHT"1: Otwórz plik źródłowy\n"RESET));
    if(conversion_done_arr[2])(printf(GRN"2: Zapisz plik wynikowy\n"RESET)); else(printf(WHT"2: Zapisz plik wynikowy\n"RESET));
    if(conversion_done_arr[3])(printf(GRN"3: Wyświetl obraz źródłowy i wynikowy\n"RESET)); else(printf(WHT"3: Wyświetl obraz źródłowy i wynikowy\n"RESET));
    if(conversion_done_arr[4])(printf(GRN"4: Negatyw\n"RESET)); else(printf(WHT"4: Negatyw\n"RESET));
    if(conversion_done_arr[5])(printf(GRN"5: Progowanie\n"RESET)); else(printf(WHT"5: Progowanie\n"RESET));
    if(conversion_done_arr[6])(printf(GRN"6: Zmiana poziomów\n"RESET)); else(printf(WHT"6: Zmiana poziomów\n"RESET));
    if(conversion_done_arr[7])(printf(GRN"7: Rozmywanie poziome\n"RESET)); else(printf(WHT"7: Rozmywanie poziome\n"RESET));
    if(conversion_done_arr[8])(printf(GRN"8: Rozciąganie histogramu\n"RESET)); else(printf(WHT"8: Rozciąganie histogramu\n"RESET));

    printf(BLU"0: Zakończ program\n"RESET);
    // menu
    scanf("%d", &menu_item);
    switch (menu_item)
    {
      case 1: //otwieranie pliku źródłowego
        if ((file_input_status = read_file(image_arr_in,&width,&height,&grey_scale_depth, file_name_input))>0)conversion_done_arr[1]=1;
        break;
      case 2: // zapisywanie pliku wynikowego
        if ((conversion_done)&&((file_output_status = write_file(image_arr_out,&width,&height,&grey_scale_depth, file_name_output))>0))conversion_done_arr[2]=1;
        break;
      case 3: // wyświetlanie obrazu źródłowego i wynikowego
        if ((file_input_status > 0)&&(file_output_status>0))
        {
          image_display(file_name_input);
          image_display(file_name_output);
          conversion_done_arr[3]=1;
        }
        break;
      case 4: // operacja negatywu
        if(conversion_done_arr[1]&&(conversion_done=(ret_value=negative( image_arr_in, image_arr_out, &width, &height, &grey_scale_depth)>0)))conversion_done_arr[4]=1;
        break;
      case 5: //operacja progowanie
        if(conversion_done_arr[1]&&(conversion_done=(ret_value=threshold( image_arr_in, image_arr_out, &width, &height, &grey_scale_depth)>0)))conversion_done_arr[5]=1;
        break;
      case 6:// operacja zmiany poziomu
        if(conversion_done_arr[1]&&(conversion_done=(ret_value=level_changing( image_arr_in, image_arr_out, &width, &height, &grey_scale_depth)>0)))conversion_done_arr[6]=1;
        break;
      case 7: // operacja rozmywania poziomego
        if(conversion_done_arr[1]&&(conversion_done=(ret_value=blur( image_arr_in, image_arr_out, &width, &height)>0)))conversion_done_arr[7]=1;
        break;
      case 8: // operacja normalizacji
        if(conversion_done_arr[1]&&(conversion_done=(ret_value=normalize( image_arr_in, image_arr_out, &width, &height, &grey_scale_depth)>0)))conversion_done_arr[8]=1;
        break;
      case 0: // wyjście z programu 
        printf(BLU"Koniec programu\n"RESET);
        break;
    }
  } while (menu_item!=0);
  
  return 0;
}