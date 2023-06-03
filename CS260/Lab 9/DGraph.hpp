#ifndef DGRAPH_H
#define DGRAPH_H
#include <stdexcept>
#include <string>
#include <deque>
#include <stack>
#include <vector>
struct DEdge //Edge with index to node.
{
    int endIndex;
    DEdge* next; //Pointer to the next edge
};

struct DNode //Node in the graph
{
    char value; //houses value
    bool visited; //houses visited status
    DEdge* adjacent; //houses adjacency list.
};

struct DGraph //A graph which has an array of nodes, and a bool matrix which is the adjacency matrix.
{
private:
    static const int SIZE = 20; //Fixed size of this matrix.
    DNode nodeList[SIZE]; //Array of nodes.
    bool adjacencyMatrix[SIZE][SIZE]; //Adjacency matrix.
    int NumberOfNodes; //Number of added nodes.
public:
    DGraph(); //Constructs and sets up graph.
    void addNode(const char node); //Adds a node to the graph
    bool addEdge(const char starts, const char ends); //Connects the nodes with an edge.
    int findNode(const char name); //Finds the index of the node and returns -1 if not found.
    std::string listNodes(); //Lists an array of nodes.
    std::string displayAdjacency(); //Displaces the adjacency lists of all of the nodes.
    std::string displayMatrix(); //Displays the state of the adjacency matrix.
    std::string breadthFirst(const char value); //Uses que to search the graph
    std::string depthFirst(const char value); //Uses stack to search the graph.
    std::string minTree(const char value); //Constructs minimum path using the breadth first search.
    std::string connectTable(); //Displacys connectivity table of the graph.
};

#endif