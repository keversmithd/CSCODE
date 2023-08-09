#ifndef R_ARCHTREE_H
#define R_ARCHTREE_H
#include <vector>
struct RVec
{
    float x,y,z;
};

struct RBoundingContainer
{
    RVec LowerLeft;
    RVec UpperRight;
};

bool RectangleIntersection(const RBoundingContainer A, const RBoundingContainer B)
{
    // Check for intersection in the x-dimension
    bool xOverlap = (A.LowerLeft.x <= B.UpperRight.x && A.UpperRight.x >= B.LowerLeft.x);
    
    // Check for intersection in the y-dimension
    bool yOverlap = (A.LowerLeft.y <= B.UpperRight.y && A.UpperRight.y >= B.LowerLeft.y);
    
    // Check for intersection in the z-dimension
    bool zOverlap = (A.LowerLeft.z >= B.UpperRight.z && A.UpperRight.z <= B.LowerLeft.z);

    // If there's overlap in all three dimensions, the rectangles intersect
    return (xOverlap && yOverlap && zOverlap);
}
float EnlargementOfBoundingContainer(RBoundingContainer User, const RBoundingContainer Enlarged)
{
    //calculate the bounding container of the two boxes

    RBoundingContainer NewContainer;

    NewContainer.LowerLeft.x = (User.LowerLeft.x < Enlarged.LowerLeft.x) ? User.LowerLeft.x : Enlarged.LowerLeft.x;
    NewContainer.LowerLeft.y = (User.LowerLeft.y < Enlarged.LowerLeft.y) ? User.LowerLeft.y : Enlarged.LowerLeft.y;
    NewContainer.LowerLeft.z = (User.LowerLeft.z > Enlarged.LowerLeft.z) ? User.LowerLeft.z : Enlarged.LowerLeft.z;

    NewContainer.UpperRight.x = (User.UpperRight.x < Enlarged.UpperRight.x) ? User.UpperRight.x : Enlarged.UpperRight.x;
    NewContainer.UpperRight.y = (User.UpperRight.y < Enlarged.UpperRight.y) ? User.UpperRight.y : Enlarged.UpperRight.y;
    NewContainer.UpperRight.z = (User.UpperRight.z > Enlarged.UpperRight.z) ? User.UpperRight.z : Enlarged.UpperRight.z;

    float NewVolume = (NewContainer.UpperRight.x - NewContainer.LowerLeft.x)*(NewContainer.UpperRight.y - NewContainer.LowerLeft.y)*(-1*NewContainer.UpperRight.z - NewContainer.LowerLeft.z);
    float EnlargedVolume = (Enlarged.UpperRight.x - Enlarged.LowerLeft.x)*(Enlarged.UpperRight.y - Enlarged.LowerLeft.y)*(-1*Enlarged.UpperRight.z - Enlarged.LowerLeft.z);
    return NewVolume - EnlargedVolume;

    //calculate the volume of the two boxes df
}

RBoundingContainer EnlargedContainer(RBoundingContainer User, const RBoundingContainer Enlarged)
{
    RBoundingContainer NewContainer;

    NewContainer.LowerLeft.x = (User.LowerLeft.x < Enlarged.LowerLeft.x) ? User.LowerLeft.x : Enlarged.LowerLeft.x;
    NewContainer.LowerLeft.y = (User.LowerLeft.y < Enlarged.LowerLeft.y) ? User.LowerLeft.y : Enlarged.LowerLeft.y;
    NewContainer.LowerLeft.z = (User.LowerLeft.z > Enlarged.LowerLeft.z) ? User.LowerLeft.z : Enlarged.LowerLeft.z;

    NewContainer.UpperRight.x = (User.UpperRight.x < Enlarged.UpperRight.x) ? User.UpperRight.x : Enlarged.UpperRight.x;
    NewContainer.UpperRight.y = (User.UpperRight.y < Enlarged.UpperRight.y) ? User.UpperRight.y : Enlarged.UpperRight.y;
    NewContainer.UpperRight.z = (User.UpperRight.z > Enlarged.UpperRight.z) ? User.UpperRight.z : Enlarged.UpperRight.z;
    return NewContainer;
}


struct RPage
{
    std::vector<REntry> entries;
    
};
struct RData
{
    int externalIdentifier;
    RBoundingContainer boundingVolume;
};

struct RLeaf
{
    RBoundingContainer value;
};


struct RNode;
struct REntry
{
    RNode* child = nullptr;
    RBoundingContainer boundingVolume;  
};

struct RNode
{
    std::vector<REntry> entries;
    std::vector<RBoundingContainer> data;

    RNode()
    {

    }

    RNode(const RBoundingContainer object)
    {

    }


    bool isLeaf()
    {
        return (entries.empty());
    }

};
#endif