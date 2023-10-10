/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

inline int calc_height(SymNode* A){
    if (A->left==NULL){return A->right!=NULL;}
    if (A->right==NULL){return -(A->left!=NULL);}
    int l=A->left->height;
    int r=A->right->height;
    if (l!=0 or r!=0){return (r!=0)-(l!=0);}
    
}

SymNode::SymNode(){
    
}

SymNode::SymNode(string k){
    key=k;
    left=NULL;right=NULL; height=0;
}

SymNode* SymNode::LeftLeftRotation(){
    
    return NULL;
}

SymNode* SymNode::RightRightRotation(){
    return NULL;
}

SymNode* SymNode::LeftRightRotation(){
    return NULL;
}

SymNode* SymNode::RightLeftRotation(){
    return NULL;
}

SymNode::~SymNode(){
    key.clear();delete left;delete right;
}