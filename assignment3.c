#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// state counter (THis specifies the index where new state should be added)
int state_counter = 0;
char state_list[100][100][100] = {{'\0'}}; // This variable is used to store chronicles of a grammer. The index value specifies the states
char non_terminals[100] = {'\0'};          // an array of non-terminals
int non_terminals_index = 0;               // index for non-terminals
char terminals[100] = {'\0'};              // an array of terminals
int terminals_index = 0;                   // index for terminals
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

// This function is used to add new states in the state list. This new state will be added in index (value depends upon the state counter) of state list
void add_new_state(int length, char new_state[100][100])
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        count = 0;
        for (int j = 0; j < strlen(new_state[i]); j++)
        {
            state_list[state_counter][i][j] = new_state[i][j];
        }
    }
}

// THis function is used for reading grammer from the file and store it in the state 0 (The index 0 of the state list)
void file_handler()
{
    FILE *ptr;
    ptr = fopen("grammer.txt", "r");
    char temp[80]; // temp array used for copying a single line from a file
    if (ptr == NULL)
    {
        printf("There was an error in opening the file");
    }
    int count = 0;
    int production_index = 0;
    // THese steps are used to store S^bar -> S
    state_list[state_counter][production_index][count] = 'Q';
    count++;
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
            else if (temp[i] != '\n' && temp[i] != '>' && temp[i] != '|')
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
    state_counter++;
    fclose(ptr);
}

// This function is used to check if the new productions created through traversal is already in the store as state or not
// First it will find the total matched productions in a state and compare it with total productions in the new production list
// If its equal that means that the new production state is already in the state list and if not then it will add it in the state list
void check_state(char new_state[100][100], int length)
{
    int production_count_new_state = 0; // This variable is used to count the number of productions in the new state
    int check_match;                    // We will count how many strings were matched
    // if the number of strings match is equal to length of the new_state then we will not append that state
    for (int i = 0; i < state_counter; i++)
    {
        check_match = 0;
        for (int count_new_state_production = 0; count_new_state_production < length; count_new_state_production++) // This will iterate over all the productions made through the traversal
        {
            production_count_new_state++;
            if (strcmp(new_state[count_new_state_production], "\0") == 0) // THis is used to figure out the total number of production in a new state list
            {
                production_count_new_state--;
                break;
            }
            for (int j = 0; j < strlen(state_list[i][0]); j++)
            {
                if (strcmp(new_state[count_new_state_production], state_list[i][j]) == 0)
                {
                    check_match++; // string matched
                    // printf("match");
                }
            }
        }
        if (check_match == production_count_new_state)
        {
            // printf("break");
            break;
        }
    }
    if (check_match != production_count_new_state)
    {
        printf("not Matched\n");
        // This will append the new state in the state list
        add_new_state(length, new_state);
        state_counter++;
    }
}

// This function is simply to display the chronicles
void display_states()
{
    for (int i = 0; i < state_counter; i++)
    {
        printf("state %d\n", i);
        for (int j = 0; j < strlen(state_list[i][0]); j++)
        {
            if (strcmp(state_list[i][j], "\0") != 0)
            {
                printf("%s\n", state_list[i][j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    file_handler();
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
    // new_state formate char new_state1[100][100] = {"Q->S.","Q->SLR"}; anthing in 2d array. just store it in tthis kinds of array


    char new_state1[100][100] = {"Q->S."};
    int length1 = sizeof(new_state1) / sizeof(new_state1[0]);
    char new_state2[100][100] = {"S->L.=R"};
    int length2 = sizeof(new_state2) / sizeof(new_state2[0]);
    check_state(new_state1, length1);
    display_states();
    check_state(new_state2, length2);
    display_states();
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
