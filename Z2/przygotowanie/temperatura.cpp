#include <iostream>

using namespace std;
int limit=18;
int temp;
int main()
{
cout << "Podaj temperature we Wroclawiu: ";
cin >> temp;
{
if (temp<limit)
{
    cout << "slaba pogoda";  
    cout << "\n";
}
else
{
    cout << "idealna aura na spacer";
    cout << "\n";
}

return 0;
}
}