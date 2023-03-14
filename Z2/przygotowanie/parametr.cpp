#include <iostream>

using namespace std;
int p;
int i=1;
int main()
{
    while (p!=99)
    {
    cout << "Podaj ";
    cout << i;
    cout << ". wartosc parametru: ";
    cin >> p;

    i++;

    {
    if (p>-5 and p<5)
        {
            cout << "Aktualna wartosc parametru: ";  
            cout << p;
            cout << "\n";
         }
    else if (p!=99)
        {
        cout << "To niepoprawna wartosc parametru";
        cout << "\n";
        }
    }
    }
return 0;


}