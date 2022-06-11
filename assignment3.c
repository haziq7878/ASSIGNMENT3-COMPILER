#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// function to break apart a grammer into left side terminal and its productions

char break_prod(char *prod)
{
    // to count number of productions to make an array list
    int count = 0;
    int max = 0;
    int size = 0;
    for (int i = 3; i < strlen(prod); i++)
    {
        if (prod[i] == '|')
        {
            if (max < size)
            {
                max = size;
            }
            size = 0;
            count++;
        }
        size++;
    }
    char ans[count][max];
}

// state counter
int state_counter = 0;;
char state_list[100][100][100] = {{'\0'}}; // state_list



int main()
{
    FILE *ptr;
    ptr = fopen("grammer.txt", "r");
    char temp[80]; // temp array used for copying a single line from a file
    if (ptr == NULL)
    {
        printf("There was an error in opening the file");
        return -1;
    }
    int count = 0;
    int production_index = 0;
    while (fgets(temp, sizeof(temp), ptr) != NULL)
    {
        for (int i = 0; i < strlen(temp); i++)
        {
            if (temp[i] != '\n')
            {
                state_list[0][production_index][count] = temp[i];
                count++;
            }
            else
            {
                production_index++;
            }
        }
        count = 0;
        memset(temp, 0, 80);
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", state_list[0][i]);
    }
    char grammer[3][9] =
        {
            "S->L=R|R\0",
            "L->*R|i\0",
            "R->L\0"};
    for (int i = 0; i < 3; i++)
    {
        break_prod(grammer[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", grammer[i]);
    }
}