// Program to print all paths of length 'n' from a given vertex of an undirected graph

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES    9

// Data structure definitions

// Value to be stored at each node
//typedef char Data;

//  Graph's node/vertex
typedef struct node_s
{
    //Data  val;  // vertex value
    int   dest; // vertex location
    struct node_s *next; // next vertex
} Node;
 
// Graph's adjacency list
typedef struct adjList_s
{
    Node *head;  // head of the list
} AdjList;
 
// Graph is an array of adjacency lists
typedef struct graph_s
{
    int      v_count; // Number of vertices in the graph
    AdjList *vertices;// List of vertices
} Graph;
 
 
// Function proto types
Node* new_node(int dest);
Graph* new_graph(int V);
void print_graph(Graph* graph);
int print_all_paths_helper(Graph *g, int s, int n, int visited[],
                              int path[], int *path_index, int *paths_count);
int print_all_paths_of_len_n(Graph *g, int s, int n);                           


// Create a new node with the given val
Node* new_node(int dest)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    
    if (new_node == NULL)
    {
        printf("-E- New node creation FAILED: Out of memory!\n");
        return new_node;
    }
    
    new_node->dest = dest;
    new_node->next = NULL;
    
    return new_node;
}
 
// Create a graph of V vertices
Graph* new_graph(int V)
{
    int v_iter;
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    
    if (graph == NULL)
    {
        printf("-E- New graph creation FAILED: Out of memory!\n");
        return graph;
    }
    
    // Initialize the graph members
    graph->v_count = V;
 
    // Create the adjacency list of size 'V'
    graph->vertices = (AdjList*) malloc(V * sizeof(AdjList));
 
    // Mark each adjacency list as empty
    for (v_iter = 0; v_iter < V; ++v_iter)
        graph->vertices[v_iter].head = NULL;
 
    return graph;
}
 
// Add an edge to the undirected graph
void add_edge(Graph* graph, int src, int dest)
{
    Node* vertex = NULL;
    
    // Input validation
    if ((src >= MAX_VERTICES) || (dest >= MAX_VERTICES))
    {
        printf("-E- Source %c and/or Destination %c OUT OF RANGE!\n", 'A' + src, 'A' + dest);
        return;
    }
    
    vertex = new_node(dest);
    if (vertex == NULL) return;
    
    // Add an edge from src to dest at the begining and update the head. 
    vertex->next = graph->vertices[src].head;
    graph->vertices[src].head = vertex;
 
    // Since the graph is undirected, add an edge from dest to src also
    vertex = new_node(src);
    if (vertex == NULL) return;
    
    vertex->next = graph->vertices[dest].head;
    graph->vertices[dest].head = vertex;
}
 
// print the adjacenncy list representation of graph
void print_graph(Graph* graph)
{
    int v_iter;
    Node *list;
    
    for (v_iter = 0; v_iter < graph->v_count; v_iter++)
    {
        list = graph->vertices[v_iter].head;
        if (list)
            printf("\n Adjacency list of vertex %c\n head ", 'A' + v_iter);
            
        while (list)
        {
            printf("-> %c", 'A' + list->dest);
            list = list->next;
        }
        printf("\n");
    }
}

// A recursive function to print all paths of length 'n' from 's'
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
// Returns no.of paths found
int print_all_paths_helper(Graph *g, int s, int n, int visited[],
                              int path[], int *path_index, int *paths_count)
{
    // Mark the current node and store it in path[]
    visited[s] = 1;
    path[(*path_index)++] = s;
 
    // base condition: if required length is met then print current path[]
    if (*path_index == (n + 1))
    {
        for (int i = 0; i < *path_index; i++)
            printf("%c ", 'A' + path[i]);
        printf("\n");
        
        (*paths_count)++;
    }
    else // path length is not sufficient
    {
        // Recur for all the vertices adjacent to current vertex
        Node *list = g->vertices[s].head;
        
        while (list)
        {
            if (!visited[list->dest])
                print_all_paths_helper(g, list->dest, n, visited, path, path_index, paths_count);
                
            list = list->next;
        }
    }
 
    // Remove current vertex from path[] and mark it as unvisited
    path[(*path_index)--] = 0;
    visited[s] = 0;
}

// Prints all paths from 's' of given length 'n'
int print_all_paths_of_len_n(Graph *g, int s, int n)
{
    int visited[MAX_VERTICES] = {0, };  // to start with mark all the vertices as not visited
    int path[MAX_VERTICES] = {0, }; //  array to store paths
    int path_index = 0, paths_count = 0;
 
    // Input validation
    if (s >= MAX_VERTICES)
    {
        printf("-E- Source %c doesn't exist!\n", 'A' + s);
        return paths_count;
    }
    
    // Call the recursive helper function to print all paths
    print_all_paths_helper(g, s, n, visited, path, &path_index, &paths_count);
    return paths_count;
}
  
// Define the graph and print the required path
int main()
{
    // create the fully connected 3x3 grid into a graph
    Graph* graph = new_graph(MAX_VERTICES);
    
    // vertices are mapped to numbers for the ease of use
    // i.e A-->0, B-->1, ... I-->8
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 3);
    add_edge(graph, 0, 4);
    
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    add_edge(graph, 1, 5);
 
    add_edge(graph, 2, 4);
    add_edge(graph, 2, 5);
    
    add_edge(graph, 3, 4);
    add_edge(graph, 3, 6);
    add_edge(graph, 3, 7);
    
    add_edge(graph, 4, 5);
    add_edge(graph, 4, 6);
    add_edge(graph, 4, 7);
    add_edge(graph, 4, 8);
    
    add_edge(graph, 5, 7);
    add_edge(graph, 5, 8);
    
    add_edge(graph, 6, 7);
    
    add_edge(graph, 7, 8);
    
    // debug util: print the adjacency list representation of the above graph
    //print_graph(graph);
    printf("No.of paths found are: %d\n", print_all_paths_of_len_n(graph, 0, 3));
 
    return 0;
}
