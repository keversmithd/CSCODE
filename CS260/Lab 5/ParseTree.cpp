#include "ParseTree.hpp"

// Constructor that takes an expression string and initializes the parse tree
ParseTree::ParseTree(std::string expression) : think(false)
{
    // Call doParse to create the parse tree
    if(expression != "")
        doParse(expression);
}
// Method that takes an expression string and returns the root of the parse tree
ParseNode* ParseTree::doParse(std::string expression) 
{
    // Loop through each character in the expression string
    for(int i = 0; i < expression.size(); i++)
    {
        // Get the current character
        char letter = expression[i];


        // Ignore spaces
        if(letter != ' ')
        {
            // If the current character is an operand (i.e. a letter or digit)
            if(isOperand(letter))
            {
                // Create a new parse node for the operand and push it onto the parse stack
                ParseNode* n = new ParseNode;
                n->value = letter;
   
                ParseStack.addTail(n);
            }
            // If the current character is an operator (i.e. anything that is not an operand)
            else
            {
                // Create a new parse node for the operator
                ParseNode* temp = new ParseNode();

                 // Set the operator value for the temporary node
                temp->value = letter;

                // Pop the top two nodes from the parse stack and set them as the left and right children of the temporary node
                if(!ParseStack.isEmpty())
                {
                    temp->right = ParseStack.removeTail();
                }
                if(!ParseStack.isEmpty())
                {
                    temp->left = ParseStack.removeTail();
                }
                    
                // Push the temporary node onto the parse stack followed by the closing parenthesis node
                ParseStack.addTail(temp);
            }
        }
    }

    // Return the head of the parse stack, which should be the root of the parse tree
    return ParseStack.getHead();
}
//Checks whether the char is any of the specific operator chars.
bool ParseTree::isOperand(const char letter)
{
    return (letter != '+' && letter != '-' && letter != '/' && letter != '*' && letter != '(' && letter != ')');
}
//Iterative pre order
std::string ParseTree::preOrder()
{
    std::string treeDisplay = "";
    Deque<ParseNode*> q;
   
    q.addTail(ParseStack.getHead()); //Add root to head of stack
    ParseNode* root = nullptr; //Makes nullptr root for iterative uses.
    while(!q.isEmpty()) //Continues until the stack is empty.
    {
        root = q.removeTail(); //Gathers the char of the top of the stack and appends it to the string.
        treeDisplay += root->value;

        if(root->right) //If there is a right add it to top of the stack
            q.addTail(root->right);
        if(root->left)
            q.addTail(root->left); //Then add this to the start of the stack

        //This will always visit all way down the left of the tree, and then climb up and to the right of all the previous right nodes up to the top, and then down the left side of the right subtree.
    }

    return treeDisplay;
}
std::string ParseTree::inOrder()
{
    std::string ino = ""; //Return string with information about the traversal.
    ParseNode* root = ParseStack.getHead(); //Gather root of tree.
    Deque<ParseNode*> s; //Stack
    Deque<char> b; //Parenthesis stack
    int i = 0;
    if(think == false){ //For the non thinking problem
    while(root != nullptr || !s.isEmpty())
    {
        while(root != nullptr) //goes down all the way left to last left leaf node, and adds open parenthesis to the stack.
        {
            ParseNode* temp = root;
            s.addTail(root);
            if(!isOperand(root->value))
            {
                b.addTail('(');
            }
            root = root->left;
        }

        root = s.removeTail(); //Gets the top of the node stack.
        //if next is operator
        if(!isOperand(root->value)){ //If it is an operator and it meets conditions of the string then add parenthesis.
            
            if(i > 1)
            {
                
                if(!b.isEmpty())
                {
                    if(!isOperand(ino[i-2]) && ino[i-2] != '(')
                    {
                        ino += ')';
                        i++;
                        b.removeTail();
                    }
                   
                }
            }
            b.addTail(')');
            
        }else //If it is an operand then unload all of the open parenthesis into the string.
        {
            bool done = false;
            while(!b.isEmpty() && done == false)
            {
                char letter = b.getTail();
                if(letter == '(')
                {
                    b.removeTail();
                    ino += letter;
                    i++;
                }else
                {
                    done = true;
                }
            }

        }

        ino += root->value;
        i++;

        root = root->right;
    }
    while(!b.isEmpty()) //Puts the rest of the closed parenthesis into the string.
    {
        ino += b.removeTail();
    }
    }else
    {
        while(root != nullptr || !s.isEmpty())
        {
            while(root != nullptr) //goes down
            {
                s.addTail(root);
                root = root->left;
            }

            root = s.removeTail();
            ino += root->value;
            root = root->right;
        }

    }


    return ino;
}


void ParseTree::parseInOrder(std::string expression)
{
    ParseStack.clear(); //Clears the stack out and resets the values.


    Deque<char> Stack; //Makes a new stack for chars, in order to conve
    std::string postfix = "";


    ParseNode* lastRoot = nullptr;  // Initialize a pointer to the last node of the parse tree (it is initially null).

    for (int i = 0; i < expression.size(); i++) {  // Loop through each character in the expression.
        char letter = expression[i];

        if (isOperand(letter)) {  // If the character is an operand, append it to the postfix string.
            postfix += letter;
        }
        else if (letter == '(') {  // If the character is an open parenthesis, add it to the stack.
            Stack.addTail(letter);
        }
        else if (letter == ')') {  // If the character is a close parenthesis, pop operators off the stack until an open parenthesis is reached.
            bool isPopping = true;

            while (!Stack.isEmpty() && isPopping) {
                char value = Stack.removeTail();
                if (value == '(') {
                    isPopping = false;
                }
                else {
                    postfix += value;
                }
            }
            // Any operators popped off the stack are added to the postfix string.
        }
        else if (!isOperand(letter)) {  // If the character is an operator, pop operators off the stack until an operator with lower precedence or an open parenthesis is reached.
            bool isPoppping = true;

            while (!Stack.isEmpty() && isPoppping) {
                char next = Stack.removeTail();

                if (next == '(') {  // If an open parenthesis is reached, it is added back to the stack, and the loop is terminated.
                    Stack.addTail(next);
                    isPoppping = false;
                }
                else {  
                    postfix += next;
                }
            }

            Stack.addTail(letter);  // The current operator is added to the stack.
        }
    }

    while (!Stack.isEmpty()) {  // Any operators left on the stack are added to the postfix string.
        postfix += Stack.removeTail();
    }



    doParse(postfix);  // Parse the postfix string to create the parse tree.

}
std::string ParseTree::postOrder()
{
    std::string data = ""; // Initializes an empty string to hold the infix expression
bool open = false; // Indicates whether an open parenthesis is currently needed
Deque<ParseNode*> s; // Initializes a stack to hold nodes from the parse tree
s.addTail(ParseStack.getHead()); // Adds the root node of the parse tree to the stack
ParseNode* prev = nullptr; // Initializes a pointer to keep track of the previously visited node

while(!s.isEmpty()) // Loops until the stack is empty
{
    ParseNode* current = s.getTail(); // Gets the node on top of the stack

    // If a child or parent is nullptr, go down left
    if(prev == nullptr || prev->left == current || prev->right == current)
    {
        // If there is a left child, add it to the stack and continue iterating
        if (current->left)
            s.addTail(current->left);
        // If there is a right child, add it to the stack and continue iterating
        else if (current->right)
            s.addTail(current->right);
        // If there are no children, remove the node from the stack and append its value to the infix string
        else{
            s.removeTail();
            if(open == false)
            {
                open = true;
            }
            data += current->value;
        }
    }
    // If we are revisiting the left child, add the right child (if it exists) and continue iterating
    else if (current->left == prev)
    {
        if(current->right)
            s.addTail(current->right);
        else {
            s.removeTail();
            if(open == true)
            {
                open = false;
            }
            data += current->value;
        }
    }
    // If we are revisiting the right child, remove the parent node from the stack and append its value to the infix string
    else if (current->right == prev)
    {
        s.removeTail();
        if(open == true)
        {
            open = false;
        }
        data += current->value;
    }
    prev = current; // Sets the current node as the previously visited node
}

return data; // Returns the infix string representation of the parse tree

}
std::string ParseTree::display()
{
    const int PAGE_WIDE = 64;   // defines the maximum width of the display page
std::string disp;           // the final string representation of the binary tree
ParseNode* root = ParseStack.getHead();  // get the root node of the binary tree from a stack
Deque<ParseNode*> q;        // a double-ended queue to hold nodes during traversal
std::string emptyNode = "."; // string to represent empty nodes
q.addTail(root);            // add the root node to the queue

int curNodes = 1;           // number of nodes to process at the current level
bool more = true;           // flag to indicate if there are more nodes to process

ParseNode* dummy = nullptr; // a dummy node to mark empty child nodes

while(more)
{
    more = false;           // assume there are no more nodes to process
    int offset = PAGE_WIDE/(curNodes*2); // calculate the offset for each node's position on the display page

    for(int i = 0; i < curNodes; i++)   // iterate through each node at the current level
    {
        ParseNode* ptr = q.removeHead();    // get the next node from the queue

        if(i == 1)  // adjust the offset for the second node at the level
        {
            offset *= 2;
        }

        if(ptr != dummy)    // process non-empty nodes
        {
            for(int s = 0; s < offset; s++) // add the appropriate number of spaces to the display string to position the node
            {
                disp += " ";
            }
            disp += ptr->value; // add the node's value to the display string

            if(ptr->left)  // add the node's left child to the queue if it exists
            {
                more = true;
                q.addTail(ptr->left);
            }
            else    // otherwise, add the dummy node to mark an empty child
            {
                q.addTail(dummy);
            }

            if(ptr->right) // add the node's right child to the queue if it exists
            {
                more = true;
                q.addTail(ptr->right);
            }else   // otherwise, add the dummy node to mark an empty child
            {
                q.addTail(dummy);
            }

        }else   // process empty nodes
        {
            for(int s = 0; s < offset; s++) // add the appropriate number of spaces to the display string to position the node
            {
                disp += " ";
            }
            disp += emptyNode;  // add the string to represent an empty node to the display string
            q.addTail(dummy);   // add two dummy nodes to the queue to mark the empty left and right children
            q.addTail(dummy);
        }
    }

    curNodes *= 2;  // update the number of nodes to process at the next level
    disp += "\n";   // add a newline character to the display string to start a new line
}

return disp; // return the final string representation of the binary tree

}
ParseTree::~ParseTree()
{
    ParseNode* root = ParseStack.getHead();
    ParseNode* prev = nullptr;
    Deque<ParseNode*> s;
    while(!s.isEmpty())
    {
        ParseNode* current = s.getTail();

        if(prev == nullptr || prev->left == current || prev->right == current) //if a child or parent is nullptr, go down left
        {
            if (current->left)
                s.addTail(current->left);
            else if (current->right)
                s.addTail(current->right);
            else{
                s.removeTail();
                delete current;
            }
        }
        else if (current->left == prev) //other wise if the operator 
        {
            if(current->right)
                s.addTail(current->right);
            else {
                s.removeTail();

                delete current;
            }
        }else if (current->right == prev)
        {
            s.removeTail();
            delete current;
        }
        prev = current;


    }
}