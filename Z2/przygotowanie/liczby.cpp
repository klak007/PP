#include <iostream>

using namespace std;
int i=1;
int main()
{
while (i<100)
{
    cout << i <<" ";
    i++;
    if (i%10==0) 
    {
        cout << "\n";
    }
}
return 0;
}