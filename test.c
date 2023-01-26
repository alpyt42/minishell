#include <stdio.h> 

int main()
{

char array[3][2][100] = {
    {"Pwd", "chemin de pwd"},
    {"goodbye", "moon"},
    {"foo", "bar"}
};
printf("array[0][0] = %s\n", array[0][0]);
printf("array[0][1] = %s\n", array[0][1]);

}