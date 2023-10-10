/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

// EPPCompiler::EPPCompiler(){

// }

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file=out_file;
    memory_size=mem_limit;
    least_mem_loc.push_heap(-mem_limit);
}

void EPPCompiler::compile(vector<vector<string>> code){
    {ofstream writer;
    writer.open(output_file,ios::trunc);
    writer<<"\n";writer.close();}

    SymbolTable* symtable = targ.symtable;

    string varID;int del_loc;
    for (vector<string>& commands:code){
        targ.parse(commands);

        if (targ.expr_trees.back()->left->type=="VAR"){
            varID=targ.expr_trees.back()->left->id;
            if (symtable->search(varID)==-2){
                symtable->insert(varID);
                symtable->assign_address(varID,least_mem_loc.get_min());least_mem_loc.pop();
            }
        }

        write_to_file(generate_targ_commands());
        if (targ.expr_trees.back()->left->type=="DEL"){
            varID=targ.expr_trees.back()->right->id;
            del_loc=symtable->search(varID);
            if(del_loc>=0){least_mem_loc.push_heap(del_loc);}
            symtable->remove(varID);
        }

        targ.expr_trees.pop_back();
    }
}

struct VisitNode
{
    ExprTreeNode* node;
    // short unsigned visits=0;
    bool visited=false;
};


vector<string> EPPCompiler::generate_targ_commands(){
    // we had given memory to the new variable
    ExprTreeNode* root= targ.expr_trees.back();
    SymbolTable* symtable = targ.symtable;
    vector<string> commands;commands.reserve(5);
    

    string line;
    if (root->left->type=="DEL"){
        line="DEL = mem[";
        line=line+to_string(symtable->search(root->right->id))+']';
        commands.push_back(line);return commands;
    }

    vector<VisitNode> stack;
    stack.push_back(VisitNode{root->right,false});
    VisitNode* current;ExprTreeNode*l,*r;
    while(not stack.empty()){
        current=&stack.back();
        // if(current->visits==2){
        if(current->visited){
            commands.push_back(current->node->type);
            stack.pop_back();continue;
        }
        else{
            if(current->node->type=="VAL"){
                line="PUSH ";
                line=line+to_string(current->node->num);
                commands.push_back(line);stack.pop_back();continue;
            }
            if(current->node->type=="VAR"){
                line="PUSH mem[";
                line=line+to_string(symtable->search(current->node->id))+']';
                commands.push_back(line);stack.pop_back();continue;
            }
            // current->visits+=1;
            current->visited=true;
            l=current->node->left;
            r=current->node->right;
            stack.push_back(VisitNode{l,false});
            stack.push_back(VisitNode{r,false});
        }
    }

    if(root->left->type=="RET"){
        commands.push_back("RET = POP");
        return commands;
    }

    line="mem[";
    line=line+to_string(symtable->search(root->left->id))+"] = POP";
    commands.push_back(line);
    return commands;

}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream writer;
    writer.open(output_file,ios::app);
    for (string& command:commands){writer<<command<<"\n";}
    // writer.close(); destructor should call it!
}

EPPCompiler::~EPPCompiler(){
  
}

// #include<iostream>
// int main(){
//     EPPCompiler c{"test1.txt",2};
//     vector<vector<string>> comands={{"x",":=","(","5","-","2",")"},{"ret",":=","x"}};
//     c.compile(comands);
// }