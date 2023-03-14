#include <iostream>

using namespace std;
int main()
{
int arr_1d[25];
int arr_2d[5][5]=   {{1,2,3,4,5},
                    {6,7,8,9,10},
                    {11,12,13,14,15},
                    {16,17,18,19,20},
                    {21,22,23,24,25}};

for (int x = 0; x < 5; ++x)
{
    for (int k = 0; k < 5; ++k){
        arr_1d[5*x + k] = arr_2d[x][k];
        {
            cout << arr_2d[x][k] << " " << endl;
        }

    }
}
return 0;
}