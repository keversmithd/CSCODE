#include "DGraph.hpp"

DGraph::DGraph() : NumberOfNodes(0), adjacencyMatrix{0}
{
    //Constructs with number of nodes set ot 0 and adjacencyMatrix set to 0.
}
void DGraph::addNode(const char node)
{
    if(NumberOfNodes >= SIZE)
    {
        throw std::range_error("Full Size"); //If exceed size then throw range error.
    }
    DNode InsertionNode; //Create node structures.
    InsertionNode.value = node;
    InsertionNode.visited = false;
    InsertionNode.adjacent = nullptr; //populate the adjacent to nullptr and visited to false, set value to added value.
    nodeList[NumberOfNodes++] = InsertionNode; //Insert the node memory into the array.
    
}
bool DGraph::addEdge(const char a, const char b)
{
    if(a == b) return false; //If a and b values are the same  return false.

    int startIndex = findNode(a); //finds node of first index.
    int endIndex = findNode(b); //finds node of second index.

    if(startIndex == -1 || endIndex == -1) return false; //if either do not exist in the graph, then return false.

    //adjacencyMatrix[startIndex][endIndex] = true;
    adjacencyMatrix[endIndex][startIndex] = true; //sets the adjacency matrix of the direction to true.

    DEdge* startToEnd = new DEdge(); //creats new edge.
    startToEnd->endIndex = endIndex; //sets end ot end.
    startToEnd->next = nodeList[startIndex].adjacent; //then sets starts next o this edge.
    nodeList[startIndex].adjacent = startToEnd; //and its adjacency to this

    // DEdge* endToStart = new DEdge();
    // endToStart->endIndex = startIndex;
    // endToStart->next = nodeList[endIndex].adjacent;
    // nodeList[endIndex].adjacent = endToStart;

    return true; //return true.
    
}
int DGraph::findNode(const char name) //Finds node iteratively throughout entire list of nodes.
{
    for(int index = 0; index <= NumberOfNodes; index++) //Search through entire list of nodes.
    {
        if(nodeList[index].value == name) //If found then return the index.
        {
            return index;
        }
    }

    return -1;
}
std::string DGraph::listNodes() //This lists all nodes inside of the nodes.
{
    std::string theList = ""; //Creates a string.
    for(int i = 0; i < NumberOfNodes; i++) //Fills the string with the value of the value of the node and then a solid space.
    {
        theList += nodeList[i].value;
        theList += " ";
    }
    return theList;
}
std::string DGraph::displayAdjacency()
{
    std::string buffer = ""; //Creates a string.

    for(int index = 0; index < NumberOfNodes; index++) //For each node.
    {
        buffer += nodeList[index].value; //Place indicator which letter it is.
        buffer += ": ";
        DEdge* ptr = nodeList[index].adjacent;

        while(ptr != nullptr) //Iterate through adjacency list and append all the adjacent nodes to the string.
        {
            buffer += nodeList[ptr->endIndex].value;
            buffer += " ";
            ptr = ptr->next;
        }

        buffer += '\n'; //Add new line.
    }
    return buffer;
}
std::string DGraph::displayMatrix()
{
    

    std::string buffer = "    "; //Creates a spaced buffer.
    for(int i = 0; i <= NumberOfNodes; i++) //Draw the horizonal axis of the node names.
    {
        buffer += " ";
        buffer += nodeList[i].value;
        buffer += "  ";
    }
    buffer += "\n";
    
    for(int i = 0; i < NumberOfNodes; i++) //Downpass through column space of matrix.
    {
        buffer += nodeList[i].value; //Append nodal indicator.
        buffer += "   ";
        for(int j = 0; j < NumberOfNodes; j++) //Drag across row and place . for 0 and 1 for 1.
        {
            bool value = adjacencyMatrix[j][i];
            if(value == false)
            { 
                buffer += " .  ";
            }
            else
            {
                buffer += " 1  ";
            }
        }

        buffer += '\n';
    }
    return buffer;
}
std::string DGraph::breadthFirst(const char value)
{
    // Resetting the visited flag for all nodes
    for (int i = 0; i < NumberOfNodes; i++)
    {
        nodeList[i].visited = false;
    }

    std::string buffer = "";
    buffer += value;
    buffer += ": ";
    int cindex = findNode(value); // Find the index of the starting node in the nodeList
    if (cindex == -1) return buffer; // If the starting node is not found, return the buffer as is
    DNode* pointer = &nodeList[cindex];
    pointer->visited = true;

    std::deque<DNode*> Q; // Create a deque to store nodes for breadth-first traversal
    Q.push_back(pointer);

    while (!Q.empty())
    {
        pointer = Q.front(); // Get the front node from the deque
        Q.pop_front();

        DEdge* edgePointer = pointer->adjacent; // Get the pointer to the adjacent edges of the current node

        while (edgePointer != nullptr)
        {
            DNode* adjacentNode = &nodeList[edgePointer->endIndex]; // Get the adjacent node from the edge
            if (adjacentNode->visited == false) // If the adjacent node is not visited
            {
                Q.push_back(adjacentNode); // Add it to the deque for further traversal
                buffer += adjacentNode->value; // Append the value of the adjacent node to the buffer
                buffer += " ";
                adjacentNode->visited = true; // Mark the adjacent node as visited
            }
            edgePointer = edgePointer->next; // Move to the next adjacent edge
        }
    }

    return buffer; // Return the buffer containing the breadth-first traversal result

}

std::string DGraph::depthFirst(const char value)
{
    // Resetting the visited flag for all nodes
    for (int i = 0; i < NumberOfNodes; i++)
    {
        nodeList[i].visited = false;
    }

    std::string buffer = "";
    buffer += value;
    buffer += ": ";
    int cindex = findNode(value); // Find the index of the starting node in the nodeList
    if (cindex == -1) return buffer; // If the starting node is not found, return the buffer as is
    DNode* pointer = &nodeList[cindex];
    pointer->visited = true;

    std::stack<DNode*> S; // Create a stack to store nodes for depth-first traversal
    S.push(pointer);

    while (!S.empty())
    {
        pointer = S.top(); // Get the top node from the stack
        //S.pop();

        DEdge* edgePointer = pointer->adjacent; // Get the pointer to the adjacent edges of the current node
        bool FirstNodeNonVisited = false;

        while (FirstNodeNonVisited == false && edgePointer != nullptr)
        {
            DNode* adjacentNode = &nodeList[edgePointer->endIndex]; // Get the adjacent node from the edge

            if (adjacentNode->visited == false) // If the adjacent node is not visited
            {
                adjacentNode->visited = true; // Mark the adjacent node as visited
                S.push(adjacentNode); // Add it to the stack for further traversal
                FirstNodeNonVisited = true;
                buffer += adjacentNode->value; // Append the value of the adjacent node to the buffer
                buffer += " ";
            }
            else
            {
                edgePointer = edgePointer->next; // Move to the next adjacent edge
            }
        }

        if (edgePointer == nullptr)
        {
            S.pop(); // If all adjacent nodes are visited, remove the current node from the stack
        }
    }

    return buffer; // Return the buffer containing the depth-first traversal result
}

std::string DGraph::minTree(const char value)
{
    // Resetting the visited flag for all nodes
    for (int i = 0; i < NumberOfNodes; i++)
    {
        nodeList[i].visited = false;
    }

    std::string buffer = "";
    buffer += value;
    buffer += ": ";

    int cindex = findNode(value); // Find the index of the starting node in the nodeList
    if (cindex == -1) return buffer; // If the starting node is not found, return the buffer as is
    DNode* pointer = &nodeList[cindex];
    pointer->visited = true;
    std::string parentNode(1, pointer->value); // Initialize the parent node with the value of the starting node

    std::deque<DNode*> Q; // Create a deque to store nodes for breadth-first traversal
    bool visitedany = false;

    Q.push_back(pointer);

    DNode* adjacentNode;
    while (!Q.empty())
    {
        pointer = Q.front(); // Get the front node from the deque
        parentNode = pointer->value; // Update the parent node to the current node's value
        Q.pop_front();

        DEdge* edgePointer = pointer->adjacent; // Get the pointer to the adjacent edges of the current node
        visitedany = false;

        while (edgePointer != nullptr)
        {
            adjacentNode = &nodeList[edgePointer->endIndex]; // Get the adjacent node from the edge

            if (adjacentNode->visited == false) // If the adjacent node is not visited
            {
                Q.push_back(adjacentNode); // Add it to the deque for further traversal
                buffer += parentNode;
                buffer += "-";
                buffer += adjacentNode->value; // Append the parent node and adjacent node values to the buffer
                buffer += " ";
                adjacentNode->visited = true; // Mark the adjacent node as visited
                visitedany = true;
            }

            edgePointer = edgePointer->next; // Move to the next adjacent edge

            if (visitedany)
            {
                parentNode = adjacentNode->value; // Update the parent node to the current adjacent node's value
            }
        }
    }

    return buffer; // Return the buffer containing the minimum spanning tree result

}

std::string DGraph::connectTable()
{   
    std::string connectivityTable = ""; //Casts breadth first search on each node and appending its connections to its list.
    for(int i = 0; i < NumberOfNodes; i++)
    {
        connectivityTable += breadthFirst(nodeList[i].value);
        connectivityTable += "\n";
    }

    return connectivityTable;

    

}