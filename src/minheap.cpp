/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){
    size=0;root=NULL;
}

void MinHeap::push_heap(int num){
    if (root==NULL){root= new HeapNode(num); return;}
    // continuing in this manner is very bad...
}

int MinHeap::get_min(){

}

void MinHeap::pop(){

}

MinHeap::~MinHeap(){
    delete root;
}