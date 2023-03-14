#include <iostream>

using namespace std;

bool  sort_and_asses(float coords[4]);
bool  enter_data(float cox[4],float coy[4]);

int main()
{
    //tablice koordynatów (odcięte x i rzędne y)
    //prostokąt 1 ma narożniki w punktach (x11,y11) i (x12,y12)
    //prostokąt 2 ma narożniki w punktach (x21,y21) i (x22,y22)
    float arr_coords_x[4] = {1, 1,-6, 4}; // inicjacja danymi przykładowymi x11,x12,x21,x22
    float arr_coords_y[4] = { 1, 1, 0, 9}; // inicjacja danymi przykładowymi y11,y12,y21,y22

    if  (!enter_data(arr_coords_x,arr_coords_y)) return 0;

    
   
    
    //sortowanie koordynatów x i y oraz równoczesna ocena, czy istnieje część wspólna dla odcinków rzutowanych na oś x oraz odcinków rzutowanych na oś y
    if  ( (sort_and_asses (arr_coords_x)) && (sort_and_asses (arr_coords_y)) )
    {
        cout <<"koordynaty czesci wspolnej:\n" ;
        cout << arr_coords_x[1] <<"," << arr_coords_y[1] <<"\n";
        cout << arr_coords_x[2] <<"," << arr_coords_y[2] <<"\n";
    }
    else
    {
        cout <<"brak czesci wspolnej \n" ;        
    }
    
    //  cout<< "posortowane koordynaty x:"<< arr_coords_x[0] <<","<< arr_coords_x[1] <<","<< arr_coords_x[2] << "," << arr_coords_x[3] <<"\n";
    //  cout<< "posortowane koordynaty y:"<< arr_coords_y[0] <<","<< arr_coords_y[1] <<","<< arr_coords_y[2] << "," << arr_coords_y[3] <<"\n";
    return 0;

}
// wprowadzanie danych do tablic koordynatow
bool  enter_data(float cox[4],float coy[4])
{
cout<< "podaj wspolrzedne punktow w kolejnosci x,y\n";
    for(int i=0;i<4;i++)
    {
        cout<< "podaj x["<<i<<"]";
        cin>>cox[i];
        cout<< "podaj y["<<i<<"]";
       
        cin>>coy[i];
        // cout<<"\n";
    }
if(cox[0] == cox[1] || coy[0] == coy[1] || cox[2] == cox[3] || coy[2] == coy[3])
   {
        cout << "wspolrzedne nie spelniaja warunkow\n";
        return false;
    }
return true;
}

// sortuje tablicę koordynatów, sprawdza, czy odcinki rzutowane mają część wspólną (zwraca true) lub czy są rozłączne (zwraca false)
bool sort_and_asses(float coords[4])
{
   //w tablicy index docelowo znajdą się indeksy w kolejności odpowiadającej kolejności posortowanych koordynatów. 
   //Z tych indeksów zostanie zbudowany order_code np. {1,3,2,0} -> 1320
   int index[4]={0,1,2,3}; // porządek początkowy 

   //tablica kodów porządku,w których możliwa rozbieżność czyli taka kolejność koordynatów, w których może zaistnieć brak części wspólnej
   int arr_order_codes_to_check[8] = {0123,0132,1023,1032,2301,2310,3201,3210}; 

   //Kod porządku - będzie pokazywał po kolei indeksy od koordynatu najmniejszego do największego
   int order_code=0; //inicjalizacja kodu porządku 

   float common_part_len=0; //odległość między środkowymi elementami po posortowaniu
    
    //sortowanie koordynatów i równocześnie indeksów
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4-i-1; j++)
        {
            if(coords[j] > coords[j+1])
            {
                //zamiana w tablicy koordynatów
                float aux_float = coords[j+1];                            
                coords[j+1] = coords[j];
                coords[j] = aux_float;
                //i równocześnie zamiana w tablicy indeksów
                int   aux_int = index[j+1] ;
                index[j+1] = index[j];
                index[j] = aux_int;
            }
        }
    }
    //posortowane koordynaty
    //cout << coords[0] << " " << coords[1] << " " << coords[2] << " " << coords[3] << "\n";
    //posortowane indeksy
    //cout << index[0] << " " << index[1] << " " << index[2] << " " << index[3] << "\n";

    //formowanie kodu porządku
    for(int i = 0; i < 4; i++)
    {
           order_code = order_code*10 + index[i];
    } 
    common_part_len= coords[2]-coords[1];
    //cout << "odleglosci miedzy srodkowymi "<< common_part_len << "\n";
    //cout << "kod porzadku " << order_code <<"\n";

    //sprawdzenie, czy kod porządku nie należy do zbioru "podejrzanych" i jeżeli jest podejrzany oraz 
    //równocześnie między środkowymi koordynatami jest dystans, to oznacza, że nie istnieje część wspólna
    for(int i = 0; i < 8; i++)
    {
        if((order_code==arr_order_codes_to_check[i]) && (common_part_len>0)) return false;
    } 
    // kod nie jest podejrzany, lub jest ale nie ma rozbieżności (możliwa degeneracja)
    return true;
}
