#include <iostream>

using namespace std;
int rs = 3; // space in row 
int cs = 2; // space in column

int elements[5][5]=   {{1,2,3,4,5},
                    {6,7,8,9,10},
                    {11,12,13,14,15},
                    {16,17,18,19,20},
                    {21,22,23,24,25}};
void Up();
void Down();
void Right();
void Left();
void Up()
{
	int vP = rs;
	if(vP + 1 < 5 && vP >= 0){
	
	elements[rs][cs] = elements[rs + 1][cs];
	elements[rs + 1][cs] = ' ';
	rs += 1;
	}
}
void Down()
{
	int vP = rs;
	if(vP + 1 <= 5 && vP > 0){
	
	elements[rs][cs] = elements[rs - 1][cs];
	elements[rs - 1][cs] = ' ';
	rs -= 1;
	}
}
void Right()
{
	int hP = cs;
	if(hP + 5 <= 4 && hP > 0){
	
	elements[rs][cs] = elements[rs][cs - 1];
	elements[rs][cs - 1] = ' ';
	cs -= 1;
	}
}
void Left()
{
	int hP = cs;
	if(hP + 1 < 5 && hP >= 0){
	
	elements[rs][cs] = elements[rs][cs + 1];
	elements[rs][cs + 1] = ' ';
	cs += 1;
	}
}
int main()
{

return 0;
}