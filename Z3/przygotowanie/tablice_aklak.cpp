#include <iostream>

using namespace std;

int arrx[10][10];
int menu;

void fill(int x,int y)
{
    for(int i = 0; i < x; i++)
        for (int j =0; j < y;j++) 
            arrx[i][j] = i * j;

}
void print(int x,int y)
{
    for(int i = 0; i < x; i++)
    {  
        for (int j =0; j < y;j++) cout << " " << arrx[i][j];
        cout<<"\n";
    }
}
void negateeee(int x, int y)
{
    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++) 
            arrx[i][j] = arrx[i][j] * ( - 1) ;
}
int main()
{
    int m=10, n=10;
    fill(m,n);
    print(m,n);
    negateeee(m,n);
    print(m,n);
    cout << "Proste menu:" << "\n" << "1 - Pozycja pierwsza" 
    << "\n" << "2 - Pozycja druga" 
    << "\n" << "3 - Pozycja trzecia" 
    << "\n" << "4 - Zakończ działanie" << "\n" << "Twój wybór: ";
  
    cin >> menu;
    switch (menu)
    {
        case 1:
            cout << "wybór trzeci:)";
            break;
        case 2:
            cout << "wybór pierwszy:)";
            break;
        case 3:
            cout << "wybór drugi:)";
            break;
        case 4:
            cout << "koniec programu <:";
            break;
    }
    return 0;
}