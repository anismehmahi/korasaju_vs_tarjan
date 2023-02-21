#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Graphe.c"

typedef struct node
{

    int data;
    int index;
    char etat[80];

} node;
#define MIN(i, j) (((i) < (j)) ? (i) : (j))

int transpose[NUM_VERTICES][NUM_VERTICES];
node tab[NUM_VERTICES];

int DFS(int matrix[NUM_VERTICES][NUM_VERTICES], int v, int parcours);

#define N 100000
int cfc=1;
int top = -1;

node stack[N];

void push(node x); 
node pop();       
void init()
{
    int i, j;
    for (i = 0; i < NUM_VERTICES; i++)
        for (j = 0; j < NUM_VERTICES; j++)
            matrice[i][j] = 0;
}
int main(int argc, char const *argv[])
{
    init();
    int i = 0;
    for (i=0;i<NUM_EDGES;i++)
    {
        
            matrice[rand()%NUM_VERTICES][rand()%NUM_VERTICES] = 1;
        
    }

    for(int k=0;k<NUM_VERTICES;k++){
        matrice[k][k]=0;
    }
    // Initialisation des noeuds
    for (int j = 0; j < NUM_VERTICES; j++)
    {
        node p;
        p.data = j;
        p.index = j;
        strcpy(p.etat, "non visite");
        tab[j] = p;
    }

    clock_t tic = clock();

    // Progarmme appeleant
    for (int i = 0; i < NUM_VERTICES; i++)
    {
        if (strcmp(tab[i].etat, "non visite") == 0)
        {
            DFS(matrice, i, 1);
        }
    }

    // Transpose matrix

    for (int i = 0; i < NUM_VERTICES; ++i)
        for (int j = 0; j < NUM_VERTICES; ++j)
        {
            transpose[j][i] = matrice[i][j];
        }

    for (int i = 0; i < NUM_VERTICES; i++)
        strcpy(tab[i].etat, "non visite");
    while (top != -1)
    {
        node x = pop();
        if (strcmp(tab[x.index].etat, "non visite") == 0)
        {
            printf("CFC %d : ",cfc);
            DFS(transpose, x.index, 2);
            cfc++;
            printf("\n");
        }
    }

    clock_t toc = clock();
    printf("Temps d'execution: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}

int DFS(int matrix[NUM_VERTICES][NUM_VERTICES], int v, int parcours)
{

    strcpy(tab[v].etat, "visite");

    if (parcours == 2)
        printf("%d ", tab[v].data);

    for (int k = 0; k < NUM_VERTICES; k++)
    {

        if (matrix[v][k] == 1)
        {
            if (strcmp(tab[k].etat, "non visite") == 0)
            {
                DFS(matrix, k, parcours);
            }
        }
    }
    if (parcours == 1)
        push(tab[v]);

    return 0;
}

void push(node x)
{
    if (top == N - 1)
        printf("Overflow State: can't add more elements into the stack\n");
    else
    {
        top += 1;
        stack[top] = x;
    }
}

node pop()
{
    if (top == -1)
        printf("Underflow State: Stack already empty, can't remove any element\n");
    else
    {
        node x = stack[top];
        top -= 1;
        return x;
    }
}
