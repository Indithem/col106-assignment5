/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    size=0;root=NULL;
}

void SymbolTable::insert(string k){
    size+=1;
    if(root==NULL){root= new SymNode{k};return;}
    SymNode* current= root;
    while(current!=NULL){
        if(current->key>k){current=current->left;continue;}
        current=current->right;
    }

    current=current->par;
    SymNode* created=new SymNode{k};
    created->par=current;
    if(current->key>k){current->left=created;current->height-=1;} else{current->right=created;current->height+=1;}

    //...need to complete...
}

void SymbolTable::remove(string k){
    if(size==0){return;}
    size-=1;
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