// George Dunnery
// Assignment 5 Graphs
// February 11 2019

// Compile this assignment with: gcc main.c -o main

// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// ====================================================
// =================== Unit Tests =====================
// ====================================================

// ================= Tests for Part 1 =============================================================

// Create a graph
void unitTestCreateGraph(){
    printf("=====================================\n");
    printf("TEST: Create Graph\n");
    graph_t * testGraph = create_graph();
    printf("numNodes 0 == %d\n", graph_num_nodes(testGraph));
    printf("numEdges 0 == %d\n", graph_num_edges(testGraph));
    free_graph(testGraph);
}

// Create a node
void unitTestCreateNode(){
    printf("=====================================\n");
    printf("TEST: Create Node\n");
    node_t* testNode = create_node(5);
    printf("Data 5 == %d\n",testNode->data);
    free_node(testNode);
}

// Create a neighbor
void unitTestCreateNeighbor(){
    printf("=====================================\n");
    printf("TEST: Create Neighbor\n");
    neighbor_t* testNeighbor = create_neighbor(3);
    printf("Data 3 == %d\n", testNeighbor->data);
    free_neighbor(testNeighbor);
}

// Check if the graph is empty
void unitTestGraphEmpty() {
    printf("=====================================\n");
    printf("TEST: Graph Empty\n");
    graph_t * testGraph = create_graph();
    printf("Graph empty 0 == %d\n", graph_empty(testGraph));
    free_graph(testGraph);
}

// Add the very first node
void unitTestAddFirstNode() {
    printf("=====================================\n");
    printf("TEST: Add the First Node\n");
    graph_t * testGraph = create_graph();
    printf("Graph empty 0 == %d\n", graph_empty(testGraph));
    printf("Adding node 0, success 0 == %d\n", graph_add_node(testGraph,0));
    printf("Graph empty -1 == %d\n", graph_empty(testGraph));
    printf("Head node data 0 == %d\n", testGraph->nodes->data);
    free_graph(testGraph);
}


// Added nodes should be stored in ascending order
// No bad overwrites!
void unitTestAddSeveralNodes() {
    printf("=====================================\n");
    printf("TEST: Add Several Nodes\n");
    graph_t * testGraph = create_graph();
    printf("Adding node 5, success 0 == %d\n", graph_add_node(testGraph,5));
    printf("Adding node 4, success 0 == %d\n", graph_add_node(testGraph,4));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Number of Nodes: 2 == %d\n", testGraph->numNodes);
    printf("Adding node 3, success 0 == %d\n", graph_add_node(testGraph,3));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Adding node 21, success 0 == %d\n", graph_add_node(testGraph,21));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Adding node -5, success 0 == %d\n", graph_add_node(testGraph,-5));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Adding node 13, success 0 == %d\n", graph_add_node(testGraph,13));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Number of Nodes: 6 == %d\n", testGraph->numNodes);
    free_graph(testGraph);
}

// Check if the nodes linked list contains a node with data = given value
void unitTestContainsNode() {
    printf("=====================================\n");
    printf("TEST: Contains Node\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, -3);
    graph_add_node(testGraph, -2);
    graph_add_node(testGraph, -1);
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Contains -3, 0 == %d\n", contains_node(testGraph,-3));
    printf("Contains -2, 0 == %d\n", contains_node(testGraph,-2));
    printf("Contains -1, 0 == %d\n", contains_node(testGraph,-1));
    printf("Contains 0, 0 == %d\n", contains_node(testGraph,0));
    printf("Contains 1, 0 == %d\n", contains_node(testGraph,1));
    printf("Contains 2, 0 == %d\n", contains_node(testGraph,2));
    printf("Contains 3, 0 == %d\n", contains_node(testGraph,3));
    printf("Doesn't contain -4, -1 == %d\n", contains_node(testGraph,-4));
    printf("Doesn't contain 4, -1 == %d\n", contains_node(testGraph,4));
    free_graph(testGraph);
}

// Check that duplicates are prevented
void unitTestNoDuplicates(){
    printf("=====================================\n");
    printf("TEST: Don't Add Duplicate Nodes\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 10);
    graph_add_node(testGraph, 20);
    graph_add_node(testGraph, 30);
    graph_add_node(testGraph, 40);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Attempting to add 10 again, 0 == %d\n", graph_add_node(testGraph, 10));
    printf("Attempting to add 20 again, 0 == %d\n", graph_add_node(testGraph, 20));
    printf("Attempting to add 30 again, 0 == %d\n", graph_add_node(testGraph, 30));
    printf("Attempting to add 40 again, 0 == %d\n", graph_add_node(testGraph, 40));
    printf("Nodes: 10 20 30 40 == ");
    print_node_list(testGraph->nodes);
    printf("Number of Nodes: 4 == %d\n", testGraph->numNodes);
    free_graph(testGraph);
}

// Check that node is removed from 'nodes'
void unitTestRemoveNode() {
    printf("=====================================\n");
    printf("TEST: Remove Node (Basic)\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 6);
    graph_add_node(testGraph, 9);
    graph_add_node(testGraph, 12);
    graph_add_node(testGraph, 15);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Attempting to remove 3, success 0 == %d\n", graph_remove_node(testGraph, 3));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Attempting to remove 15, success 0 == %d\n", graph_remove_node(testGraph, 15));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Attempting to remove 9, success 0 == %d\n", graph_remove_node(testGraph, 9));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Attempting to remove 8, failure -1 == %d\n", graph_remove_node(testGraph, 8));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Attempting to remove 6, success 0 == %d\n", graph_remove_node(testGraph, 6));
    printf("Attempting to remove 12, success 0 == %d\n", graph_remove_node(testGraph, 12));
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Graph is empty, 0 == %d\n", graph_empty(testGraph));
    free_graph(testGraph);
}

// Check that the incoming edges are deleted
void unitTestRemoveNodesIncomingEdges() {
    printf("=====================================\n");
    printf("TEST: Incoming Edges After Node Removal\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,3);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    // Baseline edges
    printf("Neighbors of node 0: 1 3 == ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    // Removed node 3, does the neighbor list reflect that?
    graph_remove_node(testGraph,3);
    printf("Neighbors of node 0: 1  == ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    // Adding another edge
    graph_add_edge(testGraph,0,2);
    printf("Neighbors of node 0: 1 2  == ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    // Remove the head node of the neighbor linked list
    graph_remove_node(testGraph,1);
    printf("Neighbors of node 0: 2  == ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);

    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    free_graph(testGraph);
}

// Add a directed edge
void unitTestAddEdge() {
    printf("=====================================\n");
    printf("TEST: Add Directed Edge\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);

    printf("Adding edge 0 to 1, success 0 == %d\n", graph_add_edge(testGraph,0,1));
    printf("Neighbors of node 0: ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    printf("Neighbors of node 1: ");
    print_neighbor(locate_node(testGraph->nodes,1)->neighbor);

    printf("Adding edge 1 to 3, success 0 == %d\n", graph_add_edge(testGraph,1,3));
    printf("Neighbors of node 1: ");
    print_neighbor(locate_node(testGraph->nodes,1)->neighbor);
    printf("Neighbors of node 3: ");
    print_neighbor(locate_node(testGraph->nodes,3)->neighbor);
    printf("Number of edges 2 == %d\n", graph_num_edges(testGraph));

    free_graph(testGraph);
}

// Check adding duplicate edges is handled properly
void unitTestAddEdgeDuplicate(){
    printf("=====================================\n");
    printf("TEST: Preventing Duplicate Edges\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 4);
    printf("Adding edge 0 to 1, success 0 == %d\n", graph_add_edge(testGraph,0,1));
    printf("Adding edge 0 to 2, success 0 == %d\n", graph_add_edge(testGraph,0,2));
    printf("Adding edge 0 to 3, success 0 == %d\n", graph_add_edge(testGraph,0,3));
    printf("Adding edge 0 to 4, success 0 == %d\n", graph_add_edge(testGraph,0,4));
    printf("Neighbors of node 0: 1 2 3 4 == ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    printf("Number of Edges: 4 == %d\n", testGraph->numEdges);

    printf("Re-adding edge 0 to 1, success 0 == %d\n", graph_add_edge(testGraph,0,1));
    printf("Re-adding edge 0 to 2, success 0 == %d\n", graph_add_edge(testGraph,0,2));
    printf("Re-adding edge 0 to 3, success 0 == %d\n", graph_add_edge(testGraph,0,3));
    printf("Re-adding edge 0 to 4, success 0 == %d\n", graph_add_edge(testGraph,0,4));
    printf("Neighbors of node 0: 1 2 3 4 == ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    printf("Number of Edges: 4 == %d\n", testGraph->numEdges);
    free_graph(testGraph);
}

// Check if a graph contains a given edge
void unitTestContainsEdge() {
    printf("=====================================\n");
    printf("TEST: Contains Directed Edge\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,0,3);
    graph_add_edge(testGraph,1,3);
    printf("Contains edge 0 to 1, true 0 == %d\n",contains_edge(testGraph,0,1));
    printf("Contains edge 0 to 2, true 0 == %d\n",contains_edge(testGraph,0,2));
    printf("Contains edge 0 to 3, true 0 == %d\n",contains_edge(testGraph,0,3));
    printf("Contains edge 1 to 3, true 0 == %d\n",contains_edge(testGraph,1,3));
    printf("Contains edge 0 to 4, false -1 == %d\n",contains_edge(testGraph,0,4));
    printf("Contains edge 2 to 3, false -1 == %d\n",contains_edge(testGraph,2,3));
    printf("Contains edge 3 to 1, false -1 == %d\n",contains_edge(testGraph,3,1));
    free_graph(testGraph);
}

// Remove an edge
void unitTestRemoveEdge() {
    printf("=====================================\n");
    printf("TEST: Remove Directed Edge\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);

    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,0,3);
    graph_add_edge(testGraph,1,3);
    printf("Neighbors of node 0: ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    // Remove head node of neighbor linked list
    printf("Removing edge 0 to 1, success 0 == %d\n", graph_remove_edge(testGraph,0,1));
    printf("Neighbors of node 0: ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    printf("Number of Edges: 3 == %d\n", testGraph->numEdges);
    // Remove tail node of neighbor linked list
    printf("Removing edge 0 to 3, success 0 == %d\n", graph_remove_edge(testGraph,0,3));
    printf("Neighbors of node 0: ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    printf("Number of Edges: 2 == %d\n", testGraph->numEdges);
    // Try bad removes
    printf("Attempting to remove edge 0 to 4, failure -1 == %d\n", graph_remove_edge(testGraph,0,4));
    printf("Attempting to re-remove edge 0 to 3, failure -1 == %d\n", graph_remove_edge(testGraph,0,3));
    printf("Number of Edges: 2 == %d\n", testGraph->numEdges);
    // Empty the list entirely
    printf("Removing edge 0 to 2, success 0 == %d\n", graph_remove_edge(testGraph,0,2));
    printf("Neighbors of node 0: ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    printf("Neighbors of node 1: ");
    print_neighbor(locate_node(testGraph->nodes,1)->neighbor);
    printf("Number of Edges: 1 == %d\n", testGraph->numEdges);

    free_graph(testGraph);
}


// Check if the number of nodes is correct
void unitTestGraphSizeNodes() {
    printf("=====================================\n");
    printf("TEST: Query Number of Nodes\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, -1);
    graph_add_node(testGraph, 6);
    graph_add_node(testGraph, 4);
    graph_add_node(testGraph, 5);
    graph_add_node(testGraph, 20);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Number of Nodes 9 == %d\n",graph_num_nodes(testGraph));
    graph_remove_node(testGraph,0);
    graph_remove_node(testGraph,-1);
    graph_remove_node(testGraph,20);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Number of Nodes 6 == %d\n",graph_num_nodes(testGraph));
    graph_remove_node(testGraph,0);
    graph_remove_node(testGraph,0);
    graph_remove_node(testGraph,0);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Number of Nodes 6 == %d\n",graph_num_nodes(testGraph));
    graph_remove_node(testGraph,1);
    graph_remove_node(testGraph,2);
    graph_remove_node(testGraph,3);
    graph_remove_node(testGraph,4);
    graph_remove_node(testGraph,5);
    graph_remove_node(testGraph,6);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("Number of Nodes 0 == %d\n",graph_num_nodes(testGraph));
    free_graph(testGraph);
}

// Check if the number of edges is correct
void unitTestGraphSizeEdges() {
    printf("=====================================\n");
    printf("TEST: Query Number of Edges\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,1,0);
    graph_add_edge(testGraph,1,2);
    printf("Number of edges 4 == %d\n", graph_num_edges(testGraph));
    graph_remove_edge(testGraph,0,1);
    graph_remove_edge(testGraph,0,2);
    graph_remove_edge(testGraph,1,0);
    printf("Number of edges 1 == %d\n", graph_num_edges(testGraph));
    graph_remove_edge(testGraph,1,2);
    graph_remove_edge(testGraph,1,2);
    graph_remove_edge(testGraph,1,2);
    graph_remove_edge(testGraph,1,2);
    graph_remove_edge(testGraph,1,2);
    graph_remove_edge(testGraph,1,2);
    printf("Number of edges 0 == %d\n", graph_num_edges(testGraph));

    free_graph(testGraph);
}

// Check the number of neighbors for a particular node
void unitTestNumNeighbors() {
    printf("=====================================\n");
    printf("TEST: Query Number of Neighbors a Node Has\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    printf("Node 0 has num neighbors 0 == %d\n", numNeighbors(testGraph,0));
    printf("Node 1 has num neighbors 0 == %d\n", numNeighbors(testGraph,1));
    printf("Node 2 has num neighbors 0 == %d\n", numNeighbors(testGraph,2));
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,1);
    printf("Node 0 has num neighbors 1 == %d\n", numNeighbors(testGraph,0));
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 4);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,0,3);
    graph_add_edge(testGraph,0,4);
    printf("Node 0 has num neighbors 4 == %d\n", numNeighbors(testGraph,0));
    printf("Node 3 has num neighbors 0 == %d\n", numNeighbors(testGraph,3));
    printf("Node 4 has num neighbors 0 == %d\n", numNeighbors(testGraph,4));
    free_graph(testGraph);
}

// Check the array generated by getNeighbors
void unitTestGetNeighborArray(){
    printf("=====================================\n");
    printf("TEST: Get Array of Neighbors\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 4);
    graph_add_node(testGraph, 5);
    graph_add_node(testGraph, 6);
    graph_add_node(testGraph, 7);
    graph_add_node(testGraph, 8);
    graph_add_node(testGraph, 9);
    printf("---------------\n");
    printf("Nodes: ");
    print_node_list(testGraph->nodes);
    printf("---------------\n");

    // Size is 0
    printf("Expect: ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    int* array = getNeighbors(testGraph,0);
    print_neighbor_array(array,0);
    free(array);

    // Size is 1
    graph_add_edge(testGraph,0,1);
    printf("Expect ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    array = getNeighbors(testGraph,0);
    print_neighbor_array(array,1);
    free(array);

    // Size is 2
    graph_add_edge(testGraph,0,2);
    printf("Expect ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    array = getNeighbors(testGraph,0);
    print_neighbor_array(array,2);
    free(array);

    // Size is 3
    graph_add_edge(testGraph,0,3);
    printf("Expect ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    array = getNeighbors(testGraph,0);
    print_neighbor_array(array,3);
    free(array);

    // Size is 4
    graph_add_edge(testGraph,0,4);
    printf("Expect ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    array = getNeighbors(testGraph,0);
    print_neighbor_array(array,4);
    free(array);

    // Size is 5
    graph_add_edge(testGraph,0,5);
    printf("Expect ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    array = getNeighbors(testGraph,0);
    print_neighbor_array(array,5);
    free(array);

    // Size is 6
    graph_add_edge(testGraph,0,6);
    printf("Expect ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    array = getNeighbors(testGraph,0);
    print_neighbor_array(array,6);
    free(array);

    // Size is 5
    graph_remove_edge(testGraph,0,6);
    printf("Expect ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);
    array = getNeighbors(testGraph,0);
    print_neighbor_array(array,numNeighbors(testGraph,0));
    free(array);

    free_graph(testGraph);
}

// Resolve issues encountered when removing a node
// that corresponded to the head neighbor in another
// node's neighbor linked list
void unitTestRemoveHeadNeighbor() {
    printf("=====================================\n");
    printf("TEST: Remove Node, Neighbor Head Bug\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph, 0);
    graph_add_node(testGraph, 1);
    graph_add_node(testGraph, 2);
    graph_add_node(testGraph, 3);
    printf("Nodes: ");
    print_node_list(testGraph->nodes);

    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,0,3);
    printf("Neighbors: 1 2 3 == ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);

    graph_remove_node(testGraph,1);
    printf("Neighbors: 2 3 == ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);

    graph_remove_node(testGraph,2);
    printf("Neighbors: 3 == ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);

    graph_remove_node(testGraph,3);
    printf("Neighbors: (none) ==  ");
    print_neighbor(locate_node(testGraph->nodes,0)->neighbor);

    free_graph(testGraph);
}

// ================= Tests for Part 2 =============================================================

// Create and free a queue
void unitTestCreateQueue() {
    printf("=====================================\n");
    printf("TEST: Create Queue\n");
    queue_t* testQ = create_queue();
    free_queue(testQ);
}

// Create and free a queue node
void unitTestCreateQueueNodes() {
    printf("=====================================\n");
    printf("TEST: Create Queue Node\n");
    q_node_t* qNode = create_Q_node(5);
    printf("Value 5 == %d\n", qNode->data);
    free_Q_node(qNode);
}

// Check empty function
void unitTestQueueEmpty() {
    printf("=====================================\n");
    printf("TEST: Queue Empty\n");
    queue_t* testQ = create_queue();
    printf("Queue is empty 0 == %d\n",queue_empty(testQ));
    queue_append(testQ,3);
    printf("Queue is not empty -1 == %d\n",queue_empty(testQ));
    free_queue(testQ);
}

// Peek front element
void unitTestQueuePeek() {
    printf("=====================================\n");
    printf("TEST: Queue Peek\n");
    queue_t* testQ = create_queue();
    queue_append(testQ,3);
    printf("First element is 3 == %d\n", queue_peek(testQ));
    queue_append(testQ,6);
    printf("First element is still 3 == %d\n", queue_peek(testQ));
    free_queue(testQ);
}

// Ability to pop the first element
void unitTestPopHead() {
    printf("=====================================\n");
    printf("TEST: Queue Pop Head\n");
    queue_t* testQ = create_queue();
    queue_append(testQ,3);
    printf("Size 1 == %d\n", testQ->size);
    printf("First element is 3 == %d\n", queue_peek(testQ));
    queue_append(testQ,6);
    printf("Size 2 == %d\n", testQ->size);
    queue_pop_head(testQ);
    printf("Pop head\n");
    printf("First element is now 6 == %d\n", queue_peek(testQ));
    printf("Size 1 == %d\n", testQ->size);
    queue_pop_head(testQ);
    printf("Pop head\n");
    printf("Size 0 == %d\n", testQ->size);
    free_queue(testQ);
}

// Add to the queue, always appends to last position
void unitTestQueueAppend() {
    printf("=====================================\n");
    printf("TEST: Queue Append\n");
    queue_t* testQ = create_queue();
    queue_append(testQ,3);
    queue_print(testQ);
    queue_append(testQ,15);
    queue_print(testQ);
    queue_append(testQ,7);
    queue_print(testQ);
    queue_append(testQ,0);
    queue_print(testQ);
    queue_append(testQ,8);
    queue_print(testQ);
    free_queue(testQ);
}

// Queue must be able to empty completely
void unitTestQueueWipe() {
    printf("=====================================\n");
    printf("TEST: Queue Wipe\n");
    queue_t* testQ = create_queue();
    queue_append(testQ,3);
    queue_append(testQ,15);
    queue_append(testQ,7);
    queue_append(testQ,0);
    queue_append(testQ,8);
    queue_print(testQ);
    queue_pop_head(testQ);
    queue_pop_head(testQ);
    queue_pop_head(testQ);
    queue_pop_head(testQ);
    queue_pop_head(testQ);
    queue_print(testQ);
    printf("Queue is empty 0 == %d\n", queue_empty(testQ));
    free_queue(testQ);
}

void unitTestGraphPrint() {
    printf("=====================================\n");
    printf("TEST: Graph Print\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph,0);
    graph_add_node(testGraph,1);
    graph_add_node(testGraph,2);
    graph_add_node(testGraph,3);
    graph_add_node(testGraph,4);
    graph_add_node(testGraph,5);
    graph_add_node(testGraph,6);
    graph_add_node(testGraph,7);
    graph_add_node(testGraph,8);
    graph_add_node(testGraph,9);
    graph_add_node(testGraph,10);
    graph_add_node(testGraph,11);
    graph_add_node(testGraph,12);
    graph_add_node(testGraph,13);
    graph_add_node(testGraph,14);

    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,1,3);
    graph_add_edge(testGraph,3,4);
    graph_add_edge(testGraph,4,5);
    graph_add_edge(testGraph,2,6);
    graph_add_edge(testGraph,2,7);
    graph_add_edge(testGraph,7,8);
    graph_add_edge(testGraph,7,9);
    graph_add_edge(testGraph,9,10);
    graph_add_edge(testGraph,9,11);
    graph_add_edge(testGraph,10,12);
    graph_add_edge(testGraph,10,13);
    graph_add_edge(testGraph,13,14);

    printf("Expect Out : 0 1 2 3 6 7 4 8 9 5 10 11 12 13 14\n");
    graph_print(testGraph);
    free_graph(testGraph);
}

// Verify this sets all nodes to unvisited status
void unitTestUnvisitAll() {
    printf("=====================================\n");
    printf("TEST: Unvisit All\n");
    graph_t * testGraph = create_graph();
    graph_add_node(testGraph,0);
    graph_add_node(testGraph,1);
    graph_add_node(testGraph,2);
    graph_add_node(testGraph,3);
    graph_add_node(testGraph,4);
    graph_add_node(testGraph,5);
    graph_add_node(testGraph,6);
    graph_add_node(testGraph,7);

    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,1,4);
    graph_add_edge(testGraph,1,5);
    graph_add_edge(testGraph,4,7);
    graph_add_edge(testGraph,5,6);
    graph_add_edge(testGraph,2,3);
    // Print twice to see if the nodes were reset!

    printf("Expect Out : 0 1 2 4 5 3 7 6\n");
    graph_print(testGraph);
    graph_print(testGraph);
    free_graph(testGraph);
}

void unitTestIsReachable() {
    printf("=====================================\n");
    printf("TEST: Graph Print\n");
    // Reusing the graph I set up earlier.
    graph_t * testGraph = create_graph();
    printf("Graph empty 0 == %d\n", graph_empty(testGraph));
    graph_add_node(testGraph,0);
    graph_add_node(testGraph,1);
    graph_add_node(testGraph,2);
    graph_add_node(testGraph,3);
    graph_add_node(testGraph,4);
    graph_add_node(testGraph,5);
    graph_add_node(testGraph,6);
    graph_add_node(testGraph,7);
    graph_add_node(testGraph,8);
    graph_add_node(testGraph,9);
    graph_add_node(testGraph,10);
    graph_add_node(testGraph,11);
    graph_add_node(testGraph,12);
    graph_add_node(testGraph,13);
    graph_add_node(testGraph,14);

    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,1,3);
    graph_add_edge(testGraph,3,4);
    graph_add_edge(testGraph,4,5);
    graph_add_edge(testGraph,2,6);
    graph_add_edge(testGraph,2,7);
    graph_add_edge(testGraph,7,8);
    graph_add_edge(testGraph,7,9);
    graph_add_edge(testGraph,9,10);
    graph_add_edge(testGraph,9,11);
    graph_add_edge(testGraph,10,12);
    graph_add_edge(testGraph,10,13);
    graph_add_edge(testGraph,13,14);

    printf("Graph empty -1 == %d\n", graph_empty(testGraph));
    printf("numNodes 15 == %d\n", testGraph->numNodes);
    printf("numEdges 14 == %d\n", testGraph->numEdges);

    int i;
    for (i = 1; i < 15; i++) {
        printf("Node %d is reachable from root, 0 == %d\n",i,is_reachable(testGraph,0,i));
    }

    printf("Node 5 is reachable from 1, 0 == %d\n",is_reachable(testGraph,1,5));
    printf("Node 0 is not reachable from 0, -1 == %d\n",is_reachable(testGraph,0,0));
    printf("Node 1 is not reachable from 5, -1 == %d\n",is_reachable(testGraph,5,1));
    printf("Node 5 is not reachable from 2, -1 == %d\n",is_reachable(testGraph,2,5));
    printf("Node 2 is not reachable from 5, -1 == %d\n",is_reachable(testGraph,2,5));
    printf("Node 12 is reachable from 9, 0 == %d\n",is_reachable(testGraph,9,12));
    printf("Node 12 is not reachable from 11, -1 == %d\n",is_reachable(testGraph,11,12));
    free_graph(testGraph);
}

void unitTestCreateStack() {
    printf("=====================================\n");
    printf("TEST: Create Stack\n");
    stack_t* testStack = create_stack();
    free_stack(testStack);
}

void unitTestStackEmpty(){
    printf("=====================================\n");
    printf("TEST: Stack Empty\n");
    stack_t* testStack = create_stack();
    printf("Stack is empty, 0 == %d\n", stack_empty(testStack));
    free_stack(testStack);
}

void unitTestStackPush() {
    printf("=====================================\n");
    printf("TEST: Stack Empty\n");
    stack_t* testStack = create_stack();
    printf("Stack is empty, 0 == %d\n", stack_empty(testStack));
    printf("Pushing 5, success 0 == %d\n", stack_push(testStack,5));
    printf("Stack is not empty, -1 == %d\n", stack_empty(testStack));
    printf("Pushing 5, success 0 == %d\n", stack_push(testStack,5));
    printf("Pushing 5, success 0 == %d\n", stack_push(testStack,5));
    printf("Pushing 5, success 0 == %d\n", stack_push(testStack,5));
    printf("Stack size 4 == %d\n", testStack->size);
    free_stack(testStack);
}

void unitTestStackPeek() {
    printf("=====================================\n");
    printf("TEST: Stack Peek\n");
    stack_t* testStack = create_stack();
    stack_push(testStack,5);
    printf("Top 5 == %d\n", stack_peek(testStack));
    stack_push(testStack,10);
    printf("Top 10 == %d\n", stack_peek(testStack));
    stack_push(testStack,7);
    printf("Top 7 == %d\n", stack_peek(testStack));
    free_stack(testStack);
}

void unitTestStackPop() {
    printf("=====================================\n");
    printf("TEST: Stack Pop\n");
    stack_t* testStack = create_stack();
    stack_push(testStack,5);
    stack_push(testStack,10);
    stack_push(testStack,7);
    printf("Top 7 == %d\n", stack_peek(testStack));
    stack_pop(testStack);
    printf("Top 10 == %d\n", stack_peek(testStack));
    stack_pop(testStack);
    printf("Top 5 == %d\n", stack_peek(testStack));
    stack_pop(testStack);
    printf("Stack is empty, 0 == %d\n", stack_empty(testStack));
    free_stack(testStack);
}

void unitTestHasCycleFalse() {
    printf("=====================================\n");
    printf("TEST: Has Cycle False\n");
    graph_t* testGraph = create_graph();
    graph_add_node(testGraph,0);
    graph_add_node(testGraph,1);
    graph_add_node(testGraph,2);
    graph_add_node(testGraph,3);
    graph_add_node(testGraph,4);
    graph_add_node(testGraph,5);
    graph_add_node(testGraph,6);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,1,5);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,2,4);
    graph_add_edge(testGraph,2,3);
    graph_add_edge(testGraph,3,6);
    printf("Graph has no cycle, -1 == %d\n", has_cycle(testGraph));
    free_graph(testGraph);
}

void unitTestHasCycleTrue() {
    printf("=====================================\n");
    printf("TEST: Has Cycle True\n");
    graph_t* testGraph = create_graph();
    graph_add_node(testGraph,0);
    graph_add_node(testGraph,1);
    graph_add_node(testGraph,2);
    graph_add_node(testGraph,3);
    graph_add_node(testGraph,4);
    graph_add_node(testGraph,5);
    graph_add_node(testGraph,6);
    graph_add_edge(testGraph,0,1);
    graph_add_edge(testGraph,1,5);
    graph_add_edge(testGraph,0,2);
    graph_add_edge(testGraph,2,4);
    graph_add_edge(testGraph,2,3);
    graph_add_edge(testGraph,3,6);
    // Used same graph, but added edge from 6 back to 0!
    graph_add_edge(testGraph,6,0);
    printf("Graph has a cycle, 0 == %d\n", has_cycle(testGraph));
    free_graph(testGraph);
}

void unitTestPrintPathBasic() {
    printf("=====================================\n");
    printf("TEST: Print Path Basic\n");
    graph_t* testGraph = create_graph();
    graph_add_node(testGraph,0);
    graph_add_node(testGraph,1);
    graph_add_node(testGraph,2);
    graph_add_node(testGraph,3);
    graph_add_node(testGraph,4);
    graph_add_node(testGraph,5);
    graph_add_node(testGraph,6);
    graph_add_node(testGraph,7);
    graph_add_node(testGraph,8);
    graph_add_node(testGraph,9);
    graph_add_node(testGraph,10);
    graph_add_node(testGraph,11);

    graph_add_edge(testGraph,0,1);
    printf("Expected Output : 0 1\n");
    print_path(testGraph,0,1);

    graph_add_edge(testGraph,1,2);
    printf("Expected Output : 0 1 2\n");
    print_path(testGraph,0,2);

    graph_add_edge(testGraph,1,3);
    printf("Expected Output : 0 1 3\n");
    print_path(testGraph,0,3);

    graph_add_edge(testGraph,0,4);
    printf("Expected Output : 0 4\n");
    print_path(testGraph,0,4);

    graph_add_edge(testGraph,4,5);
    printf("Expected Output : 0 4 5\n");
    print_path(testGraph,0,5);

    graph_add_edge(testGraph,4,6);
    printf("Expected Output : 0 4 6\n");
    print_path(testGraph,0,6);

    graph_add_edge(testGraph,4,7);
    printf("Expected Output : 0 4 7\n");
    print_path(testGraph,0,7);

    graph_add_edge(testGraph,5,10);
    printf("Expected Output : 0 4 5 10\n");
    print_path(testGraph,0,10);

    graph_add_edge(testGraph,2,9);
    printf("Expected Output : 0 1 2 9\n");
    print_path(testGraph,0,9);

    graph_add_edge(testGraph,2,8);
    printf("Expected Output : 0 1 2 8\n");
    print_path(testGraph,0,8);

    // Now there are two routes to get here, errors?
    // Probably takes 0 1 2 8 10 because DFS starts with the earliest edges from 0
    // and the first edge was 0 to 1
    graph_add_edge(testGraph,8,10);
    printf("Expected Output : 0 4 5 10 (OR) 0 1 2 8 10\n");
    print_path(testGraph,0,10);

    graph_add_edge(testGraph,10,11);
    printf("Expected Output : 0 4 5 10 11 (OR) 0 1 2 8 10 11\n");
    print_path(testGraph,0,11);

    // No such path
    printf("Expected Output : (none)\n");
    print_path(testGraph,2,7);

    // NULL
    graph_t* g = NULL;
    printf("Expected Output : (none)\n");
    print_path(g,0,1);
    free(g);

    free_graph(testGraph);
}

void unitTestFreeQueue() {
    printf("=====================================\n");
    printf("TEST: Double check free on queue\n");
    // Empty
    queue_t* testQ1 = create_queue();
    free_queue(testQ1);

    // One element
    queue_t* testQ2 = create_queue();
    queue_append(testQ2,5);
    free_queue(testQ2);

    // Two elements
    queue_t* testQ3 = create_queue();
    queue_append(testQ3,5);
    queue_append(testQ3,10);
    free_queue(testQ3);

    // Three elements
    queue_t* testQ4 = create_queue();
    queue_append(testQ4,5);
    queue_append(testQ4,10);
    queue_append(testQ4,11);
    free_queue(testQ4);

    // Queue that became empty
    queue_t* testQ5 = create_queue();
    queue_append(testQ5,5);
    queue_append(testQ5,10);
    queue_append(testQ5,11);
    queue_pop_head(testQ5);
    queue_pop_head(testQ5);
    queue_pop_head(testQ5);
    free_queue(testQ5);
}

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
    printf("BEGINNING UNIT TESTS...\n");

    // ========================================================================
    // Each unit test has one specific objective.
    // Previously passed tests are commented out to make the results readable.
    // Unit test functions are split into two sections above:
    //     "Tests for Part 1"
    //     "Tests for Part 2"
    // ========================================================================

    // === Passed Part 1 Tests ===
    unitTestCreateGraph();
    unitTestCreateNode();
    unitTestCreateNeighbor();
    unitTestGraphEmpty();
    unitTestAddFirstNode();
    unitTestAddSeveralNodes();
    unitTestContainsNode();
    unitTestNoDuplicates();
    unitTestContainsEdge();
    unitTestGraphSizeNodes();
    unitTestGraphSizeEdges();
    unitTestNumNeighbors();
    unitTestGetNeighborArray();
    unitTestAddEdge();
    unitTestAddEdgeDuplicate();
    unitTestRemoveEdge();
    unitTestRemoveNode();
    unitTestRemoveHeadNeighbor();
    unitTestRemoveNodesIncomingEdges();

    // === Passed Part 2 Tests ===
    unitTestCreateQueue();
    unitTestCreateQueueNodes();
    unitTestQueueEmpty();
    unitTestQueuePeek();
    unitTestPopHead();
    unitTestQueueAppend();
    unitTestQueueWipe();
    unitTestGraphPrint();
    unitTestUnvisitAll();
    unitTestCreateStack();
    unitTestStackEmpty();
    unitTestStackPush();
    unitTestStackPeek();
    unitTestStackPop();
    unitTestFreeQueue();
    unitTestHasCycleFalse();
    unitTestHasCycleTrue();
    unitTestIsReachable();
    unitTestPrintPathBasic();

    printf("=====================================\n");
    printf("END OF UNIT TESTING.\n");

    return 0;
}
