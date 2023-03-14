#include <iostream>  
using namespace std; 

int triangle(int n) 
{ 
  for (int line = 1; line <= n; line++) 
  { 
      int a = 1; 
      for (int i = 1; i <= line; i++)  
      { 

          cout<< a<<" ";  
          a = a * (line - i) / i;  
      } 
      cout<<"\n"; 
  } 
} 

int main() 
{ 
    int n;
    cin >> n ; 
    triangle(n); 
    return 0; 
} 