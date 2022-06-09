#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

//function to break apart a grammer into left side terminal and its productions

char* break(char[] prod)
{
    //to count number of productions to make an array list
    int count = 0; int max = 0; int size = 0;
    for (int i = 2;i<strlen(prod);i++)
    {
        if (prod[i] == '|')
        {
            if (max < size)
            {
                max = size;
            }
            size = 0;
            count ++;
        }
        size++;
    }
    ans[count][size];
    
}

int main()
{
    char grammer[3][8] = 
    {
        "S-L=R|R\0",
        "L-*R|i\0",
        "R-L\0"
    };
    for(int i = 0;i<3;i++)
    {
        printf("%s\n",grammer[i]);
    }
}