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
int state_counter = 0;
char state_list[100][100][100] = {{'\0'}}; // state_list

int main()
{
    FILE *ptr;
    ptr = fopen("grammer.txt", "r");
    char temp[80];                    // temp array used for copying a single line from a file
    char non_terminals[100] = {'\0'}; // an array of non-terminals
    int non_terminals_index = 0;      // index for non-terminals
    char terminals[100] = {'\0'};     // an array of terminals
    int terminals_index = 0;          // index for terminals
    if (ptr == NULL)
    {
        printf("There was an error in opening the file");
        return -1;
    }
    int count = 0;
    int production_index = 0;
    state_list[state_counter][production_index][count] = 'Q';
    count++;
    // Adding start state to non terminals list
    non_terminals[non_terminals_index] = 'Q';
    non_terminals_index++;
    state_list[state_counter][production_index][count] = '-';
    count++;
    state_list[state_counter][production_index][count] = '>';
    count++;
    state_list[state_counter][production_index][count] = '.';
    count++;
    while (fgets(temp, sizeof(temp), ptr) != NULL)
    {
        for (int i = 0; i < strlen(temp); i++)
        {
            if (temp[i] == ' ')
            {
                continue;
            }

            else if (temp[i] != '\n' && temp[i] != '>' && temp[i] != '|' && temp[i] != '-')
            {
                if (production_index == 0)
                {
                    state_list[state_counter][production_index][count] = temp[i];
                    count = 0;
                    production_index++;
                }

                state_list[state_counter][production_index][count] = temp[i];
                count++;
            }
            else if (temp[i] == '>')
            {
                state_list[state_counter][production_index][count] = temp[i];
                count++;
                state_list[state_counter][production_index][count] = '.';
                count++;
            }
            else if (temp[i] == '-')
            {
                non_terminals[non_terminals_index] = temp[i - 1];
                non_terminals_index++;
                state_list[state_counter][production_index][count] = temp[i];
                count++;
            }
            else if (temp[i] == '|')
            {
                production_index++;
                count = 0;
                while (state_list[state_counter][production_index - 1][count] != '.')
                {
                    state_list[state_counter][production_index][count] = state_list[state_counter][production_index - 1][count];
                    count++;
                }
                state_list[state_counter][production_index][count] = '.';
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
    for (int i = 0; i < strlen(state_list[0][0]); i++)
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
    // for (int i = 0; i < 3; i++)
    // {
    //     printf("%s\n", grammer[i]);
    // }
    for (int i = 0; i < strlen(non_terminals); i++)
    {
        printf("Non Terminals: %c\n", non_terminals[i]);
    }

    // to seperate out non terminals
    for (int j = 0; j < production_index; j++)
    {
        for (int i = 0; i < strlen(state_list[0][j]); i++)
        {
            int flag;
            for (int k = 0; k < strlen(non_terminals); k++)
            {
                if (state_list[0][j][i] != non_terminals[k] && state_list[0][j][i] != '-' && state_list[0][j][i] != '>' && state_list[0][j][i] != '.')
                {
                    flag = 1;
                }
                else
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {

                terminals[terminals_index] = state_list[0][j][i];
                terminals_index++;
            }
        }
    }

    for (int i = 0; i < strlen(terminals); i++)
    {
        printf("Terminals: %c\n", terminals[i]);
    }
}
