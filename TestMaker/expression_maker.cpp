/* /14.10.2018
This program generates mathematical expressions which are supposed to test our main calculator program.
It can generate expressions with 3 different difficulty levels: easy, normal, hard.
The working principle of generating such expressions relies on P.O.C.L.(Probabilistic Operation Container List)
Therefore it is easier to change the structure of expressions in any time just by changing that list.
Easily managable, safe codes containing static lists and 'generic' functions to be able to work with those lists.

V2 /15.10.2018
Upgraded:
    -Precise P.O.C.L. structure
    -factorial order bug fixed (5!+3)
    -opened parantheses bug fixed
    -3 difficulty levels have been set up
    -first position operators have been organized
    -fail counter has been added in order to increase efficiency
    -function reducement
    -new mode("silent") has been added
*/

#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<unistd.h>
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
    unsigned* prob;
    int PROB[MAX_NB_OPR-1][MAX_NB_RORD];
    int OFFSET[MAX_NB_OPR-1];
    string expression;

    public:
    POCL(const Operation& operation,unsigned* prob): 
        operation(operation) , prob(prob) {}
    void init_PROB();
    unsigned get_rand_opr_index(unsigned opr_index, bool is_fail);
    string get_expression(unsigned max_length, unsigned level);

    void print_prob();
    void print_PROB();
}POCL;

int main(int argc, char* argv[]){
//the syntax : ./expr_maker [-numerical] [-level] [char length]
    
    if(!(argc==4 || argc==5)){ cout<<"The syntax : ./expr_maker [-numerical] [level] [char length]\n"; exit(0); }
    bool silent=false;
    if(argc==5 && strcmp(argv[4],"-s")==0){ silent=true; }
    bool numerical=strcmp(argv[1],"-n")==0? NUMERICAL : N_NUMERICAL;
    int args[2]={atoi(argv[2]),atoi(argv[3])};
    if(args[1]<=0 || args[1]>500){ cout<<"char length should be less than 500!\n"; exit(0); }
    string expression;

    const Operation operation;
    const unsigned* prob=nullptr;

    //set your lists below by changing the numbers of correspoinding prob
    // 2.      0%
    // 13.     ~0.365%
    // 3.      ~9.489%
    // 2.      ~23.722%
    // 2.      ~37.956%
    // 1.      ~28.467%
    const unsigned prob_EASY[MAX_NB_OPR-1]{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,26,26,26,65,65,104,104,78};
    const unsigned prob_NORMAL[MAX_NB_OPR-1]{15,500,2,2,2,2,2,2,2,2,2,2,2,2,2,150,150,150,120,120,80,80,150};
    const unsigned prob_HARD[MAX_NB_OPR-1]{100,50,10,10,10,10,10,10,10,10,10,10,10,10,10,130,65,65,65,65,65,65,30};

    switch(args[0]){
        case EASY:
            prob=prob_EASY;
            break;
        case NORMAL:
            prob=prob_NORMAL;
            break;
        case HARD:
            prob=prob_HARD;
            break;
        default:
            cout<<"Difficulty level can be 0/1/2!\n";
            exit(0);
    }
    srand(time(nullptr));

    POCL pocl(operation, const_cast<unsigned*>(prob));
    string file_name; int NB, opt;
    cout<<"Enter a file name(Press : and hit enter for default name) : ";
    cin>>file_name;
    if(file_name.compare(":")==0){ file_name=OUT_FILE; }
    cout<<"Enter the number of expressions to be generated : ";
    cin>>NB;
    ofstream out;
    out.open(file_name);
    // if(!out.good() || !out.eof()){
    //     cout<<"File isn't empty. (1)Rewrite or (2)Append? ";
    //     cin>>opt;
    //     if(opt==2){ out.seekp(0,ios::end); }
    // }
    for(int nb=0;nb<NB;++nb){
        if(numerical){
            pocl.init_PROB();
            expression=pocl.get_expression(args[1],args[0]);
        } else{
            cout<<"Not ready to generate!\n";
            out.close();
            exit(0);
        }
        out<<expression<<'\n';
        if(!silent){ cout<<"Expression "<<nb+1<<" : "<<expression<<'\n'; }
        expression.clear();
    }
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
    {1, 16, 17, 18, 19, 20, 21, M, M, M, M, M, M, M, M, M, M},
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

void POCL::init_PROB(){
    unsigned ord_index=0, tmp=0;
    for(unsigned i=0;i<MAX_NB_OPR-1;++i){
        PROB[i][0]=0;
        for(unsigned j=1;j<=MAX_NB_RORD;++j){
            ord_index=Operation::get_order(i,j-1);
            if(ord_index==M || ord_index==M-1){
                PROB[i][j]=-1;    
                break;
            }
            for(unsigned k=0;k<1;++k){ tmp+=prob[ord_index]; }
            PROB[i][j]=tmp;
        }   tmp=0;
    }
}

unsigned POCL::get_rand_opr_index(unsigned opr_index, bool is_fail){
    static unsigned fail_counter=0;
    if(is_fail){ ++fail_counter; }
    if(fail_counter==3){ fail_counter=0; return 1; }
    int r=rand()%OFFSET[opr_index];
    for(unsigned i=0;i<22;++i){
        if(PROB[opr_index][i]<=r && r<PROB[opr_index][i+1]){
            return i;
        }
    }
}

string POCL::get_expression(unsigned max_length, unsigned level){
    unsigned index=22, size=0;
    for(unsigned i=0;i<MAX_NB_OPR-1;++i){
        OFFSET[i]=-1;
        for(unsigned j=0;j<17;++j){
            if(PROB[i][j]==-1){ break; }
            OFFSET[i]=PROB[i][j];
        }
    }
    if(!expression.empty()){ expression.clear(); }    
    unsigned beg; int op=0;
    switch(level){
        case 0:{
            beg=rand()%3;
            if(beg==0){ expression+="-"; size=1;  index=21; }
            else if(beg==1){ expression+="+"; size=1; index=20; }
            else if(beg==2){ expression+=to_string(rand()%9+1); size=1; }
        }   break;
        case 1:{
            beg=rand()%12;
            if(beg<2){ expression+="-"; size=1; index=21; }
            else if(beg<4){ expression+="+"; size=1; index=20; }
            else if(beg<6){ expression+=to_string(rand()%9+1); size=1; index=22; }
            else if(beg<12){
                beg=rand()%14;
                if(beg==1){ beg=14; }
                else if(beg==0){ ++op; }
                expression+=Operation::get_name(beg);
                size=(beg==0)? 1 : (beg==2? 3 : 6 );
                index=beg;
            }
        }   break;
        case 2:{
            beg=rand()%17;
            if(beg<2){ expression+="-"; size=1; index=21; }
            else if(beg<4){ expression+="+"; size=1; index=20; }
            else if(beg<5){ expression+=to_string(rand()%9+1); size=1; index=22; }
            else if(beg<17){
                beg=rand()%14;
                if(beg==1){ beg=14; }
                else if(beg==0){ ++op; }
                expression+=Operation::get_name(beg);
                size=(beg==0)? 1 : (beg==2? 3 : 6 );
                index=beg;
            }
        }
    }
    
    unsigned index1=0, i=0; bool is_fail=false;
    while(size<max_length){
        index1=get_rand_opr_index(index,is_fail);
        i=Operation::get_order(index,index1);
        if(i==1 && op==0){ is_fail=true; continue; }
        is_fail=false;
        index=i;
        if(index==22){ i=rand()%9+1; expression+=to_string(i); }
        else{
            if(index==0){ ++op; }
            else if(index==1){ --op; }
            expression+=Operation::get_name(index);
        }
        size+=Operation::jump_length(index);
    }
    size=expression.size();
    if(expression[size-1]!=')' && expression[size-1]!='!' && !isdigit(expression[size-1])){
        expression+=to_string((rand()%9+1));
        if(expression[size-1]=='('){ expression+=")"; --op; }
    }
    for(int i=0;i<op;++i){ expression+=")"; }
    return expression;
}

void POCL::print_prob(){
    for(unsigned i=0;i<MAX_NB_OPR-1;++i){
        cout<<this->prob[i]<<'\n';
    }
}

void POCL::print_PROB(){
    for(unsigned i=0;i<MAX_NB_OPR-1;++i){
        for(unsigned j=0;j<17;++j){
            if(this->PROB[i][j]==-1){ break; }
            cout<<this->PROB[i][j]<<" ";
        }   cout<<'\n';
    }
}
