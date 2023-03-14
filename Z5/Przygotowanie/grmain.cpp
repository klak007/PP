#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include "grconnect.hpp"
using namespace std;
// deklaracja kolorów użytych do menu, wartości i długości linii
#define  RED  "\x1B[31m"
#define  GRN  "\x1B[32m"
#define  BLU  "\x1B[34m"
#define  WHT  "\x1B[37m"
#define  RESET  "\x1B[0m"
#define MAX 800           
#define LINE_LENGTH 1024


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
    printf(  BLU  "Wybierz operacje:\n" RESET );
    if(conversion_done_arr[1])(printf( GRN "1: Otwórz plik źródłowy\n" RESET )); else(printf( WHT "1: Otwórz plik źródłowy\n" RESET ));
    if(conversion_done_arr[2])(printf( GRN "2: Zapisz plik wynikowy\n" RESET )); else(printf( WHT "2: Zapisz plik wynikowy\n" RESET ));
    if(conversion_done_arr[3])(printf( GRN "3: Wyświetl obraz źródłowy i wynikowy\n" RESET )); else(printf( WHT "3: Wyświetl obraz źródłowy i wynikowy\n" RESET ));
    if(conversion_done_arr[4])(printf( GRN "4: Negatyw\n" RESET )); else(printf( WHT "4: Negatyw\n" RESET ));
    if(conversion_done_arr[5])(printf( GRN "5: Progowanie\n" RESET )); else(printf( WHT "5: Progowanie\n" RESET ));
    if(conversion_done_arr[6])(printf( GRN "6: Zmiana poziomów\n" RESET )); else(printf(  WHT  "6: Zmiana poziomów\n" RESET ));
    if(conversion_done_arr[7])(printf( GRN "7: Rozmywanie poziome\n" RESET )); else(printf( WHT "7: Rozmywanie poziome\n" RESET ));
    if(conversion_done_arr[8])(printf( GRN "8: Rozciąganie histogramu\n" RESET )); else(printf( WHT "8: Rozciąganie histogramu\n" RESET ));

    printf( BLU "0: Zakończ program\n" RESET );
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
        printf( BLU "Koniec programu\n" RESET );
        break;
    }
  } while (menu_item!=0);
  
  return 0;
}

