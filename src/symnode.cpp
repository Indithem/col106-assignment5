/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    
}

SymNode::SymNode(string k){
    key=k;
}

SymNode* SymNode::LeftLeftRotation(){

}

SymNode* SymNode::RightRightRotation(){

}

SymNode* SymNode::LeftRightRotation(){

}

SymNode* SymNode::RightLeftRotation(){

}

SymNode::~SymNode(){
    delete left;delete right;key.clear();
}