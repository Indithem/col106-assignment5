/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    size=0;root=NULL;
}

void SymbolTable::insert(string k){
     size++;
    if(root==nullptr){root=new SymNode{k};return;}

    SymNode*prev_position{root},*position=root;
    while(position!=nullptr){
        prev_position=position;
        if (position->key>k){position=position->left;}
        else{position=position->right;}
    }
    if(prev_position->key>k){prev_position->left=\
    new SymNode{k};return;}
    else{prev_position->right= new SymNode{k};return;}
    //...need to complete...
}

void SymbolTable::remove(string k){
    SymNode*node=root;
    SymNode*parent=root;
    while(node!=nullptr and node->key!=k){
        parent=node;
        if (node->key>k){node=node->left;}
        else{node=node->right;}
    }

    if(node==nullptr){return;}
    int checking = (node->left==nullptr) +2*(node->right==nullptr);
    bool node_on_left = (parent->left==node);

    switch (checking)
    {
    case 3:
        size--;
        if(node==root){root=nullptr;}
        delete node;
        return;
    case 2:
        if(node_on_left){parent->left=node->left;}
        else{parent->right=node->left;}
        if(node==root){root=node->right;}
        node->left=nullptr;node->right=nullptr;
        delete node;
        size--;
    return;
    case 1:
        if(node_on_left){parent->left=node->right;}
        else{parent->right=node->right;}
        if(node==root){root=node->right;}
        node->right=nullptr;node->left=nullptr;
        delete node;
        size--;
    return;
    case 0:
        SymNode* replacable,*replacable_parent;
        
        replacable_parent=node;
        replacable=node->right;

        while(replacable->left!=nullptr){replacable_parent=replacable;replacable=replacable->left;}

        if(node==root){root=replacable;}

        if(node_on_left){parent->left=replacable;}
        else{if(node!=root){parent->right=replacable;}}

        replacable->left=node->left;

        if(replacable_parent!=node){
            replacable_parent->left=replacable->right;
            replacable->right=node->right;
        }

        node->left=nullptr;node->right=nullptr;
        delete node;
        size--;
        return;

    return;
    }
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