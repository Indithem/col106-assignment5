/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"


bool is_operator(string &s){
    static constexpr const char operator_chars[]={'+','-','/','*'};
    char t=s[0];
    if (s.length()!=1){return false;}
    for (const char&c : operator_chars){
        if (c==t){return true;}
    }
    return false;
}

bool is_number(string& s){
    static constexpr const char numbers[]={'1','2','3','4','5','6','7','8','9','0','-'};
    char t=s[0];
    for (const char&c : numbers){
        if (c==t){return true;}
    }
    return false;
}

//Write your code below this line

Parser::Parser(){
    expr_trees.clear();
    symtable = new SymbolTable;
    last_deleted=-1;
}

void Parser::parse(vector<string> expression){
    ExprTreeNode* root = new ExprTreeNode{};
    expr_trees.push_back(root);

    if (expression[0]=="del"){
        root->left=new ExprTreeNode{"DEL",0};
        root->right=new ExprTreeNode{"VAR",0};
        root->right->id=expression[2];
        last_deleted=symtable->search(expression[2]);
        return;
    }

    if (expression[0]=="ret"){
        root->left=new ExprTreeNode{"RET",0};
    }
    else{
        root->left=new ExprTreeNode{"VAR",0};
        root->left->id=expression[0];
    }

    vector<ExprTreeNode*> stack;
    stack.push_back(NULL);

    string s; ExprTreeNode* last_element=NULL;
    for (vector<string>::iterator i=expression.begin()+2;i<expression.end();i++){
        s = *i;

        if (s[0]=='('){stack.push_back(NULL);continue;}

        last_element=stack.back();

        if(s[0]==')'){
            ExprTreeNode* current = last_element;
            stack.pop_back();

            stack.pop_back(); //an NULL for (
            
            last_element=stack.back();
            if (last_element==NULL){stack.push_back(current);continue;}

            stack.pop_back();
            last_element->right=current;
            stack.push_back(last_element);
            continue;
        }

        if(is_operator(s)){
            string type;
            switch (s[0])
            {
            case '+':
                type="ADD";
                break;
            case '-':
                type="SUB";
                break;
            case '*':
                type="MUL";
                break;
            case '/':
                type="DIV";
                break;
            }

            ExprTreeNode* current= new ExprTreeNode{type,0};
            stack.pop_back();
            current->left=last_element;
            stack.push_back(current);continue;
        }

        //last ele is an num or var

        ExprTreeNode* current;
        if(is_number(s)){    
            current = new ExprTreeNode{"VAL",stoi(s)};
        }

        else{
            current= new ExprTreeNode{"VAR",0};
            current->id=s;
        }

        if(last_element==NULL){stack.push_back(current);continue;}
        else{
            last_element->right=current;
            continue;
        }
    }

    ExprTreeNode* operations_root = stack.back();
    root->right=operations_root;

}

Parser::~Parser(){
    expr_trees.clear();
    delete symtable;
}

#include<iostream>
int main(){
    Parser p;
    vector<string> vec={"del",":=","c","(","2",")","+","(","3","/","5",")"};
    p.parse(vec);
}