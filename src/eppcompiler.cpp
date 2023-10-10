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

}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* root= targ.expr_trees.back();
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
