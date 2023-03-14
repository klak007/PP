#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// funkcja signum zwraca 1, gdy x > 0; zwraca 0, gdy x = 0; zwraca -1, gdy x < 0
int signum(double x) 
{
    if (x>0) return 1; 
    else if (x==0) return 0;
    else return -1;
}

int main ()
{
    FILE * data_file; // wskaźnik na plik
    char cline[50];  // tablica na ignorowany czas 
    int sample_index = 0,polarity_change_index = 0; // indeksy próbek, indeksy zmiany znaku
    double value,value_prev,hr; //wartości czytane z pliku, wartość jaka jest w poprzedniej linijce, 
    // by móc dowiedzieć sie czy zachodzi między tymi dwoma wartosciami przejście przez zero, hr -> heart rate 
    
    data_file = fopen ("1.txt", "r");       //otwieranie pliku
    while ( ! feof (data_file) )            // czytanie pliku
    {
        fscanf (data_file,"%s %lf\n",cline,&value); //format linijki
    
        sample_index++;
                    
        if (sample_index % 100 == 0) //grupowanie 100 próbek
        {
            hr = polarity_change_index * 6;
            if ((hr >= 50) && (hr <= 80)) cout << "hr=" << hr << "\n"; //wartości graniczne tetna
            else cout << "wartosc hr niepoprawna \n";         // jeśli hr się w nich nie mieści, hr jest niepoprawne
            polarity_change_index = 0;      
            sample_index = 0;
        }
        if(value != 99)         //warunkowy koniec programu
        {
            if ((sample_index > 1) && (signum(value) * signum(value_prev) < 0)) polarity_change_index ++;

            if (signum(value) != 0) value_prev = value;
        }
    }
    fclose (data_file); //zamknięcie pliku
    return 0;
}