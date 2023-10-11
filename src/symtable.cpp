/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

inline int balance_factor(SymNode* A){
    if (A==NULL){return 0;}
    int l{0},r{0};
    if (A->left!=NULL){l=A->left->height;}
    if (A->right!=NULL){r=A->right->height;}
    
    return r-l;
}

inline int get_height(SymNode* A){
    int l{0},r{0};
    if (A->left!=NULL){l=A->left->height;}
    if (A->right!=NULL){r=A->right->height;}
    
    return max(l,r)+1;
}

SymbolTable::SymbolTable(){
    size=0;root=NULL;
}

void inline balance_till_root(SymNode* start,SymNode* &root){
    SymNode* current = start; int balfac,bf2; bool change_root=false;
    while(true){
        change_root= current==root;

        current->height=get_height(current);
        balfac=balance_factor(current);
        //can optimize this with a switch stmt;
        if(balfac==2){
            bf2=balance_factor(current->right);
            if (bf2==-1){current=current->RightLeftRotation();}
            else{current=current->RightRightRotation();}
        }
        else if(balfac==-2){
            bf2=balance_factor(current->left);
            if (bf2==1){current=current->LeftRightRotation();}
            else{current=current->LeftLeftRotation();}
        }
        
        if (change_root){root=current;return;}
        current=current->par;
    }
}

void SymbolTable::insert(string k){
    //surely the element doesnt exist before
     size++;
    if(root==NULL){root=new SymNode{k};return;}

    SymNode*prev_position{root},*position=root;
    while(position!=NULL){
        prev_position=position;
        if (position->key>k){position=position->left;}
        else{position=position->right;}
    }

    if(prev_position->key>k){prev_position->left=new SymNode{k};prev_position->left->par=prev_position;}
    else{prev_position->right= new SymNode{k};prev_position->right->par=prev_position;}

    balance_till_root(prev_position,root);
}

void SymbolTable::remove(string k){
    // the element maynot exist
    SymNode*node=root;
    SymNode*parent=root;
    while(node!=NULL and node->key!=k){
        parent=node;
        if (node->key>k){node=node->left;}
        else{node=node->right;}
    }

    if(node==NULL){return;}
    int checking = (node->left==NULL) +2*(node->right==NULL);
    bool node_on_left = (parent->left==node);

    switch (checking)
    {
    case 3:
        size--;
        if (node_on_left){parent->left=NULL;}
        else{parent->right=NULL;}
        if(node==root){root=NULL;parent=NULL;}
        delete node;
        break;
    case 2:
        if(node_on_left){parent->left=node->left;}
        else{parent->right=node->left;}
        if(node==root){root=node->right;parent=NULL;}
        node->left=NULL;node->right=NULL;
        delete node;
        size--;
    break;
    case 1:
        if(node_on_left){parent->left=node->right;}
        else{parent->right=node->right;}
        if(node==root){root=node->right;}
        node->right=NULL;node->left=NULL;
        delete node;
        size--;
    break;
    case 0:
        SymNode* replacable,*replacable_parent;
        
        replacable_parent=node;
        replacable=node->right;

        while(replacable->left!=NULL){replacable_parent=replacable;replacable=replacable->left;}

        if(node==root){root=replacable;parent=NULL;}

        if(node_on_left){parent->left=replacable;}
        else{if(parent!=NULL){parent->right=replacable;}}
        replacable->par=parent;

        replacable->left=node->left;node->left->par=replacable;

        if(replacable_parent!=node){
            replacable_parent->left=replacable->right;replacable->right->par=replacable_parent;
            replacable->right=node->right;node->right->par=replacable;
        }

        node->left=NULL;node->right=NULL;
        delete node;
        size--;
        break;
    }

    balance_till_root(parent,root);
}

int SymbolTable::search(string k){
    SymNode* current= root;
    while(current!=NULL and current->key!=k){
        if(current->key>k){current=current->left;continue;}
        current=current->right;
    }
    if(current==NULL){return -2;}
    return current->address;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* current= root;
    while(current!=NULL and current->key!=k){
        if(current->key>k){current=current->left;continue;}
        current=current->right;
    } 
    if(current==NULL){return;}
    current->address=idx;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    delete root;
}

#include<iostream>
int main(){
    SymbolTable avl;

    for (char c: "123456"){
        avl.insert(string{c});
    }
    for (char c: "356124"){
        avl.remove(string{c});
    }
}