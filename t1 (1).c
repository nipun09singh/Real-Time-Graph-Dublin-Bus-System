#include <stdio.h>
#include <stdlib.h>
#include "t1.h"
#define SIZE 40

struct Graph* create_graph(int num_nodes); 
void add_edge(struct Graph *g, int from, int to); 
void bfs(struct Graph* g, int origin); 
void dfs(struct Graph* g, int origin); 
void print_graph(struct Graph* g); 

int num2char(int number){
	number = number+65;
	return number;
}

struct queue {
	int elements[SIZE];
	int start;
	int end;
};
	

struct queue* makeQueue() {
	struct queue* queue = malloc(sizeof(struct queue));
	queue->start = -1;
	queue->end = -1;
	return queue;
}
	
int qEmpty(struct queue* queue) {
	if (queue->end == -1)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}	

void enqueue(struct queue* queue, int value) {
	if (queue->end == SIZE - 1)
	{
		printf("\nQueue Full");
	}
    	
	else {
    	if (queue->start == -1)
    	{
    		queue->start = 0;
		}
      		
    	queue->end++;
    	queue->elements[queue->end] = value;

	}
}

int dequeue(struct queue* queue) {
	int element;
	if (qEmpty(queue)) 
	{
    	printf("Queue empty");
    	element = -1;
	} 
	else 
	{
		element = queue->elements[queue->start];
		queue->start++;
    	if (queue->start > queue->end) 
		{//We reset the Queue

      		queue->start = queue->end = -1;
    	}
	}
	return element;
}


void printQueue(struct queue* queue) {
	int i = queue->start;

	if (qEmpty(queue)) 
	{
    	printf("Queue is empty");
	} 
	else 
	{

    	for (i = queue->start; i < queue->end + 1; i++) 
		{
      		printf("%c ", num2char(queue->elements[i]));//Printing elements in Queue
    	}
    }
}




Graph* create_graph(int num_nodes) // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
{
	Graph* g = (struct Graph*) malloc(sizeof(Graph));
    g->num_of_nodes = num_nodes;

    g->array = malloc(num_nodes * sizeof(struct AdjListNode*));
	g->visited = malloc(num_nodes * sizeof(int));
    int i;
    for (i = 0; i < num_nodes; i++)
	{
    	g->array[i] = NULL;
        g->visited[i] = 0;
  
	}

    return g;
}


AdjListNode* newAdjList_Node(int var)//Making adjacency List
{
    struct AdjListNode* new_node = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    new_node->final = var;
    new_node->next = NULL;
    return new_node;
};

void add_edge(Graph *g, int from, int to) //Helps to add directed edge
{
	AdjListNode* new_node = newAdjList_Node(to);
    new_node->next = g->array[from];
    g->array[from] = new_node;
  

}

void bfs(Graph* g, int origin) //Implement BFS and printing results
{
	struct queue* queue = makeQueue();
	printf("\n");
	printf("BFS ");
	g->visited[origin] = 1;
	enqueue(queue, origin);
	
	while (!qEmpty(queue)) 
	{
		
		int currentVertex = dequeue(queue);	
		printf(" %c ", num2char(currentVertex));
		struct AdjListNode* temp = g->array[currentVertex];
		
		while (temp) 
		{
			int VertexAdj = temp->final;
			
			if (g->visited[VertexAdj] == 0) 
			{
				g->visited[VertexAdj] = 1;
				enqueue(queue, VertexAdj);
			}
			temp = temp->next;
		}
	}
	int j;
	for(j=0; j<g->num_of_nodes; j++){
		g->visited[j]=0;
	}
	free(queue);

}

int counter(Graph* g, int origin){
	
	struct queue* queue = makeQueue();
	
	g->visited[origin] = 1;
	int x = 0;
	x++;
	
	while (!qEmpty(queue)) 
	{
		
		int currentVertex = dequeue(queue);		
		struct AdjListNode* temp = g->array[currentVertex];
		
		while (temp) 
		{
			int VertexAdj = temp->final;
			
			if (g->visited[VertexAdj] == 0) 
			{
				g->visited[VertexAdj] = 1;
				x++;
			}
			temp = temp->next;
		}
	}
	free(queue);
	return x;
}

void dfs(Graph* g, int origin) //implements depth first search and prints the results
{	
	static int Booltemp = 0;
	static int Booltemp2 = 0;
	
	struct AdjListNode* arrays  = g->array[origin];
	struct AdjListNode* temp = arrays;
	if(Booltemp2 == 0){
		printf("DFS:");
		Booltemp2++;
	}
	
	g->visited[origin] = 1;

	printf(" %c ", num2char(origin));

	while (temp != NULL) {
    int Node_f = temp->final;

    if (g->visited[Node_f] == 0) 
	{
		dfs(g, Node_f);
		Booltemp++;
    }
	temp = temp->next;
	}
	if(Booltemp+1 == g->num_of_nodes){
		int j;
		for(j=0; j<g->num_of_nodes; j++){
			g->visited[j]=0;
		}	
	}
	

}

void print_graph(Graph* g) //Printing
{	
	printf("\n");
	int i;
    for (i = 0; i < g->num_of_nodes; i++)
    {
        struct AdjListNode* point = g->array[i];
		printf("%c ", num2char(i));
        while (point)
        {
			printf(" -> %c ", num2char(point->final));
        	point = point->next;
  
        }
		printf("\n");
    }

}

void delete_graph(Graph* g) // delete the graph and all its data structures.
{
	int i;
    for (i = 0; i < g->num_of_nodes; i++)
    {
        struct AdjListNode* point = g->array[i];

        while (point)
        {	
        	struct AdjListNode* temp;
        	temp = point;
        	point = point->next;
            free(temp);
        }

    }
    free(g->array);
    free(g->visited);
    free(g);
//    printf("Deleted Graph");
}


