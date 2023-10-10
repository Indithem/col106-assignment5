/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){

}

ExprTreeNode::ExprTreeNode(string t,int v){
    type=t;num=v;
}

ExprTreeNode::~ExprTreeNode(){
    id.clear();
    type.clear();
    delete left; left=nullptr;
    delete right;right=nullptr;
}

