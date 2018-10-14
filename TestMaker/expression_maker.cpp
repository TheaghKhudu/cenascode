/* /
This program generates mathematical expressions which are supposed to test our main calculator program.
It can generate expressions with 3 different difficulty levels: easy, normal, hard.
The working principle of generating such expressions relies on P.O.C.L.(Probabilistic Operation Container List)
Therefore it is easier to change the structure of expressions in any time just by changing that list.
Easily managable, safe codes containing static lists and 'generic' functions to be able to work with those lists.
*/

#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include"../User_Interface/exception.hpp"

#define MAX_NB_OPR 24
#define M MAX_NB_OPR
#define MAX_NB_RORD 17
#define OUT_FILE "test_expr.txt"
#define NUMERICAL true
#define N_NUMERICAL false
#define EASY 0
#define NORMAL 1
#define HARD 2

using namespace std;

typedef struct OPERATION{
    private:
    static const std::string name[MAX_NB_OPR];
    static const unsigned length[MAX_NB_OPR];
    static const unsigned order[MAX_NB_OPR][MAX_NB_RORD];
    
    public:
    static unsigned jump_length(unsigned index);
    static std::string get_name(unsigned i);
    static unsigned get_order(unsigned i, unsigned j);
}Operation;

typedef struct POCL{
    private:
    Operation operation;
    unsigned prob[MAX_NB_OPR-1];
    int PROB[MAX_NB_OPR][MAX_NB_RORD];
    int OFFSET[MAX_NB_OPR-1];
    string expression;

    public:
    POCL(const Operation& operation): operation(operation) {}
    void set_prob(const unsigned* prob);
    void init_PROB();
    unsigned get_rand_opr_index(unsigned opr_index);
    string get_expression(unsigned max_length);

    void print_prob();
    void print_PROB();
}POCL;

//Expression_Lit POCL::list=

int main(int argc, char* argv[]){
//the syntax : ./expr_maker [-numerical] [-level] [char length]
    
    if(argc!=4){ cout<<"The syntax : ./expr_maker [-numerical] [-level] [char length]\n"; exit(0); }
    bool numerical=strcmp(argv[1],"-n")==0? NUMERICAL : N_NUMERICAL;
    int args[2]={atoi(argv[2]),atoi(argv[3])};
    if(0>args[1] || args[1]>500){ cout<<"char length should be less than 500!\n"; exit(0); }
    string expression;

    const Operation operation;
    POCL pocl(operation);
    unsigned* prob=nullptr;
    
    //set your lists below by changing the numbers of correspoinding prob
    const unsigned prob_EASY[23]{0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,39,65,91,156,221,325,429,507};
    const unsigned prob_NORMAL[23]{10,20,23,24,25,26,27,28,29,30,31,32,33,34,35,40,45,50,51,70,80,81,82};
    const unsigned prob_HARD[23]{20,40,43,53,63,73,83,93,93,93,93,93,93,93,93,96,97,98,99,110,140,141,142};

    switch(args[0]){
        case EASY:
            prob=const_cast<unsigned*>(prob_EASY);
            break;
        case NORMAL:
            prob=const_cast<unsigned*>(prob_NORMAL);
            break;
        case HARD:
            prob=const_cast<unsigned*>(prob_HARD);
            break;
        default:
            cout<<"Difficulty level can be 0/1/2!\n";
            exit(0);
    }
    srand(time(nullptr));
    //ofstream out; unsigned counter=0;
    //out.open(OUT_FILE);
    //GET:
    //++counter;
    if(numerical){
        //cout<<"Init prob : "<<'\n';
        pocl.set_prob(prob);
        //pocl.print_prob();
        //cout<<"Init PROB : "<<'\n';
        pocl.init_PROB();
        //pocl.print_PROB();
        //cout<<"Get Expression : "<<'\n';
        expression=pocl.get_expression(args[1]);
    } else{
        cout<<"Not ready to generate!\n";
        exit(0);
    }

    ofstream out;
    out.open(OUT_FILE);
    out<<expression;
    expression.clear();
    //if(counter<50000){ goto GET; }
    out.close();

    return 0;
}

/* Operation block */

const std::string Operation::name[MAX_NB_OPR]={
    "(", ")", "log", "arcsinh", "arccosh", "arctanh",
    "arcsin", "arccos", "arctan", "sinh", "cosh", "tanh",
    "sin", "cos", "tan", "^", "!", "%", "*", "/", "+", "-", "1", "."
};

const unsigned Operation::length[MAX_NB_OPR]={
    1, 1, 3, 7, 7, 7, 6, 6, 6, 4, 4, 
    4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
const unsigned Operation::order[MAX_NB_OPR][MAX_NB_RORD]={
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 20, 21, 22},
    {1, 15, 16, 17, 18, 19, 20, 21, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {1, 16, 17, 18, 19, 20, 21, 22, M, M, M, M, M, M, M, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {1, 15, 16, 17, 18, 19, 20, 21, 22, 23, M, M, M, M, M, M, M},
    {22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M}
};

unsigned Operation::jump_length(unsigned index){
    return length[index];
}

std::string Operation::get_name(unsigned i){ return Operation::name[i]; } // for expression_maker

unsigned Operation::get_order(unsigned i, unsigned j){ return Operation::order[i][j]; }

/* P.O.C.L. block */

void POCL::set_prob(const unsigned* prob){
    for(unsigned i=0;i<23;++i){ this->prob[i]=prob[i]; }
}

void POCL::init_PROB(){
    unsigned ord_index=0;
    for(unsigned i=0;i<MAX_NB_OPR-1;++i){
        PROB[i][0]=0;
        for(unsigned j=1;j<=MAX_NB_RORD;++j){
            ord_index=Operation::get_order(i,j-1);
            if(ord_index==M || ord_index==M-1){
                PROB[i][j]=-1;    
                break;
            }
            PROB[i][j]=prob[ord_index];
        }
    }
}

unsigned POCL::get_rand_opr_index(unsigned opr_index){
    //srand(time(nullptr));
    //cout<<"offset["<<opr_index<<"] : "<<OFFSET[opr_index]<<'\n';
    int r=rand()%OFFSET[opr_index];
    for(unsigned i=0;i<22;++i){ //i - index
        //cout<<"Comparing : "<<PROB[opr_index][i]<<"<="<<r<<"<"<<PROB[opr_index][i+1]<<'\n';
        if(PROB[opr_index][i]<=r && r<PROB[opr_index][i+1]){
            //cout<<"Returned new opr_index : "<<i<<'\n';
            return i;
        }
    }
}

string POCL::get_expression(unsigned max_length){
    //srand(time(nullptr));
    unsigned index=22, size=0;
    for(unsigned i=0;i<23;++i){
        OFFSET[i]=-1;
        for(unsigned j=0;j<17;++j){
            if(PROB[i][j]==-1){ break; }
            OFFSET[i]=PROB[i][j];
        }
    }
    if(!expression.empty()){ expression.clear(); }
    // cout<<"OFFSET : \n";
    // for(unsigned i=0;i<23;++i){
    //     if(OFFSET[i]==0){ cout<<"offset is 0 :(\n"; continue; }
    //     cout<<OFFSET[i]<<" ";
    // }   cout<<'\n';
    
    unsigned beg=rand()%3;
    if(beg==0){ expression+="-"; size=1;  index=21; }
    else if(beg==1){ expression+="+"; size=1; index=20; }
    else if(beg==2){ expression+=to_string(rand()%9+1); size=1; }
    unsigned index1=0, i=0; int op=0;
    while(size<max_length){
        index1=get_rand_opr_index(index);
        i=Operation::get_order(index,index1);
        if(i==1 && op==0){ continue; }
        index=i;
        //cout<<"index + index1 : "<<index<<" and "<<index1<<'\n';
        if(index==22){ /*cout<<"index=22!\n";*/ i=rand()%9+1; expression+=to_string(i); }
        else{
            if(index==0){ ++op; }
            else if(index==1 && op>0){ --op; }
            expression+=Operation::get_name(index);
        }
        size+=Operation::jump_length(index);
        //cout<<"\t\texpression : "<<expression<<'\n';
    }
    size=expression.size();
    if(expression[size-1]!=')' && expression[size-1]!='!' && !isdigit(expression[size-1])){
        expression+=to_string((rand()%9+1));
        if(expression[size-1]=='('){ expression+=")"; --op; }
    }

    for(int i=0;i<op;++i){ expression+=")"; }
    //cout<<"Expression : "<<expression<<'\n';
    return expression;
}

void POCL::print_prob(){
    for(unsigned i=0;i<23;++i){
        cout<<this->prob[i]<<'\n';
    }
}

void POCL::print_PROB(){
    for(unsigned i=0;i<23;++i){
        for(unsigned j=0;j<17;++j){
            if(this->PROB[i][j]==-1){ break; }
            cout<<this->PROB[i][j]<<" ";
        }   cout<<'\n';
    }
}
