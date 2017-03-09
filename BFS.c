#include <stdio.h>
#include <stdlib.h>
int colour[100000];
int distance[100000];
int parent[100000];
struct AdjListNode
{
	int dest;
	struct AdjListNode * next;
};
struct AdjList
{
	struct AdjListNode *head;
};
struct Graph
{
	int v;
	struct AdjList* array;
};
struct Graph* createGraph(int vertices)
{
	struct Graph* graph=(struct Graph*)malloc(sizeof(struct Graph));
	graph->v=vertices;
	graph->array=(struct AdjList*)malloc(vertices*sizeof(struct AdjList));
	int i;
	for(i=0;i<vertices;i++)
	{
		graph->array[i].head=NULL;
	}
	return graph;
};
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
struct Graph* addEdge(struct Graph* graph,int src,int dest)
{
	struct AdjListNode* newnode=newAdjListNode(dest);
	//newnode->dest=dest;
	newnode->next=graph->array[src].head;
	graph->array[src].head=newnode;
	//since it is undirected we have to add an edge from dest to src 
	newnode=newAdjListNode(src);
	newnode->next=graph->array[dest].head;
	graph->array[dest].head=newnode;
};
void printGraph(struct Graph* graph)
{
	int i;
	for(i=0;i<graph->v;i++)
	{
		struct AdjListNode* t=graph->array[i].head;
		printf("%d->",i);
		while(t)
		{
			printf("%d->",t->dest);
			t=t->next;
		}
		printf("\n");

	}	
};
void BFS(struct Graph* graph, int vertices,int src)
{
	int i;
	for(i=0;i<vertices;i++)
	{
		colour[i]=0;
		distance[i]=100000;
		parent[i]=-1;
	}
	colour[src]=1;
	distance[src]=0;
	int q[vertices];
	int entry=0;
	int exit=0;
	q[exit++]=src;
	while(entry!=exit)
	{
		int popped=q[entry++];
		struct AdjListNode* t=graph->array[popped].head;
		printf("%d ",popped);
		while(t)
		{
			if(colour[t->dest]==0)
			{
				colour[t->dest]=1;
				distance[t->dest]=distance[popped]+1;
				parent[t->dest]=popped;
				q[exit++]=t->dest;
			}
			t=t->next;
		}
		colour[popped]=2;
	}
}
int main()
{
	int n,m;
	//n=no. of vertices
	//m=no. of edges
	scanf("%d %d ",&n,&m);
	struct Graph* graph=createGraph(n);
	int i;
	for(i=0;i<m;i++)
	{
		int src,dest;
		scanf("%d %d",&src,&dest);
		addEdge(graph,src,dest);
	}
	int start;
	printf("Enter the source = ");
	scanf("%d",&start);
	BFS(graph,n,start);
	return 0;
}