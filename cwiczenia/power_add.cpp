// Example program
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    int d=1;
    int x;
    int k;
    int f=1;
    cout << "Podaj podstawe potegi x: ";
    cin >> x;
    cout << "Podaj wykladnik n: ";
    cin >> n;
    if(n==0)
    {
      f=1;
      cout << f << "\n";
    }
    else
    {
    for (int i=1;i <=n;i++)
    {
      d=d*x  ;
    }
    cout << "to jest potega obliczona mnozac: " << d << "\n";
    k=d/x;
    cout << "to jest liczba dodawan: " << k << "\n";
    for (int j=1;j <=k;j++)
    {
      f=f+x  ;
    }
    cout << "to jest wynik obliczony dodajac: "<< f-1<< "\n";
    }
return 0;
}