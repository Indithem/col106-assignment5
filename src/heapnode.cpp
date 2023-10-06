/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    left=NULL;right=NULL;par=NULL;
}

HeapNode::HeapNode(int _val){
    left=NULL;right=NULL;par=NULL;
    val=_val;
}

HeapNode::~HeapNode(){
  delete left; delete right;
}