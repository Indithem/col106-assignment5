/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

// EPPCompiler::EPPCompiler(){

// }

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file=out_file;
    memory_size=mem_limit;
}

void EPPCompiler::compile(vector<vector<string>> code){
    {fstream writer;
    writer.open(output_file,ios::trunc);
    writer.close();}

    least_mem_loc.push_heap(-memory_size);
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
        if (targ.expr_trees.back()->type=="DEL"){
            varID=targ.expr_trees.back()->right->id;
            del_loc=symtable->search(varID);
            if(del_loc>=0){least_mem_loc.push_heap(del_loc);}
            symtable->remove(varID);
        }
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    // we had given memory to the new variable
    ExprTreeNode* root= targ.expr_trees.back();
    SymbolTable* symtable = targ.symtable;
    vector<string> commands;

    
}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream writer;
    writer.open(output_file,ios::app);
    for (string& command:commands){writer<<command<<"\n";}
    // writer.close(); destructor should call it!
}

EPPCompiler::~EPPCompiler(){
  
}
