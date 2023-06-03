#include "Tree.hpp"

Tree::Tree() : root(nullptr)
{

}

void Tree::insertValue(const int value)
{
    if(root == nullptr)
    {
        TreeNode* nr = new TreeNode();
        nr->value =  value;
        root = nr;
    }else
    {
        TreeNode* nr = root;
        int z = 0;
        bool found = false;
        while(nr != nullptr && found == false)
        {
            if(value < nr->value)
            {
                if(nr->left)
                    nr = nr->left;
                else
                {
                    z = 0;
                    found = true;
                }
                    
            }else if(value > nr->value)
            {
                if(nr->right)
                    nr = nr->right;
                else{
                    z = 1;
                    found = true;
                }
            }else
            {
                return;
            }
        }

        if(z == 0)
        {
            TreeNode* dd = new TreeNode();
            dd->value = value;
            nr->left = dd;
        }else
        {
            TreeNode* dd = new TreeNode();
            dd->value = value;
            nr->right = dd;
        }

    }
}



std::string Tree::inOrder()
{
    std::string mainString = "";
    inOrderRec(mainString, root); //Calls the recurvsive functions on the root node for inorder traversal and string appenison.
    return mainString;
}

std::string Tree::preOrder()
{
    std::string mainString = "";
    preOrderRec(mainString, root); //Calls the recurvsive functions on the root node for preorder traversal and string appenison.
    return mainString;
}
std::string Tree::postOrder()
{
    std::string mainString = "";
    postOrderRec(mainString, root); //Calls the recurvsive functions on the root node for postorder traversal and string appenison.
    return mainString;

}
std::string Tree::display()
{
    const int PAGE_WIDE = 64;   // defines the maximum width of the display page
    std::string disp;           // the final string representation of the binary tree
    Deque<TreeNode*> q;        // a double-ended queue to hold nodes during traversal
    std::string emptyNode = "."; // string to represent empty nodes
    q.addTail(root);            // add the root node to the queue

    int curNodes = 1;           // number of nodes to process at the current level
    bool more = true;           // flag to indicate if there are more nodes to process

    TreeNode* dummy = nullptr; // a dummy node to mark empty child nodes

    while(more)
    {
        more = false;           // assume there are no more nodes to process
        int offset = PAGE_WIDE/(curNodes*2); // calculate the offset for each node's position on the display page

        for(int i = 0; i < curNodes; i++)   // iterate through each node at the current level
        {
            TreeNode* ptr = q.removeHead();    // get the next node from the queue

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
                disp += std::to_string(ptr->value); // add the node's value to the display string

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
void Tree::inOrderRec(std::string& s, TreeNode* n)
{
    if(!n){return;}
    inOrderRec(s,n->left); //Travel down the left subtree, and the left lefts subtree etc.
    s+=std::to_string(n->value) + ", "; //pop out after all left gone and add to the string s
    inOrderRec(s, n->right); //pop out to the right subtree.
}

void Tree::preOrderRec(std::string& s, TreeNode* n)
{
    if(!n){return;}
    s+=std::to_string(n->value) + ", "; //add value to string
    preOrderRec(s,n->left); //add left tree first
    preOrderRec(s,n->right); //add right tree second
} 

void Tree::postOrderRec(std::string& s, TreeNode* n)
{
    if(!n){return;}
    postOrderRec(s, n->left); //travel left tree, pop at bottom
    postOrderRec(s, n->right); //travel right trees
    s+=std::to_string(n->value) + ", "; //pop back into the string
}

bool Tree::findValue(const int value)
{
    if(root == nullptr)
    {
        return false; //If tree empty return false.
    }else
    {
        TreeNode* nr = root; //Select iterative node as the root.
        while(nr != nullptr) //While the node is not nullptr...
        {
            if(value < nr->value) //If the value of the node is greater the value...
                nr = nr->left; //Move to the left.
            else if(value > nr->value) //other wise go to the right
                nr = nr->right;
            else
                return true; //if they are equal than return true.
        }
    }

    return false;
}

void Tree::removeValue(const int value)
{
    if(root == nullptr)
    {
        return; //If tree empty return;
    }else
    {
        TreeNode* nr = root; //Root iterative node.
        TreeNode* pr = nullptr; //Parent iterative node.
        bool lr = false; //Indicator if the value was a left or right node of the parent.
        bool found = false; //A found locaiton variable.

        while(nr != nullptr && found == false) //While found is false and the iterative node is not a nullptr.
        {   
            if(value < nr->value) //If the value of the node is greater the value...
            {
                pr = nr; //Set parent to current node.
                lr = false; //Set the indicator to specificy that this node is a left child of the parent.
                nr = nr->left; //Move left.
            }else if(value > nr->value)
            {
                pr = nr; //Set parent to current node.
                lr = true; //Set the indicator to specifiy that this node is a right child of the parent.
                nr = nr->right; //Move right.
            }else
            {
                found = true; //Other wise break and set found to true.
            }
        }


        TreeNode* temp = nr;
        if(!temp->left && !temp->right) //If the node has no children then simply
        {
            (lr) ? pr->right = nullptr : pr->left = nullptr; //Set the left or right child of parent to nullptr depending on which sub tree of the parent the removed node is from.
            delete temp; //Delete the node
        }else
        if(temp->left && temp->right) //If the node has a left and right child.
        {
            TreeNode* RightLeftNull = nr->right; //The nodes right child.
            TreeNode* RLNP = nullptr; //Parent node of the right left null node.
            while(RightLeftNull->left != nullptr)
            {
                RLNP = RightLeftNull;
                RightLeftNull = RightLeftNull->left;
            }
            //Select the node for which its left is nullptr and cannot progress any furthur.

            //we've found a node with empty left where NR->LEFT BELONGS

            RightLeftNull->left = nr->left; //Set this nullptr node to the left sub tree of the removed node.

            TreeNode* RightSubs = RightLeftNull->right; //Select the right sub tree of the "replacement node" Right left null.

            //If no right subs, then just change left
            if(RightSubs)
            {
                //place right subs into nr->rights left subtree,
                while(RightSubs->right != nullptr)
                {
                    RightSubs = RightSubs->right;
                }
                //Select the node for which right has a nullptr and cannot progress any furthur

                RightSubs->right = nr->right; //and move the right sub tree of the removed node to this location.
            }else //other wise if the right side is nullptr.
            {
                if(RLNP)
                {
                    RLNP->left = nullptr; //Set the left sub tree of the left parent tree to nullptr.
                    RightLeftNull->right = nr->right; //Sets the right subtree of the replacement node to this right sub tree
                }else
                {
                    RightLeftNull->right = nr->right->right; //Other wise if no parent and inital node, then set right sub tree to the right right node of removed node.
                }
                
            }

            (lr) ? pr->right = RightLeftNull : pr->left = RightLeftNull; //if left child, set parents right to the replacement node, otherwise do the left.
            delete temp; //and delete temp.

        }else
        {
            TreeNode* replacement = (nr->left) ? nr->left : nr->right; //other wise if only onechild, find that node.
            (lr) ? pr->right = replacement : pr->left = replacement;  //replace it.
            delete temp; //and delete it.
        }

    }
}

int Tree::findLarger(const int value)
{
    //because I am confused about what this function is supposed to accomplish, it does not want the smallest node larger than value, it wants something more confusing like that something
    //that is only apart of a specific path in the tree so it is a bit more confusing, and could be infinetly stable if i was able to use a stack but since I wasn't.
    if(root == nullptr)
    {
        return -1; //if tree empty return -1.
    }else
    {
        TreeNode* nr = root; //current iterative node.
        TreeNode* gp = nullptr; //grandparent.
        TreeNode* gpp = nullptr; //grandparent parent.
        bool lr = false; //left or right values
        TreeNode* pr = nullptr; //parent.

        while(nr != nullptr)
        {
            //Begin binary search proccess updating all of the parent nodes.
            if(value < nr->value)
            {
                gpp = gp;
                gp = pr;
                pr = nr;
                lr = false;
                nr = nr->left;
            }  
            else if(value > nr->value)
            {
                gpp = gp;
                gp = pr;
                pr = nr;
                lr = true;
                nr = nr->right;
            } //End binary search proccess.
            else //Once the value equals the node.
            {
                if(pr) //If has parent.
                {
                    if(!lr) //if is in left sub tree
                    {
                        return pr->value; //then the parent is larger and nothing else is smaller and larger.
                    }
                    if(nr->right) //if has right.
                    {
                        return nr->right->value; //return this.
                    }
                    if(pr->right && pr->right->value >= value)
                    {
                        return pr->right->value; //other wise if parent right has value return it.
                    }
                    return-1;
                }else //other wise.
                {
                    if(nr == root)
                    {
                        return nr->value; //if root return root.
                    }
                    if(nr->right) //if right return right.
                    {
                        
                        return nr->right->value;
                    }
                    return -1;
                }
            }


        }


        if(pr) //if nothing has returned yet aka value not found.
        {
            if(!lr) //return parent information if in left sub tree again.
            {
                return pr->value;
            }else
            {
                if(gp && gp->value > value) //otherwise useing grandparent values for best fit.
                {

                    return gp->value;
                }
                else if(gpp && gpp->value > value)
                {
                    return gpp->value;
                    
                }
                else
                {
                    return -1;
                }
            }
        }

        return -1;
        
    }
}
int Tree::removeLarger(const int value)
{
    if(root == nullptr)
    {
        return -1; //if tree empty return -1.
    }else
    {
        TreeNode* nr = root; //current iterative node.
        TreeNode* gp = nullptr; //grandparent.
        TreeNode* gpp = nullptr; //grandparent parent.
        bool lr = false; //left or right values
        TreeNode* pr = nullptr; //parent.

        while(nr != nullptr)
        {

            //Begin binary search proccess updating all of the parent nodes.    
            if(value < nr->value)
            {
                gpp = gp;
                gp = pr;
                pr = nr;
                lr = false;
                nr = nr->left;
            }  
            else if(value > nr->value)
            {
                gpp = gp;
                gp = pr;
                pr = nr;
                lr = true;
                nr = nr->right;
            }  //End binary search proccess.
            else //Once the value equals the node.
            {
                if(pr)   //If has parent.
                {
                    if(!lr) //if is in left sub tree
                    {
                        if(pr->left->value == value) //then the parent is larger and nothing else is smaller and larger.
                        {
                            int temp = value;
                            removeValue(temp); //remove this value, and return it
                            return temp;
                        }
                        int temp = pr->value;
                        removeValue(temp); //remove this value, and return it
                        return temp;
                    }
                    if(nr->right) //if has right.
                    {
                        if(nr->value == value) 
                        {
                            int temp = value;
                            removeValue(temp); //remove this value, and return it
                            return temp;
                        }
                        int temp = nr->right->value;
                        removeValue(temp); //remove this value, and return it
                        return temp;
                    }
                    if(pr->right && pr->right->value >= value) //other wise if parent right has value return it.
                    {
                        int temp = pr->right->value;
                        removeValue(temp); //remove this value, and return it
                        return temp;;
                    }
                    return-1;
                }else //other wise.
                {
                    if(nr == root)
                    {
                        int temp = nr->value;
                        removeValue(temp); //remove this value, and return it
                        return temp;
                    }
                    if(nr->right)
                    {
                        int temp = nr->right->value;
                        removeValue(temp); //remove this value, and return it
                        return temp;
                    }
                    return -1;
                }
            }


        }


        if(pr) //if nothing has returned yet aka value not found.
        {
            if(!lr)
            {
                //if root return root.
                //if right return right.
                int temp = pr->value;
                removeValue(temp); //remove this value, and return it
                return temp;
            }else
            {
                if(gp && gp->value > value)
                {
                    int temp = gp->value;
                    removeValue(temp); //remove this value, and return it
                    return temp;
                }
                else if(gpp && gpp->value > value)
                {
                    int temp = gpp->value;
                    removeValue(temp); //remove this value, and return it
                    return temp;
                    //teacher said cant use stack thats why the code is bad.
                }
                else
                {
                    return -1;
                }
            }
        }

        return -1;
        
    }
}