/* /05.10.2018
Small transaction unit between the user and data holders to restore the user's input.
Static mathematical operations/functions are used to define basic operations.
Contains calculator which is capable of evaluating the expression.
Upgraded with lots of new high functionalities which helps to solve complex problems.

V1.1 /09.10.2018
Updated:
    -better interaction with float numbers
    -bugs fixed
*/

#include<cstdlib>
#include"iaos.hpp"

/* Operation and Expression_List structure initializers and functions */

const std::string Operation::name[MAX_NB_OPR]={
    "(", ")", "log", "arcsinh", "arccosh", "arctanh",
    "arcsin", "arccos", "arctan", "sinh", "cosh", "tanh",
    "sin", "cos", "tan", "^", "!", "%", "*", "/", "+", "-", "1", "."
};

const unsigned Operation::priority[MAX_NB_OPR]={
    6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 4, 3, 3, 2, 2, 1, 1, 0, 0
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

unsigned Operation::get_index(const std::string& opr){
    unsigned index=0;
    for(;index<MAX_NB_OPR-1;++index){
        if(opr.compare(name[index])==0){ return index; }
    }
    if(std::isdigit(opr[0])){ return 22; }
    else if(opr[0]=='.'){ return 23; }
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
    if(std::isdigit(str[0]) || str.compare(0,length,".")==0){ return 1; }
    return 0;
}

bool Operation::is_ordered(unsigned opr_index, unsigned index){
    for(unsigned i=0;i<MAX_NB_RORD;++i){
        if(order[opr_index][i]==MAX_NB_OPR){ break; }
        if(order[opr_index][i]==index){ return true; }
    }
    return false;
}

Expression_List* Expression_List::create_node(){
    Expression_List* node=new Expression_List;
    node->value=0;
    node->index=0;
    node->position=0;
    node->next=nullptr;
    return node;
}

int Expression_List::search_position(unsigned priority, unsigned beg_pos){
    Expression_List* tmp=this;
    for(unsigned i=0;i<beg_pos;++i){ tmp=tmp->next; }
    for(tmp;tmp->get_priority()!=priority;tmp=tmp->next){
        if(tmp->next==nullptr || tmp->next->index==1){ return -1; }
    }
    return tmp->position;
}

unsigned* Expression_List::split(unsigned opr_index, unsigned opr_pos){
    unsigned* beg_end=new unsigned[2];
    if(opr_index==0){
        beg_end[0]=opr_pos;
        beg_end[1]=cp_pos(opr_pos);
    } else if(opr_index==Operation::get_index("!")){
        beg_end[0]=opr_pos-1;
        beg_end[1]=opr_pos;
    } else if(opr_index==Operation::get_index("^") ||
              opr_index==Operation::get_index("%") ||
              opr_index==Operation::get_index("*") ||
              opr_index==Operation::get_index("/") ||
              opr_index==Operation::get_index("+") ||
              opr_index==Operation::get_index("-")){
        beg_end[0]=opr_pos-1;
        beg_end[1]=opr_pos+1;
    } else{
        beg_end[0]=opr_pos;
        beg_end[1]=opr_pos+1;
    }
    return beg_end;
}

unsigned Expression_List::cp_pos(unsigned op_pos){
    Expression_List* node=this;
    for(unsigned i=0;i<=op_pos;++i){ node=node->next; }
    unsigned counter=1;
    for(;node->next!=nullptr;node=node->next){
        if(node->index==0){ ++counter; }
        else if(node->index==1){ --counter; }
        if(counter==0){ return node->position; }
    }
    //return node->position;
}

void Expression_List::set_list(long double value, unsigned position, unsigned priority, unsigned index, EXPRESSION_LIST* next){
    this->value=value;  this->position=position; this->priority=priority;   this->index=index; this->next=next;
}

long double Expression_List::get_value(){ return this->value; }

unsigned Expression_List::get_index(){ return this->index; }

unsigned Expression_List::get_position(){ return this->position; }

unsigned Expression_List::get_priority(){ return this->priority; }

Expression_List* Expression_List::get_next(){ return this->next; }

void Expression_List::delete_list(EXPRESSION_LIST* beg, EXPRESSION_LIST* end){
    Expression_List* tmp=beg;

    if(tmp!=nullptr){ for(beg;beg!=end;beg=beg->next){ tmp=beg; delete tmp; } }

    /*
        tmp=beg
        beg=beg->next
        free(tmp);
    */
}

void Expression_List::debug_print(){
    std::cout<<"_________\n";
    std::cout<<"Debug Print of List :\n";
    std::cout<<"Value : "<<this->value<<'\n';
    std::cout<<"Position : "<<this->position<<'\n';
    std::cout<<"Index : "<<this->index<<'\n';
    std::cout<<"Priority : "<<this->priority<<'\n';
}

void Expression_List::manage_list(long double value, unsigned beg_pos, unsigned end_pos){
    Expression_List* beg=this;
    Expression_List* end=this;
    for(unsigned i=0;i<beg_pos;++i){ beg=beg->next; end=end->next; }
    for(unsigned i=beg_pos;i<=end_pos;++i){ end=end->next; }
    Expression_List::delete_list(beg->next,end);
    beg->set_list(value,beg_pos,0,22,end);
    for(unsigned diff=end_pos-beg_pos;end!=nullptr;end=end->next){
        end->position-=diff;
    }
}

/* Math namespace functions */

long double Math::add_(long double a, long double b){ return a+b; }

long double Math::sbtr_(long double a, long double b){ return a-b; }

long double Math::mult_(long double a, long double b){ return a*b; }

long double Math::div_(long double a, long double b){
    if(b==0){ throw Exception("Dividing by 0!"); }
    return a/b;
}

long double Math::pow_(long double a, long double p){
    if(a<0){ throw Exception("Power error!"); }
    return pow(a,p);
}

long double Math::fact_(long double a, long double b){
    if(a<0){ throw Exception("Minus factorial!"); }
    int ia=static_cast<int>(a);
    for(unsigned i=ia-1;i>0;--i){ ia*=i; }
    return ia;
}

long double Math::pctn_(long double a, long double b){ return a*b/100; }

long double Math::log_(long double a, long double b){
    if(a<0){ throw Exception("Log error!"); }
    return log10(a);
}

long double Math::sin_(long double a, long double b){ return sin(a); }

long double Math::cos_(long double a, long double b){ return cos(a); }

long double Math::tan_(long double a, long double b){ return tan(a); }

long double Math::sinh_(long double a, long double b){ return sinh(a); }

long double Math::cosh_(long double a, long double b){ return cosh(a); }

long double Math::tanh_(long double a, long double b){ return tanh(a); }

long double Math::arcsin_(long double a, long double b){
    if(a<-1 || a>1){ throw Exception("Arcsin error!"); }
    return asin(a);
}

long double Math::arccos_(long double a, long double b){
    if(a<-1 || a>1){ throw Exception("Arccos error!"); }
    return acos(a);
}

long double Math::arctan_(long double a, long double b){ return atan(a); }

long double Math::arcsinh_(long double a, long double b){ return asinh(a); }

long double Math::arccosh_(long double a, long double b){ return acosh(a); }

long double Math::arctanh_(long double a, long double b){ return atanh(a); }

std::function<long double(long double, long double)> operation_[20]={
    &Math::log_, &Math::arcsinh_, &Math::arccosh_, &Math::arctanh_, &Math::arcsin_, 
    &Math::arccos_, &Math::arctan_, &Math::sinh_, &Math::cosh_, &Math::tanh_, 
    &Math::sin_, &Math::cos_, &Math::tan_, &Math::pow_, &Math::fact_, &Math::pctn_, 
    &Math::mult_, &Math::div_, &Math::add_, &Math::sbtr_
};

/* Calculator functions */

void Calculator::set_expr(const std::string& str){
    expr=str;   size=expr.size();
}

void Calculator::init_list(const std::string& expr){
    Expression_List* list=this->get_list();
    unsigned size=expr.size();
    unsigned index=0, length=0, position=0, priority=0;
    long double value=0;
    bool pass=true;
    for(unsigned it=0;it<size;){
        length=Operation::is_opr(&expr[it],size-it);
        index=Operation::get_index(expr.substr(it,length));
        priority=Operation::get_priority(index);
        if(index==22 && pass){
            value=atof(&expr[it]);
            list->set_list(value,position,priority,index,Expression_List::create_node());
            list=list->get_next();
            pass=false;
            ++position;
        } else if(index!=22 && index!=23){
            list->set_list(index,position,priority,index,Expression_List::create_node());
            list=list->get_next();
            pass=true;
            ++position;
            it+=(length-1);
        }
        ++it;
        if(it>=size){ delete list; }
    }
}

Expression_List* Calculator::get_list(){ return &list; }

std::string Calculator::get_expr() const{ return expr; }

bool Calculator::MeMeo_test() const{
    unsigned length=Operation::is_opr(expr,size), opr_index=0, index=0;
    unsigned counter=0;
    if(length==0){ return false; }
    for(unsigned it=0;it<size;){
        if(it==0 && 
          (expr[0]==')' || expr[0]=='^' || expr[0]=='!' || 
           expr[0]=='%' || expr[0]=='*' || expr[0]=='/' ||
           (expr[size-1]!=')' && expr[size-1]!='!' && !std::isdigit(expr[size-1])))){ return false; }
        opr_index=Operation::get_index(expr.substr(it,length));
        it+=length;
        if(opr_index==0){ ++counter; } else if(opr_index==1){ --counter; }
        if(it>=size){ if(counter!=0){ return false; } break; }
        if(!(length=Operation::is_opr(&expr[it],size-it))){ return false; }
        index=Operation::get_index(expr.substr(it,length));
        if(!Operation::is_ordered(opr_index,index)){ return false; }
    }
    return true;
}

long double Calculator::calculate(){
    this->init_list(expr);
    this->get_soe(0);
    return this->list.get_value();
}

long double Calculator::single_opr_calc(unsigned* pos, unsigned opr_pos){
    Expression_List* node=this->get_list();
    long double a, b=0;
    unsigned opr_index=0;
    if(opr_pos==pos[0]){
        for(;node->get_position()!=opr_pos;node=node->get_next());
        a=node->get_next()->get_value();
        opr_index=node->get_index();
        if(opr_index==0){ return a; }
        return operation_[opr_index-2](a,0);
    } else if(opr_pos>pos[0] && pos[1]!=0){
        for(;node->get_position()!=pos[0];node=node->get_next());
        a=node->get_value();    node=node->get_next();
        opr_index=node->get_index();    node=node->get_next();
        b=node->get_value();
        //std::cout<<"a : "<<a<<", b : "<<b<<", opr_index : "<<opr_index<<'\n';
        return operation_[opr_index-2](a,b);
    } else{
        for(;node->get_position()!=pos[0];node=node->get_next());
        a=node->get_value();
        opr_index=node->get_next()->get_index();
        return operation_[opr_index](a,0);
    }
}

void Calculator::get_soe(unsigned beg_pos){
    Expression_List* List=this->get_list();
    Expression_List* node=List;
    unsigned beg=0, *beg_end=&beg/*new unsigned[2]{0,0}*/, opr_index=0, pr=6;
    int pos=0;    bool pass=false;    long double elem=0;
    beg_end[0]=0;
    while(pr!=0){
        elem=0;
        for(pr=6;pr>0;--pr){
            if((pos=List->search_position(pr,beg_end[0]))==-1){ continue; }
            node=List;
            for(int i=0;i<pos;++i){ node=node->get_next(); }
            beg_end=List->split(node->get_index(),pos);
            if(beg_end[1]-beg_end[0]<=2){
                elem=single_opr_calc(beg_end,pos);
                List->manage_list(elem,beg_end[0],beg_end[1]);
                beg_end[0]=0;
                ++pr; if(pass){ pr=7; } pass=false;
            } else{
                pass=true;
                beg_end[0]++; break;
            }
        }
    }
}

void Calculator::debug_print() const{
    std::cout<<"_________\n";
    std::cout<<"Debug Print of Calculator :\n";
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
    std::cout<<"Debug Print of IaOS :\n";
    std::cout<<"Function : "<<function<<'\n';
    std::cout<<"Size : "<<size<<'\n';
    std::cout<<"Sys : "<<sys<<'\n';
    std::cout<<"Matrix : \n"; display_matrix();
}
