/* /05.10.2018
Small transaction unit between the user and data holders to restore the user's input.
Static mathematical operations/functions are used to define basic operations.
Contains calculator which is capable of evaluating the expression.
*/

#include"iaos.hpp"

/* Operation structure initializers and functions */

const std::string Operation::name[MAX_NB_OPR]={
    "(", ")", "log", "arcsinh", "arccosh", "arctanh",
    "arcsin", "arccos", "arctan", "sinh", "cosh", "tanh",
    "sin", "cos", "tan", "^", "!", "%", "*", "/", "+", "-", "1"
};

const unsigned Operation::priority[MAX_NB_OPR]={
    6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 4, 3, 3, 2, 2, 1, 1, 0
};

const unsigned Operation::length[MAX_NB_OPR]={
    1, 1, 3, 7, 7, 7, 6, 6, 6, 4, 4, 
    4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1
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
    {1, 15, 16, 17, 18, 19, 20, 21, 22, M, M, M, M, M, M, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {1, 15, 16, 17, 18, 19, 20, 21, 22, M, M, M, M, M, M, M, M}
};

unsigned Operation::get_index(const std::string& opr){
    unsigned index=0;
    for(;index<MAX_NB_OPR-1;++index){
        if(opr.compare(name[index])==0){ return index; }
    }
    if(std::isdigit(opr[0])){ return 22; }
    return MAX_NB_OPR;
}

unsigned Operation::jump_length(unsigned index){
    return length[index];
}

unsigned Operation::get_priority(unsigned index){
    return priority[index];
}

unsigned Operation::is_opr(const std::string& str, unsigned left){
    unsigned length=0;
    for(unsigned it=0;it<MAX_NB_OPR-1;++it){
        length=jump_length(get_index(name[it]));
        if(left<length){ continue; }
        if(str.compare(0,length,name[it])==0){ return length; }
    }
    if(std::isdigit(str[0])){ return 1; }
    return 0;
}

bool Operation::is_ordered(unsigned opr_index, unsigned index){
    for(unsigned i=0;i<MAX_NB_RORD;++i){
        if(order[opr_index][i]==MAX_NB_OPR){ break; }
        if(order[opr_index][i]==index){ return true; }
    }
    return false;
}

/* Calculator functions */

void Calculator::set_expr(const std::string& str){
    expr=str;   size=expr.size();
}

std::string Calculator::get_expr() const{
    return expr;
}

bool Calculator::MeMeo_test() const{
    std::cout<<"MeMeo activated.\n";
    unsigned length=Operation::is_opr(expr,size), opr_index=0, index=0;
    unsigned counter=0;
    //std::cout<<"length : "<<length<<'\n';
    if(length==0){ return false; }
    for(unsigned it=0;it<size;){
        if(it==0 && (expr[0]==')' || expr[0]=='^' || expr[0]=='!' || expr[0]=='%' || expr[0]=='*' || expr[0]=='/')){ return false; }
        if(it==0 && (expr[size-1]!=')' && !std::isdigit(expr[size-1]))){ return false; }
        opr_index=Operation::get_index(expr.substr(it,length));
        //std::cout<<"opr index - "<<opr_index<<" : "<<expr.substr(it,length)<<'\n';
        it+=length;
        if(opr_index==0){ ++counter; } else if(opr_index==1){ --counter; }
        if(it>=size){ if(counter!=0){ return false; } break; }
        //std::cout<<"it : "<<it<<'\n';
        if(!(length=Operation::is_opr(&expr[it],size-it))){ return false; }
        //std::cout<<"new length for index : "<<length<<'\n';
        index=Operation::get_index(expr.substr(it,length));
        //std::cout<<"index - "<<index<<" : "<<expr.substr(it,length)<<'\n';
        if(!Operation::is_ordered(opr_index,index)){ /*std::cout<<"Ooops : "<<opr_index<<" - "<<index<<"\n";*/ return false; }
    }
    return true;
}

long double Calculator::calculate() const{
    //incompleted
}

void Calculator::debug_print() const{
    std::cout<<"_________\n";
    std::cout<<"Debug Print:\n";
    std::cout<<"Expression : "<<expr<<'\n';
    std::cout<<"Size : "<<size<<'\n';
}

/* IaOS functions */

IaOS::IaOS(const Vector<long double>* vector){
    io=vector->get_vect();
    sys=vector->get_sys();
    size=vector->get_size();
}

IaOS::IaOS(std::fstream& file, bool OPTION){
    long double elem;
    unsigned sys=0;
    char tmp='0';
    if(OPTION==READ){
        while(file>>elem){
            if(tmp!='\n'){ file.get(tmp); ++sys; }
            io->push_back(elem);
        }
        size=io->size();
        this->sys=sys;
    } else{
        file<<function<<'\n';
    }
}

std::string& IaOS::find_function() const{
    //incompleted
}

void IaOS::init_matrix(Matrix vector){
    //incompleted
}

void IaOS::display_matrix() const{
    for(unsigned r=0;r<size/sys;++r){
        for(unsigned c=0;c<sys;++c){
            std::cout<<(*io)[r*sys+c]<<" ";
        }
        std::cout<<'\n';
    }
}

void IaOS::display_function() const{
    for(auto it=function.begin();it<function.end();++it){
        std::cout<<*it;
    }   std::cout<<'\n';
}

void IaOS::sbtr_row(unsigned r, unsigned r1){
    for(unsigned c=0;c<sys;++c){
        (*io)[r*sys+c]-=(*io)[r1*sys+c];
    }
}

void IaOS::mult_row(unsigned r, long double k){
    for(unsigned c=0;c<sys;++c){
        (*io)[r*sys+c]*=k;
    }
}

void IaOS::swap_row(unsigned r1, unsigned r2){
    for(unsigned c=0;c<sys;++c){
        long double tmp=(*io)[r1*sys+c];
        (*io)[r1*sys+c]=(*io)[r2*sys+c];
        (*io)[r2*sys+c]=tmp;
    }
}

void IaOS::sort() const{
    //incompleted
}

bool IaOS::check_d() const{
    //incompleted
}

long double IaOS::check_D() const{
    //incompleted
}

void IaOS::solve_matrix(bool SOLVE_FOR){
    //incompleted
}

std::string IaOS::get_func() const{
    return function;
}

Matrix IaOS::get_matrix() const{
    return io;
}

IaOS::~IaOS(){
    delete io;
}

void IaOS::debug_print() const{
    std::cout<<"_________\n";
    std::cout<<"Debug Print:\n";
    std::cout<<"Function : "<<function<<'\n';
    std::cout<<"Size : "<<size<<'\n';
    std::cout<<"Sys : "<<sys<<'\n';
    std::cout<<"Matrix : \n"; display_matrix();
}
