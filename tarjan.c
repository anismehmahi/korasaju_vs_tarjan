#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Graphe.c"
typedef struct node {
  
  int data;
  char etat[80];
  int low;
  int index;
} node;
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
int cfc=1;
node tab[NUM_VERTICES];
    int cpt=0;

int DFS(int v);


#define N 100000

int top = -1;

node stack[N];

void push(node x);       
node  pop();         




int main(int argc, char const *argv[])
{
  


 // Initialisation des noeuds
   for(int j=0; j<NUM_VERTICES; j++){
    node p ;
     p.data=j;
     p.index=-1;
     strcpy(p.etat, "non visite");   
     p.low=-1;
     tab[j] = p;
    }
    clock_t tic = clock();


    // Progarmme appeleant 
    for(int i=0;i<NUM_VERTICES;i++)
    {
        if(tab[i].index==-1){
            DFS(i);
        }
    }
    clock_t toc = clock();
        printf("Temps d'execution: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);


    return 0;
}



int DFS(int v){
   
    tab[v].low = tab[v].index=cpt;   
     strcpy(tab[v].etat , "visite") ;
    cpt++;

    push(tab[v]);


    for(int k=0;k<NUM_VERTICES;k++){

        if (matrice[v][k]==1){
        if ( tab[k].index==-1 ) {
             DFS(k);
             tab[v].low = MIN(tab[k].low,tab[v].low);
        }else {
            if (strcmp(tab[k].etat , "visite")==0){
            tab[v].low = MIN(tab[k].index,tab[v].low);
           }
        }
        }
   
    }
  int w =-1;
    if (tab[v].index==tab[v].low){
        printf("CFC %d : ", cfc);
        while(w!=tab[v].data){
            w = pop().data;
            printf("%d  ", w);
            strcpy(tab[w].etat,"visite");
        }
        cfc++;
        printf("\n");
    }
  



    return 0;

}

void push(node x){
    if(top == N-1)
        printf("Overflow State: can't add more elements into the stack\n");
    else{
        top+=1;
        stack[top] = x;
    }
}

node pop(){
    if(top == -1)
        printf("Underflow State: Stack already empty, can't remove any element\n");
    else{
        node x = stack[top];
        top-=1;
        return x;
    }
   
}


