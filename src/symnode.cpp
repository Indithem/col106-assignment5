/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

inline int get_height(SymNode* A){
    int l{0},r{0};
    if (A->left!=NULL){l=A->left->height;}
    if (A->right!=NULL){r=A->right->height;}
    
    return max(l,r)+1;
}

inline bool onleft(SymNode* par, SymNode* child){
    return (par->left)==child;
}

SymNode::SymNode(){
    
}

SymNode::SymNode(string k){
    key=k;
    left=NULL;right=NULL;par=NULL; height=1;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* B = left;
    SymNode* T2 = B->right;

    left=T2; if(T2!=NULL){T2->par=this;}
    B->right=this;
    B->par=par; par=B;
    if(B->par!=NULL){
        if (onleft(B->par,this)){B->par->left=B;}
        else {B->par->right=B;}
    }

    height=get_height(this);
    B->height=get_height(B);
    return B;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* B = right;
    SymNode* T2 = B->left;

    right=T2; if(T2!=NULL){T2->par=this;}
    B->left=this;
    B->par=par; par=B;
    if(B->par!=NULL){
        if (onleft(B->par,this)){B->par->left=B;}
        else {B->par->right=B;}
    }

    height=get_height(this);
    B->height=get_height(B);
    return B;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* C= left->right;
    SymNode* T2= C->left;
    SymNode* T3= C->right;
    SymNode* B=left;
    SymNode* parent= par;

    B->right=T2; if(T2!=NULL){T2->par=B;}
    this->left=T3; if(T3!=NULL){T3->par=this;}

    C->left=B; B->par=C;
    C->right=this; this->par= C;

    C->par=parent;
    if(parent!=NULL){
        if(onleft(parent,this)){parent->left=C;}
        else{parent->right=C;}
    }

    B->height=get_height(B);
    this->height=get_height(this);
    C->height=get_height(C);

    return C;
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* B=right;
    SymNode* C= B->left;
    SymNode* T2= C->right;
    SymNode* T3= C->left;
    SymNode* parent= par;

    B->left=T2; if(T2!=NULL){T2->par=B;}
    this->right=T3; if(T3!=NULL){T3->par=this;}

    C->right=B; B->par=C;
    C->left=this; this->par= C;

    C->par=parent;
    if(parent!=NULL){
        if(onleft(parent,this)){parent->left=C;}
        else{parent->right=C;}
    }

    B->height=get_height(B);
    this->height=get_height(this);
    C->height=get_height(C);

    return C;
}

SymNode::~SymNode(){
    key.clear();delete left;delete right;
}