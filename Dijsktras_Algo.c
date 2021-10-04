#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define inf 9999
#define max 10
 
void Dijkstra(long int graph[max][max],long int n,long int startnode)
{
 
	long int cost[max][max],distance[max],pred[max];
	long int visited[max],count,mindistance,nextnode,a,j;
	
	for(a=0;a<n;a++)
		for(j=0;j<n;j++)
			if(graph[a][j]==0)
				cost[a][j]=inf;
			else
				cost[a][j]=graph[a][j];
	
	for(a=0;a<n;a++)
	{
		distance[a]=cost[startnode][a];
		pred[a]=startnode;
		visited[a]=0;
	}
	
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<n-1)
	{
		mindistance=inf;
		
		for(a=0;a<n;a++)
			if(distance[a]<mindistance&&!visited[a])
			{
				mindistance=distance[a];
				nextnode=a;
			}
						
			visited[nextnode]=1;
			for(a=0;a<n;a++)
				if(!visited[a])
					if(mindistance+cost[nextnode][a]<distance[a])
					{
						distance[a]=mindistance+cost[nextnode][a];
						pred[a]=nextnode;
					}
		count++;
	}
 
	for(a=0;a<n;a++)
		if(a!=startnode)
		{
			printf("\nDistance of node%ld=%ld",a,distance[a]);
			printf("\nPath=%ld",a);
			
			j=a;
			do
			{
				j=pred[j];
				printf("<-%ld",j);
			}while(j!=startnode);
	}
}

void UsingAdjacencyMatrix()
{
	long int graph[max][max],a,j,n,u;
	printf("Enter no. of vertices:");
	scanf("%ld",&n);
	printf("\nEnter the adjacency matrix:\n");
	
	for(a=0;a<n;a++)
		for(j=0;j<n;j++)
			scanf("%ld",&graph[a][j]);
	
	printf("\nEnter the starting node:");
	scanf("%ld",&u);
	Dijkstra(graph,n,u);

}





struct adjacencyListNode
{
    long int destination;
    long int wt;
    struct adjacencyListNode* nxt;
};
 
struct adjacencyList
{
   struct adjacencyListNode *before; 
};
 
struct graph
{
    long int Vert;
    struct adjacencyList* Array;
};

struct min_Heap_Node
{
    long int  vert;
    long int distance;
};
 
// A utility function to create 
// a new adjacency list node
struct adjacencyListNode* newAdjacencyListNode(
                   long int destination, long int wt)
{
    struct adjacencyListNode* NewNode =
            (struct adjacencyListNode*) 
      malloc(sizeof(struct adjacencyListNode));
    NewNode->destination = destination;
    NewNode->wt = wt;
    NewNode->nxt = NULL;
    return NewNode;
}
 
// A utility function that creates 
// a graph of Vert vertices
struct graph* CreatingGraph(long int Vert)
{
    struct graph* graph = (struct graph*) 
            malloc(sizeof(struct graph));
    graph->Vert = Vert;
 
    // Create an Array of adjacency lists.  
    graph->Array = (struct adjacencyList*) 
       malloc(Vert * sizeof(struct adjacencyList));
 
    // Initialize each adjacency list 
    for (long int a = 0; a < Vert; ++a)
        graph->Array[a].before = NULL;
 
    return graph;
}

struct min_Heap
{    
    long int sizeOfHeap;     
    long int cap;  
    // This is needed for DecreasingKey()
    long int *position;    
    struct min_Heap_Node **Array;
};
 
void AddingEdge(struct graph* graph, long int src, 
                   long int destination, long int wt)
{
    // Add an edge from src to destination.  
    struct adjacencyListNode* NewNode = 
            newAdjacencyListNode(destination, wt);
    NewNode->nxt = graph->Array[src].before;
    graph->Array[src].before = NewNode;
    // add an edge from destination to src (undirected)
    NewNode = newAdjacencyListNode(src, wt);
    NewNode->nxt = graph->Array[destination].before;
    graph->Array[destination].before = NewNode;
}
 
// A utility function to create a 
// new Min Heap Node
struct min_Heap_Node* newMinHeapNode(long int vert, 
                                 long int distance)
{
    struct min_Heap_Node* minHeapNode =
           (struct min_Heap_Node*) 
      malloc(sizeof(struct min_Heap_Node));
    minHeapNode->vert = vert;
    minHeapNode->distance = distance;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct min_Heap* createMinHeap(long int cap)
{
    struct min_Heap* minHeap =
         (struct min_Heap*) 
      malloc(sizeof(struct min_Heap));
    minHeap->position = (long int *)malloc(
            cap * sizeof(long int));
    minHeap->sizeOfHeap = 0;
    minHeap->cap = cap;
    minHeap->Array =
         (struct min_Heap_Node**) 
                 malloc(cap * 
       sizeof(struct min_Heap_Node*));
    return minHeap;
}
 
void swapMinHeapNode(struct min_Heap_Node** x, 
                     struct min_Heap_Node** y)
{
    struct min_Heap_Node* t = *x;
    *x = *y;
    *y = t;
}
 
void minHeapify(struct min_Heap* minHeap, 
                                  long int idx)
{
    long int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->sizeOfHeap &&
        minHeap->Array[left]->distance < 
         minHeap->Array[smallest]->distance )
      smallest = left;
 
    if (right < minHeap->sizeOfHeap &&
        minHeap->Array[right]->distance <
         minHeap->Array[smallest]->distance )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct min_Heap_Node *smallestNode = 
             minHeap->Array[smallest];
        struct min_Heap_Node *idxNode = 
                 minHeap->Array[idx];
 
        // Swap positions
        minHeap->position[smallestNode->vert] = idx;
        minHeap->position[idxNode->vert] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->Array[smallest], 
                         &minHeap->Array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
long int isEmpty(struct min_Heap* minHeap)
{
    return minHeap->sizeOfHeap == 0;
}
 

struct min_Heap_Node* extractMin(struct min_Heap* 
                                   minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
    struct min_Heap_Node* root = 
                   minHeap->Array[0];

    struct min_Heap_Node* lastNode = 
         minHeap->Array[minHeap->sizeOfHeap - 1];
    minHeap->Array[0] = lastNode;

    minHeap->position[root->vert] = minHeap->sizeOfHeap-1;
    minHeap->position[lastNode->vert] = 0;
 
    // Reduce heap sizeOfHeap and heapify root
    --minHeap->sizeOfHeap;
    minHeapify(minHeap, 0);
 
    return root;
}
 
void DecreasingKey(struct min_Heap* minHeap, 
                         long int vert, long int distance)
{
    
    long int a = minHeap->position[vert];
 
    
    minHeap->Array[a]->distance = distance;
 
    while (a && minHeap->Array[a]->distance < 
           minHeap->Array[(a - 1) / 2]->distance)
    {
        // Swap this node with its parent
        minHeap->position[minHeap->Array[a]->vert] = 
                                      (a-1)/2;
        minHeap->position[minHeap->Array[
                             (a-1)/2]->vert] = a;
        swapMinHeapNode(&minHeap->Array[a],  
                 &minHeap->Array[(a - 1) / 2]);

        a = (a - 1) / 2;
    }
}
 
long int isInMinHeap(struct min_Heap *minHeap, long int vert)
{
   if (minHeap->position[vert] < minHeap->sizeOfHeap)
     return 1;
   return 0;
}

void printArr(long int distance[], long int n)
{
    printf("Vertex   Distance from Source\n");
    for (long int a = 0; a < n; ++a)
        printf("%ld \t\t %ld\n", a, distance[a]);
}
 

void dijkstra(struct graph* graph, long int src)
{
    
    long int Vert = graph->Vert;
    long int distance[Vert];     
    struct min_Heap* minHeap = createMinHeap(Vert);
 
    for (long int vert = 0; vert < Vert; ++vert)
    {
        distance[vert] = INT_MAX;
        minHeap->Array[vert] = newMinHeapNode(vert, 
                                      distance[vert]);
        minHeap->position[vert] = vert;
    }
 
    minHeap->Array[src] = 
          newMinHeapNode(src, distance[src]);
    minHeap->position[src]   = src;
    distance[src] = 0;
    DecreasingKey(minHeap, src, distance[src]);
 
   
    minHeap->sizeOfHeap = Vert;

    while (!isEmpty(minHeap))
    {
        
        struct min_Heap_Node* minHeapNode = 
                     extractMin(minHeap);
       
        long int u = minHeapNode->vert; 

        struct adjacencyListNode* pCrawl =
                     graph->Array[u].before;
        while (pCrawl != NULL)
        {
            long int vert = pCrawl->destination;
 
            if (isInMinHeap(minHeap, vert) && 
                      distance[u] != INT_MAX && 
              pCrawl->wt + distance[u] < distance[vert])
            {
                distance[vert] = distance[u] + pCrawl->wt;
 
                // update distance 
                // value in min heap also
                DecreasingKey(minHeap, vert, distance[vert]);
            }
            pCrawl = pCrawl->nxt;
        }
    }
    printArr(distance, Vert);
}
 
void UsingAdjacencyList()
{

    long int vert , edj ,src, des,wt,start;

    printf("ENTER THE NUMBER OF VERTICES  :  ");
    scanf("%ld", & vert);

    printf("\nENTER THE NUMBER OF EDGES   :  ");
    scanf("%ld", & edj);

    struct graph* graph = CreatingGraph(vert);
    printf("\n\nEnter the NODE NUMBERS where EDGE is present ...format--->(a b)\n");
    for (long int a = 0; a < edj; a++)
    {
        printf("EDGE %ld           ----> ", a + 1);
        scanf("%ld%ld", &src, & des);
        printf("ENTER IT'S WEIGHT  ----> ");
        scanf("%ld", &wt);
        AddingEdge(graph, src, des, wt);

    }
    printf("\nEnter the starting node:");
	scanf("%ld",&start);

    dijkstra(graph, start);
 
}


void main() {
    long int var;
    printf("Enter 1 for implementing DIJKSTRA'S USING ADJ. MATRIX...\n");
    printf("Enter 2 for implementing DIJKSTRA'S USING ADJ. LIST...\n");
    printf("PLEASE ENTER YOUR CHOICE : ");
    scanf("%ld", &var);
    if (var == 1) 
    {
        UsingAdjacencyMatrix();
    } 
    else if (var == 2) 
    {
        UsingAdjacencyList();
    } 
    else 
    {
        printf("ENTER A VALID NO.");
    }

}
