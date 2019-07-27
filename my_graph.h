// George Dunnery
// Assignment 5 Graphs
// February 11 2019

// =================== Support Code =================
// Graph.
//
//
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================

#ifndef MYGRAPH_H
#define MYGRAPH_H



// ================================================================================================
// ======================================= PART 1 =================================================
// ================================================================================================



// ====================== Structs =================================================================
// Create a neighbor data structure to server as the neighbor's list.
// In our case, we will stores 'integers' as our neighbors that 
// corresponding to the data that the actual nodes store.
typedef struct neighbor{
	int data;
	struct neighbor * next;
}neighbor_t;

// Create a node data structure to store data within
// our graph. In our case, we will store 'integers'
// as our data in the nodes
typedef struct node{
    // The visited field is used during traversal algorithms
    int visited;
	int data;
	// "Present Nodes": The next field points to the next node in the linked list
	// of nodes contained in the graph. This list says nothing about the edges in the graph.
	// Rather it simply declares which nodes are present in the graph.
	struct node *next;
	// "Adjacency List": The neighbor field points to the head node in a singly linked list of
	// this nodes immediate neighbors.
	struct neighbor * neighbor;
}node_t;

// Create a graph data structure
// Our graph keeps track of the number of nodes, the number of edges and an array
// of all the nodes in the graph, and the maximum number of nodes we store in our graph.
typedef struct graph{
	int numNodes;		
	int numEdges;
	// Pointer to the head of the linked list storing the nodes which are
	// present in the graph. Must check the neighbor field of a node to
	// determine the node's immediate neighbors.
	node_t* nodes;	 //an array of nodes storing all of our nodes. (linked list)
}graph_t;

// ================= Initializers =================================================================
// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
graph_t* create_graph(){
	// Allocate memory for the graph's data.
	graph_t* myGraph = (graph_t*)malloc(sizeof(graph_t));
	// Default values reflecting an empty graph are used for initialization.
	myGraph->numEdges = 0;
	myGraph->numNodes = 0;
	myGraph->nodes = NULL;
	// A pointer to the heap of memory for the new graph is returned.
	return myGraph;
}

// Creates a node
// Returns a pointer to a newly created node
// The node is initialized with data on the heap
// The data field is set to the given integer 'item'
// The other node fields are initialized to default values
node_t* create_node(int item){
    node_t* myNode = (node_t*)malloc(sizeof(node_t));
    // Store the given data (integer).
    myNode->data = item;
    // Default pointers of NULL are initialized upon creation.
    myNode->next = NULL;
    myNode->neighbor = NULL;
    // Initialize nodes as unvisited
    myNode->visited = 0;
    return myNode;
}

// Creates a neighbor
// Returns a pointer to a newly created neighbor
// The neighbor is initialized with data on the heap
// Neighbor's data field is set to the item
// Neighbor's neighbor field is initialized to NULL
neighbor_t* create_neighbor(int item) {
    neighbor_t* myNeighbor = (neighbor_t*)malloc(sizeof(neighbor_t));
    myNeighbor->data = item;
    myNeighbor->next = NULL;
    return myNeighbor;
}

// =============  Function Declarations ===========================================================
// Functions are declared here so that they may be used
// before the code block containing their actual definition.
int contains_node( graph_t * g, int value);
node_t* node_add_node(node_t* existing, node_t* newNode);
int check_nodes(node_t* n, int value);
node_t* node_remove_node(node_t* n, int item);
node_t* locate_node(node_t* n, int value);
neighbor_t* add_neighbor(neighbor_t* existing, neighbor_t* edge);
neighbor_t* remove_neighbor(graph_t* g, neighbor_t* start, int destination);
int contains_edge(graph_t * g, int source, int destination);
int numNeighbors(graph_t * g, int value);
unsigned int graph_num_nodes(graph_t* g);
void free_node(node_t* n);
void free_neighbor(neighbor_t* neighbor);

// =============== Functions for Part 1 ===========================================================

// Graph Empty
// Check if the graph is empty
// Returns 0 if true (The graph is completely empty, i.e. numNodes == 0 )
// Returns -1 if false (the graph has at least one node)
int graph_empty(graph_t* g) {
    // NULL graphs are empty
    if (g == NULL) {
        return 0;
    }
    if (g->numNodes == 0) {
        return 0;
    }
    // Otherwise, the graph is not empty.
    return -1;
}

// Adds a new node with the corresponding item in the graph.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
// Duplicates nodes should not be added. For a duplicate node returns 0.
int graph_add_node(graph_t* g, int item){
    // Prevent the addition of a duplicate node and return 0.
    if (contains_node(g,item) == 0) {
        return 0;
    }
    // If the node is not a duplicate, continue onwards.
    // Create the node
    node_t* myNode = create_node(item);
    // Check if memory allocation failed
    if (myNode == NULL) {
        free(myNode);
        return -1;
    }
    // Set it as the head node if there isn't a head node yet.
    if (g->nodes == NULL) {
        g->nodes = myNode;
    }
    // Otherwise, place the node into the list in ascending order
    else {
        // Recursive helper handles insertion to the correct position
        // Reassign the head node if necessary
        g->nodes = node_add_node(g->nodes, myNode);
    }
    // Duplicates and memory failures have already been filtered out
    g->numNodes++;
    return 0;
}

// Helper method to recursively add the nodes
// Duplicates have already been filtered out
node_t* node_add_node(node_t* existing, node_t* newNode){
    if (existing->next == NULL){
        existing->next = newNode;
        // The preceding nodes should remain unchanged.
        return existing;
    }
    // Continue recursion until the end of the list is found
    else {
        existing->next = node_add_node(existing->next, newNode);
        return existing;
    }
}

// Helper method to print out the 'nodes' field of the graph_t
// Intended to assist debugging & testing
// Should be called with a reference from the graph, print_node_list(graph->nodes);
void print_node_list(node_t* n) {
    // Empty
    if (n == NULL) {
        printf("\n");
        return;
    }
    // Base Case: Print the last node and finish
    if (n->next == NULL) {
        printf("%d\n", n->data);
        return;
    }
    // Recursive Step: Print this node, pass it on to the next
    printf("%d ", n->data);
    print_node_list(n->next);
}

// Removes the node from the graph and the corresponding edges connected 
// to the node.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (the node to be removed doesn't exist in the graph).
int graph_remove_node(graph_t* g, int item){
    // NULL graphs always return -1
    if (g == NULL) {
        return -1;
    }
    // Check if the node exists in the graph
    if (contains_node(g,item) == -1) {
        return -1;
    }
    // REMOVE ALL EDGES:
    // (1) Delete incoming edges (i.e. edges from other nodes to this node)
    node_t* iterator = g->nodes;
    while (iterator != NULL) {
        // Look through all the neighbors for the given value and remove it
        if (iterator->neighbor != NULL) {
            iterator->neighbor = remove_neighbor(g, iterator->neighbor,item);
        }
        iterator = iterator->next;
    }
    // Subtract the number of neighbors this node has from numEdges before freeing
    g->numEdges -= numNeighbors(g,item);
    // Decrement the nodes to reflect this removal
    g->numNodes--;
    // (2) & (3) Delete outgoing edges and the node itself
    // Helper function will call free_node, which then calls free_neighbor
    g->nodes = node_remove_node(g->nodes,item);
    return 0;
}

// Helper function for graph_remove_node
// Removes a node from the linked list
// Frees the node and its neighbor linked list
node_t* node_remove_node(node_t* n, int item) {
    // Remove this node
    if (n->data == item) {
        // Save this node's next node before deleting it
        node_t* newNext = n->next;
        // Set next to NULL to prevent recursive delete
        n->next = NULL;
        // Ready to delete this node
        free_node(n);
        return newNext;
    }
    // Should not encounter NULL since the calling function determined
    // node's existence with contains_node()
    n->next = node_remove_node(n->next, item);
    return n;
}


// Adds an edge from source to destination.
// If source or destination is not found in the graph returns -1.
// Otherwise it returns 0 (even for trying to add a duplicate edge)
int graph_add_edge(graph_t * g, int source, int destination){
    // Check if the source and destination exist, return -1 if they don't
    if (contains_node(g, source) == 0 && contains_node(g,destination) == 0) {
        // Return 0 if the edge already exists (but don't add a new one)
        if (contains_edge(g,source,destination) == -1) {
            // Locate the source node in the list of nodes to access its neighbor field
            node_t *start = locate_node(g->nodes, source);
            // Add a directed edge (duplicates will be handled by the helper function)
            neighbor_t *newNeighbor = create_neighbor(destination);
            // Check if memory allocation failed
            if (newNeighbor == NULL) {
                // Operation failed due to memory allocation
                return -1;
            }
            start->neighbor = add_neighbor(start->neighbor, newNeighbor);
            // When a new edge actually is added, increment the numEdges
            g->numEdges++;
        }
        return 0;
    }
    // Operation failed due to source or destination not existing
	return -1;
}

// Helper method that returns a pointer to the node of the given value
// Should be called with some reference to the graph, locate_node(g->nodes, value)
node_t* locate_node(node_t* n, int value) {
    // Base Case: found the node we are looking for
    if (n->data == value) {
        return n;
    }
    return locate_node(n->next, value);
}

// Helper function to add a neighbor to the neighbor linked list of a node
// Prevents duplicates
neighbor_t* add_neighbor(neighbor_t* existing, neighbor_t* edge) {
    // When the end is reached, add the new neighbor
    if (existing == NULL) {
        return edge;
    }
    // Allow the new neighbor to be set as the next field if necessary
    existing->next = add_neighbor(existing->next, edge);
    // Preceding neighbors should remain unchanged
    return existing;
}

// Helper function to print the neighbor linked list of a node
void print_neighbor(neighbor_t* neighbor) {
    if (neighbor == NULL) {
        printf("\n");
        return;
    }
    printf("%d ", neighbor->data);
    print_neighbor(neighbor->next);
}

// Removes an edge from source to destination.
// If source or destination is not found in the graph returns -1.
// If no such edge exists also returns -1.
// Otherwise it returns 0
int graph_remove_edge(graph_t * g, int source, int destination){
    // Check if the edge exists
    // Also handles checking if the nodes exist in this graph
    if (contains_edge(g,source,destination) == 0) {
        // Locate the source node to access its neighbor list
        node_t* sourceNode = locate_node(g->nodes,source);
        if (sourceNode->neighbor != NULL) {
            sourceNode->neighbor = remove_neighbor(g, sourceNode->neighbor, destination);
            return 0;
        }
    }
    // Source or destination wasn't found, or no such edge exists
	return -1;
}

// Helper function to recursively find and remove the given neighbor
neighbor_t* remove_neighbor(graph_t* g, neighbor_t* start, int destination) {
    // If the next neighbor was null, bounce back
    // NULL handling required for graph_remove_node
    if (start == NULL) {
        return NULL;
    }
    else if (start->data == destination) {
        // Save this neighbor's next neighbor, return this to relink the list
        neighbor_t* newNext = start->next;
        // Set the next field of the neighbor which will be removed to NULL
        // to prevent accidentally deleting all the remaining neighbors
        start->next = NULL;
        // Ready to remove the neighbor
        free_neighbor(start);
        // Record that an edge was removed
        g->numEdges--;
        // Return the removed neighbor's next field to maintain list integrity
        return newNext;
    }
    start->next = remove_neighbor(g, start->next, destination);
    return start;
}

// Returns 0 if the node with value is in the graph, otherwise returns -1;
int contains_node( graph_t * g, int value){
    if (g == NULL) {
        return -1;
    }
    // Call recursive helper to handle this request
   	return check_nodes(g->nodes, value);
}

// Helper function for contains_node
// Recursively explores the list of nodes that exist in the graph
// Returns 0 when if the node is found, otherwise returns -1
// Should be called with a reference from the graph, check_nodes(graph->nodes);
int check_nodes(node_t* n, int value) {
    // If a NULL node is reached, the value was not found
    if (n == NULL) {
        return -1;
    }
    // If a node with that value is found, return 0
    if (n->data == value) {
        return 0;
    }
    else {
        return check_nodes(n->next, value);
    }
}

//Returns 0 if an edge from source to destination exists, -1 otherwise.
int contains_edge(graph_t * g, int source, int destination){
    // Check if the nodes actually exist
    if (contains_node(g,source) == 0 && contains_node(g,destination) == 0){
        // Locate the source node to access its neighbor list
        neighbor_t* n = locate_node(g->nodes,source)->neighbor;
        // Look through the neighbors for the given value
        while (n!= NULL) {
            // Check if neighbor was found
            if (n->data == destination) {
                return 0;
            }
            // Go to the next neighbor
            n = n->next;
        }
    }
    // Neighbor was not found, or source / destination did not exist
	return -1;
}
// Returns an int array of all the neighbors of the node with data=value.
// Null graphs and nodes that don't exist always return pointer to an empty array
// Contains commented print statements which printed the array contents for testing
int * getNeighbors(graph_t * g, int value){
    // Find the number of integers that need to be stored
    int size = numNeighbors(g,value);
    // Initialize an array and allocate enough memory for the integers
    int* neighborArray;
    neighborArray = malloc(size * sizeof(int));
    // Only continue if the array is not empty
    if (size > 0) {
        // Locate the node 'value', and set iterator to the head node neighbor
        neighbor_t* iterator = (locate_node(g->nodes, value))->neighbor;
        int position = 0;
        while (iterator != NULL) {
            // Store the integer data found at the neighbor node
            neighborArray[position] = iterator->data;
            // Go to the next neighbor
            iterator = iterator->next;
            // Move one position ahead in the array
            position++;
        }
    }
    // Return a pointer to the array
    // Skip to this step for empty arrays
    return neighborArray;
}

// Helper method to print out the neighbor array
void print_neighbor_array(int* array, int size) {
    int i;
    printf("Array:");
    for (i = 0; i < size; i++) {
        printf(" %d", array[i]);
    }
    printf("\n");
}

// Returns the number of neighbors for value.
// Null graphs and nodes that don't exist always return 0
int numNeighbors(graph_t * g, int value){
    int count = 0;
    // Make sure the graph isn't null
    if (g != NULL) {
        // Make sure the node exists
        if (contains_node(g,value) == 0) {
            node_t* mainNode = locate_node(g->nodes, value);
            neighbor_t* iterator = mainNode->neighbor;
            // Increment the count as the neighbors are reached
            // Finish when the next neighbor is null
            while (iterator != NULL) {
                count++;
                iterator = iterator->next;
            }
        }
    }
	return count;
}

// ***
// Original Location of the graph_print() function
// It has been moved down to the section labelled
// "PART 2" since it uses BFS
// Sorry if this causes any inconvenience when grading!
// ***

// Graph Size
// Returns the number of nodes in the graph
unsigned int graph_num_nodes(graph_t* g){
    if (g == NULL) {
        return 0;
    }
    return (unsigned int) g->numNodes;

}

// Graph Size
// Returns the number of edges in the graph
unsigned int graph_num_edges(graph_t* g){
    if (g == NULL) {
        return 0;
    }
    return (unsigned int) g->numEdges;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
void free_graph(graph_t* g){
    if (g == NULL) {
        free(g);
        return;
    }
    // Free the nodes, which then also free their neighbors
    free_node(g->nodes);
    // Lastly, free the graph itself
    free(g);
}

// Helper function to free_graph
// Handles freeing the nodes
// Calls another helper function to free the neighbors
void free_node(node_t* n) {
    // Create references to this node and the next one
    node_t* iterator = n;
    node_t* next;
    // Handle a null node passed to free
    if (n == NULL) {
        free(n);
        return;
    }
    // When the null node is reached, there are no more nodes to free
    while (iterator != NULL) {
        // Capture the next node in the linked list before it is lost
        next = iterator->next;
        // Free all neighbors in this nodes neighbor linked list
        free_neighbor(iterator->neighbor);
        // Free this node
        free(iterator);
        // Move on to the next node
        iterator = next;
    }
}


// Helper function to free_graph and free_nodes
// Handles freeing the neighbors of the calling node
void free_neighbor(neighbor_t* neighbor) {
    // Create references for this neighbor and the next one
    neighbor_t* iterator = neighbor;
    neighbor_t* next;
    // Handle null neighbor passed to free
    if (neighbor == NULL) {
        free(neighbor);
        return;
    }
    // When the null neighbor is reached, there are no more neighbors to free
    while (iterator != NULL) {
        // Capture the next neighbor before it is lost
        next = iterator->next;
        // Free this neighbor
        free(iterator);
        // Move on to the next neighbor
        iterator = next;
    }
}


// ================================================================================================
// ============================== PART 2 ==========================================================
// ================================================================================================


// ================== Structs =====================================================================

// Nodes that are specifically for the queue / stack
typedef struct q_node{
    int data;
    struct q_node* next;
}q_node_t;

// Structure to represent the entire queue
// Has pointers to the head and tail q_nodes of the linked list for O(1) operations
typedef struct queue{
    int size;
    q_node_t* head;
    q_node_t* tail;
}queue_t;

// Structure to represent a stack
// Also uses the q_node for its linked list
typedef struct stack{
    int size;
    q_node_t* top;
}stack_t;

// ================= Initializers =================================================================

// Initializes an empty queue with default values
// Queue will use linked list for dynamic scaling
queue_t* create_queue() {
    queue_t* myQueue = (queue_t*)malloc(sizeof(queue_t));
    // How many elements are in the queue
    myQueue->size = 0;
    // Points to the first element of the queue
    myQueue->head = NULL;
    // Points to the last element of the queue
    myQueue->tail = NULL;
    return myQueue;
}

// Creates a queue node with the given data
// Using linked list for dynamic scaling
q_node_t* create_Q_node(int value) {
    q_node_t* myQNode = (q_node_t*)malloc(sizeof(q_node_t));
    myQNode->data = value;
    myQNode->next = NULL;
    return myQNode;
}

// Creates a stack structure, also uses q_nodes
// Initializes default values
// Stack will use linked list for dynamic scaling
stack_t* create_stack() {
    stack_t* myStack = (stack_t*)malloc(sizeof(stack_t));
    myStack->size = 0;
    myStack->top = NULL;
    return myStack;
}

// ================= Function Declarations ========================================================
void free_Q_node(q_node_t* qNode);
void free_queue(queue_t* q);
void unvisit_all(graph_t* g);
int depth_first_search(graph_t* g, stack_t* s);
void dfs_path(graph_t* g, stack_t* s, int destination);
void pathify(stack_t* s);

// ================= Queue Functions ==============================================================

// Check if a queue is empty
// Returns 0 when empty, or -1 otherwise
int queue_empty(queue_t* q) {
    // Handle NULL queue
    if (q == NULL) {
        return 0;
    }
    // Return 0 when size is 0
    if (q->size == 0) {
        return 0;
    }
    // Otherwise, queue is not empty
    return -1;
}

// Returns the value of the head q_node in the queue
// Does not remove the value
// Calling this function on a NULL or empty queue crashes the program!
int queue_peek(queue_t* q) {
    if (q == NULL) {
        free(q);
        exit(1);
    }
    if (q->head == NULL) {
        free(q);
        exit(1);
    }
    return q->head->data;
}

// Removes the head node of the queue
void queue_pop_head(queue_t* q) {
    // Filter out NULL queues
    if (q == NULL) {
        return;
    }
    // Do nothing if the queue has no head (i.e. is empty)
    if (q->head == NULL) {
        return;
    }
    // Otherwise, pop the head node
    // Capture the reference to next
    q_node_t* newHead = q->head->next;
    // Pop the node
    free(q->head);
    // Set the new head node
    q->head = newHead;
    // Keep track of the queue size
    q->size--;
}

// Add another element to the back of the queue
// Returns 0 on success, -1 otherwise
int queue_append(queue_t* q, int value) {
    // Handle null
    if (q == NULL) {
        return -1;
    }
    // Create the new q_node
    q_node_t* qNode = create_Q_node(value);
    // Check for memory allocation failure
    if (qNode == NULL) {
        return -1;
    }
    // Add the q_node to the linked list
    // Special Case: Appending to an empty queue
    if (queue_empty(q) == 0) {
        q->head = qNode;
        q->tail = qNode;
    }
    else {
        // Link the tail node to the newly appended node
        q->tail->next = qNode;
        // Update the queue's tail to the newly appended node
        q->tail = qNode;
    }
    // Keep track of the queue size
    q->size++;
    // Operation was successful
    return 0;
}

// Helper function that prints out the queue
// Meant to assist queue testing
void queue_print(queue_t* q) {
    // Handle NULL
    if (q == NULL) {
        return;
    }
    // Print nothing if there are no elements
    if (q->size == 0) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    // Follow the linked list and print values
    q_node_t* iterator = q->head;
    while (iterator != NULL) {
        printf(" %d", iterator->data);
        iterator = iterator->next;
    }
    printf("\n");
}

// Frees the memory associated with a queue
// Calls a helper method to free the q_nodes
void free_queue(queue_t* q) {
    if (q == NULL) {
        free(q);
        return;
    }
    // Free all the queue nodes first
    free_Q_node(q->head);
    // Then free the queue itself
    free(q);
}

// Frees the memory associated with q_nodes
// Travels down the linked list, removing all nodes from the queue
void free_Q_node(q_node_t* qNode) {
    // Create references to this q_node and the next
    q_node_t* iterator = qNode;
    q_node_t* next;
    // Handle NULL
    if (qNode == NULL) {
        free(qNode);
        return;
    }
    // Iterate through all the queue nodes
    while (iterator != NULL) {
        // Capture next before it's lost
        next = iterator->next;
        // Free the current q_node
        free(iterator);
        // Move on to the next q_node in the linked list
        iterator = next;
    }
}

// ================= Stack Functions ==============================================================

// Check if the stack is empty
// Returns 0 when the stack is empty, otherwise -1
int stack_empty(stack_t* s) {
    if (s == NULL) {
        return 0;
    }
    if (s->size == 0) {
        return 0;
    }
    return -1;
}

// Pushes a new element to the stack
// Returns 0 on success, -1 otherwise
int stack_push(stack_t* s, int value) {
    if (s == NULL) {
        return -1;
    }
    // Create the new node
    q_node_t* newDish = create_Q_node(value);
    // Check if memory allocation failed
    if (newDish == NULL) {
        return -1;
    }
    // Add to an empty stack
    if (s->top == NULL) {
        s->top = newDish;
    }
    // Add to non-empty stack
    else {
        // Capture the old top node as the new node's next
        newDish->next = s->top;
        // Set the new top node
        s->top = newDish;
    }
    // Keep track of the size
    s->size++;
    // Operation was successful
    return 0;
}

// Check the top value of the stack
// No changes are made to the stack
// Not to be called on an empty/null stack
int stack_peek(stack_t* s) {
    // No reasonable return possible, thus crash
    if (s == NULL || s->top == NULL) {
        free(s);
        exit(1);
    }
    // Return the value of the top node
    return s->top->data;
}

// Remove the top value from the stack
void stack_pop(stack_t* s) {
    // Do nothing for NULL
    if (s == NULL || s->top == NULL) {
        return;
    }
    // Capture reference to the next node
    q_node_t* under = s->top->next;
    // Use generic free since free_Q_node will delete the whole list
    free(s->top);
    // Set the new top
    s->top = under;
    // Keep track of the size
    s->size--;
}

// Clear the memory associated with a stack
// Also clears nodes by calling a helper
void free_stack(stack_t* s) {
    // Check for the null stack
    if (s == NULL) {
        free(s);
        return;
    }
    // Otherwise, free all the nodes
    free_Q_node(s->top);
    // Then free the stack
    free(s);
}

// ================= Part 2 Functions =============================================================

// Function to reset the visited field on all nodes
void unvisit_all(graph_t* g) {
    // Handle NULL
    if (g == NULL) {
        return;
    }
    // Do nothing if the graph is empty
    if (graph_empty(g) == 0) {
        return;
    }
    // Otherwise, iterate through graph's linked list of nodes, setting visited = 0
    node_t* iterator = g->nodes;
    while (iterator != NULL) {
        iterator->visited = 0;
        iterator = iterator->next;
    }
}

// REQUIRED FUNCTION
// Determines if there is a path from the source to the destination node
// Uses Breadth First Search
// Returns 0 if the destination can be reached, -1 otherwise
// Note: Returns -1 if destination can't be reached, node doesn't exist, or the graph is null
int is_reachable(graph_t * g, int source, int dest) {
    // Filter out NULL graphs
    if (g == NULL) {
        //printf("Graph is NULL.\n");
        return -1;
    }
    // Filter out empty graphs
    if (graph_empty(g) == 0) {
        //printf("Graph is empty.\n");
        return -1;
    }
    if (contains_node(g, source) == 0 && contains_node(g, dest) == 0) {
        // ===== BREADTH FIRST SEARCH: IS REACHABLE ======================
        // Make sure all nodes are set to unvisited before starting
        unvisit_all(g);
        // Initialize the queue with the source node ('source')
        queue_t* bfsQ = create_queue();
        queue_append(bfsQ, source);
        // Take the first value from the queue, and explore the corresponding node's neighbors
        while (queue_empty(bfsQ) == -1) {
            // Capture the number of the node
            int nodeData = queue_peek(bfsQ);
            // Find the corresponding node
            node_t* sourceNode = locate_node(g->nodes, nodeData);
            // Pop the head of the queue to prepare for the next iteration
            queue_pop_head(bfsQ);
            // Get array of neighbors for this node
            int* neighborArray = getNeighbors(g,sourceNode->data);
            int i;
            // Check for unvisited neighbors
            for (i = 0; i < numNeighbors(g,nodeData); i++) {
                // Locate the node corresponding to each neighbor
                node_t* neighborNode = locate_node(g->nodes, neighborArray[i]);
                // If this neighbor is the destination, finish and return 0
                if (neighborNode->data == dest) {
                    // Make sure to free everything before terminating the function
                    free(neighborArray);
                    free_queue(bfsQ);
                    return 0;
                }
                // Append the queue if the neighboring node has not yet been visited
                if (neighborNode->visited == 0) {
                    queue_append(bfsQ, neighborNode->data);
                    neighborNode->visited = 1;
                }
                // Otherwise ignore it and move on to the next neighbor
            }
            // After for loop, free the neighbor array for each while loop iteration
            free(neighborArray);
        }
        // Free the queue before ending
        free_queue(bfsQ);
        // Otherwise, not found and return -1
        // ===== END BFS IS REACHABLE ====================================
    }
    return -1;
}

// REQUIRED FUNCTION
// Determines if there is a cycle in the graph
// Uses Depth First Search
// Returns 0 if there is a cycle in the graph, -1 otherwise
// Note: Returns -1 if the graph is null
int has_cycle(graph_t * g) {
    // Handle NULL graph
    if (g == NULL) {
        return -1;
    }
    // Initialize result to -1
    int result = -1;
    int i;
    // Pick a node to start with
    node_t* start = g->nodes;
    for (i = 0; i < g->numNodes; i++) {
        // Prepare the nodes by resetting their visited status
        unvisit_all(g);
        // Create a stack for this run
        stack_t* dfsStack = create_stack();
        // Push the data from the starting node to the stack to represent it
        // This node will be the 'root node' from the perspective of the DFS
        stack_push(dfsStack, start->data);
        // Call depth first search
        // If cycle encountered, ends and returns -1
        // Otherwise, runs dfs on all nodes and finishes with 0
        result = depth_first_search(g,dfsStack);
        // Free the stack to prevent memory leaks
        free_stack(dfsStack);
        if (result == 0) {
            break;
        }
        // Locate the node for the next iteration
        if (start->next != NULL) {
            node_t *source = locate_node(g->nodes, start->next->data);
            // Reassign start for the next iteration
            start = source;
        }
    }
    return result;
}

// Helper function to has_cycle
// Returns 0 if there is a cycle in the graph, -1 otherwise
int depth_first_search(graph_t* g, stack_t* s) {
    // If there is nothing in the stack, there is nothing to do here.
    if (stack_empty(s) == 0) {
        return -1;
    }
    // Set the current integer to top of stack
    int current = stack_peek(s);
    // Pop the stack
    //stack_pop(s);
    // Get the neighbors of the current node
    int* neighborArray = getNeighbors(g,current);
    int i;
    int result = -1;
    node_t* neighborNode;
    // Check for unvisited neighbors
    for (i = 0; i < numNeighbors(g,current); i++) {
        // Find the corresponding node
        neighborNode = locate_node(g->nodes, neighborArray[i]);
        // If it is unvisited, recursive dfs call
        if (neighborNode->visited == 0) {
            // Set visited status
            neighborNode->visited = 1;
            // Push this node's integer data to the stack
            stack_push(s,neighborNode->data);
            // Then call dfs
            result = depth_first_search(g,s);
        }
        // If it is visited, we have found a cycle
        else if (neighborNode->visited == 1) {
            // Break the loop and indicate 0 for cycle presence
            result = 0;
            break;
        }
    }
    // Free neighbor array after for loop
    free(neighborArray);
    // Stack is freed by calling function, has_cycle
    return result;
}

// REQUIRED FUNCTION
// Prints any path from the source to the destination, if one exists
// Otherwise, prints nothing
// Note: Nothing will be printed for null graphs, or if a node does not exist
void print_path(graph_t * g, int source, int dest) {
    // Handle null
    if (g == NULL) {
        return;
    }
    // Only enter if the node is_reachable
    // Use DFS to trace a path
    if (is_reachable(g,source,dest) == 0) {
        // Reset node visited status
        unvisit_all(g);
        // Create a stack for the DFS
        stack_t *dfsStack = create_stack();
        // Push the starting node to the stack, in this case source
        stack_push(dfsStack, source);
        // Prepare a nice format for the output
        printf("Path from %d to %d:",source,dest);
        // Call the dfs helper
        dfs_path(g, dfsStack, dest);
        // Get on a new line to keep output tidy
        printf("\n");
        free_stack(dfsStack);
    }
}

// Helper function to path print
// Uses DFS to print the path
void dfs_path(graph_t* g, stack_t* s, int destination) {
    // If there is nothing in the stack, there is nothing to do here.
    if (stack_empty(s) == 0) {
        return;
    }
    // Set the current integer to top of stack
    int current = stack_peek(s);
    // Pop the stack
    //stack_pop(s);
    // Get the neighbors of the current node
    int* neighborArray = getNeighbors(g,current);
    int i;
    node_t* neighborNode;
    // Check for unvisited neighbors
    for (i = 0; i < numNeighbors(g,current); i++) {
        // Find the corresponding node
        neighborNode = locate_node(g->nodes, neighborArray[i]);
        // If it is unvisited, recursive dfs call
        if (neighborNode->visited == 0) {
            // Set visited status
            neighborNode->visited = 1;
            // Push this node's integer data to the stack
            stack_push(s,neighborNode->data);
            // If this node is the destination, print path back to source
            if (neighborNode->data == destination) {
                pathify(s);
                // Break out of the for loop for final steps
                break;
            }
            // Otherwise, recursive call dfs_path
            else {
                dfs_path(g, s, destination);
                // Pop the stack on the way out
                stack_pop(s);
            }
        }
        // If it is already visited, ignore it
    }
    // Free neighbor array after for loop
    free(neighborArray);
}

// Helper function to print_path
// Transfers contents from original stack into a new stack
// This reverses the order, so now it will go from source to destination instead!
void pathify(stack_t* s) {
    // Create a second stack to push to
    // This will place the top of first stack in bottom of second stack
    stack_t* reverse = create_stack();
    while (s->top != NULL) {
        // Push the data from first stack to second stack
        stack_push(reverse, stack_peek(s));
        // Pop the first stack
        stack_pop(s);
    }
    // Now print and pop the second stack to print the correct direction
    while (reverse->top != NULL) {
        // Print the top
        printf(" %d",stack_peek(reverse));
        // Then pop
        stack_pop(reverse);
    }
    // Free the reversing stack before returning to dfs_print, print_path
    // print_path will take care of freeing the original stack
    free_stack(reverse);
}

// PROVIDED FUNCTION, MOVED DOWN FROM PART 1
// Prints the the graph using BFS
// For NULL or empty graph it should print nothing.
void graph_print(graph_t * g){
    // Filter out NULL graphs
    if (g == NULL) {
        printf("Graph is NULL.\n");
        return;
    }
    // Filter out empty graphs
    if (graph_empty(g) == 0) {
        printf("Graph is empty.\n");
        return;
    }
    // ===== BREADTH FIRST SEARCH: PRINT =================================
    // Make sure all nodes are set to unvisited before starting
    unvisit_all(g);
    // Initialize the queue with the source node
    // Source for graph_print is simply the first node in the nodes list
    queue_t* bfsQ = create_queue();
    queue_append(bfsQ, g->nodes->data);
    printf("Graph Print:");
    // Take the first value from the queue, and explore the corresponding node's neighbors
    while (queue_empty(bfsQ) == -1) {
        // Capture the number of the node and print it
        int nodeData = queue_peek(bfsQ);
        printf(" %d", nodeData);
        // Find the corresponding node
        node_t* sourceNode = locate_node(g->nodes, nodeData);
        // Pop the head of the queue
        queue_pop_head(bfsQ);
        // Get array of neighbors
        int* neighborArray = getNeighbors(g,sourceNode->data);
        int i;
        for (i = 0; i < numNeighbors(g,nodeData); i++) {
            // Locate the node corresponding to each neighbor
            node_t* neighborNode = locate_node(g->nodes, neighborArray[i]);
            // Append the queue if the neighboring node has not yet been visited
            if (neighborNode->visited == 0) {
                queue_append(bfsQ, neighborNode->data);
                neighborNode->visited = 1;
            }
            // Otherwise ignore it and move on to the next neighbor
        }
        // After the for loop has finished, free the neighbor array
        free(neighborArray);
    }
    printf("\n");
    // Free the queue before ending
    free_queue(bfsQ);
    // ===== END BFS PRINT ===============================================
}



#endif
