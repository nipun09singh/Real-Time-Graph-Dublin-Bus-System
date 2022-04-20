#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "t2.h"



Graph* create_graph(int num_nodes); 
void add_edge(Graph *g, int from, int to, int weight); 
void dijkstra(Graph* g, int origin); 
void delete_graph(Graph* g); 

struct Graph* create_graph(int num_nodes) // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
{
    Graph* g = (struct Graph*) malloc(sizeof( Graph));
    g->totalnodes = num_nodes;

    int i,j;
    for (i = 0; i < VERTEXMAX; i++)
    {
        for(j = 0; j<VERTEXMAX;j++ ){
            (g->elements[i][j] = 999999);
        }  
    }

    return g;
}

void add_edge(Graph *g, int from, int to, int weight) // adds a directed edge
{
    g->elements[from][to] = weight;
    g->elements[to][from] = weight;  
}



void dijkstra(Graph* g, int origin){
    int i;
    int num = g->totalnodes;
    int CalcDistan[num], ifVisit[num], temp, DistanceMin, ElNext;
    

    for (i = 0; i < num; i++) {
    CalcDistan[i] = g->elements[origin][i];

    ifVisit[i] = 0;

    }
    ifVisit[origin] = 1;
    CalcDistan[origin] = 0;
    temp = 1;  

    while (temp < num-1) {
        
        DistanceMin = 999999;
    
        for (i = 0; i < num; i++)
        {
            if (CalcDistan[i] < DistanceMin && ifVisit[i] != 1) {
            DistanceMin = CalcDistan[i];
            ElNext = i;
            }
        }
           
    
        ifVisit[ElNext] = 1;
        for (i = 0; i < num; i++){
            if (ifVisit[i] != 1){
                if (DistanceMin + g->elements[ElNext][i] < CalcDistan[i]) {
                    CalcDistan[i] = DistanceMin + g->elements[ElNext][i];

                }
            }
        }
        temp++;
    }

    int sort[num];
    int u,v;
    for(u=0;u<num;u++){
        sort[u]=CalcDistan[u]; 
    }
    
    int index_arr[num];
    
    for(u=0;u<num;u++){
        index_arr[u]=u; 
    }
    
    for( i = 1; i < num; i++){
        
        for( v = i-1; v>=0; v--){
            if(sort[i] < sort[v]){

                int t1,t2;
                t2 = index_arr[i];
                t1 = sort[i];
                index_arr[i] = index_arr[v];
                index_arr[v] = t2;
                sort[i] = sort[v];
                sort[v] = t1;
                i = i-1;
            }
        }
    }
        
    for(i=0;i<num;i++){
        printf("%c ",'A'+index_arr[i]);
    }

    printf("\n");

    for(i=0; i<num; i++){
        printf("The length of the shortest path between %c and %c is %d\n",'A'+origin,'A'+i,CalcDistan[i]);
    }
}

void delete_graph(Graph* g) 
{
   
    int i,v;
    for(i=0; i<g->totalnodes; i++){
        for(v=0; v<g->totalnodes; v++){
            g->elements[i][v]=0;
        }
    }
    free(g);
}
