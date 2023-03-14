#include <iostream>

using namespace std;
int main()
{
int arr_1d[25];
int arr_2d[5][5];
for (int i = 0; i < 25; ++i)
{
    arr_1d[i] = i; 
}

for (int x = 0; x < 5; ++x)
{
    for (int k = 0; k < 5; ++k){
        arr_2d[x][k] = arr_1d[5*x + k];
        {
            cout << arr_2d[x][k] << " " << endl;
        }

    }
}
return 0;
}