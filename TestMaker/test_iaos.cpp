#include<iostream>
#include<fstream>
#include<cmath>
#include<string>

using namespace std;

#define epsilon 0.000001
#define FILENAME "test_iaos.csv"

template<typename T>
void Cin(const string message, T& t, unsigned i=0){
    cout<<message<<"["<<i<<"] : ";
    cin>>t;
}

// ./test -m nb_v a0 a1 ... an => y(x[1],...,x[nb_v])
int main(int argc, char** argv){

    double *x=nullptr, *dif=nullptr, y=0;
    unsigned *nb_x=0, *P=0, mult_v=1;
    string str=argv[1];
    //checking and allocating memory for essentials
    if(str.compare("-m")==0){
        mult_v=atof(argv[2]);
        cout<<"Mult_V : "<<mult_v<<'\n';
    }
    str.clear();
    x=new double[mult_v];
    dif=new double[mult_v];
    nb_x=new unsigned[mult_v];
    P=new unsigned[mult_v];
    //collects all necessary details to execute the process
    for(unsigned i=0;i<mult_v;++i){
        if(mult_v>1){
            Cin<unsigned>("The biggest power of x",P[i],i);
        }
        else{ P[0]=argc-2; }
        Cin<double>("Initial x",x[i],i);
        Cin<double>("Difference ",dif[i],i);
        Cin<unsigned>("Number of inputs ",nb_x[i],i);
    }
    //ready to process
    unsigned k[2]={0,0}, z[2]={1,1}, *C=new unsigned[mult_v];
    unsigned jump=0, *Nb_x=new unsigned[mult_v], perm=1;
    for(unsigned i=0;i<mult_v;++i){ C[i]=0; Nb_x[i]=1; }
    double tmp=1;
    //ready to open a file
    ofstream iaos_file;
    iaos_file.open(FILENAME);
    //core part of the processing - computing the value of y
    ITERATOR:
    for(;C[mult_v-1]<=P[mult_v-1];++C[mult_v-1]){
        for(unsigned j=0;j<mult_v;++j){
            tmp*=pow(x[j],C[j]);
            if(perm){ str+="x["+to_string(j)+"]^"+to_string(C[j]); }
        }
        if(perm){ str+="*("+to_string(atof(argv[argc-1-jump]))+")+"; }
        y+=(atof(argv[argc-1-jump])*tmp); tmp=1; ++jump;
    }
    if(mult_v-z[0]<1){ goto WRITER; }
    HANDLER:
    if(C[mult_v-1-z[0]]<P[mult_v-1-z[0]]){
        ++C[mult_v-1-z[0]]; C[mult_v-1]=0;
        if(k){ z[0]-=k[0]; k[0]=0; }
        goto ITERATOR;
    }
    else{
        C[mult_v-1-z[0]]=0; k[0]=z[0]; ++z[0];
        if(z[0]<mult_v){ goto HANDLER; }
    }
    //writing to the file
    WRITER:
    k[0]=0; z[0]=1; for(unsigned i=0;i<mult_v;++i){ C[i]=0; }
    for(unsigned j=0;j<mult_v;++j){
        iaos_file<<x[j]<<" ";
    }
    iaos_file<<y<<"\n"; y=0; jump=0; perm=0;
    //the second core part of the process - having all combinations of x's
    ITERATOR2:
    for(;Nb_x[mult_v-1]<nb_x[mult_v-1];){
        x[mult_v-1]+=dif[mult_v-1];
        ++Nb_x[mult_v-1];
        goto ITERATOR;
    }
    if(mult_v-z[0]<1){ goto EOP; }
    HANDLER2:
    if(Nb_x[mult_v-1-z[1]]<nb_x[mult_v-1-z[1]]){
        ++Nb_x[mult_v-1-z[1]];
        x[mult_v-1-z[1]]+=dif[mult_v-1-z[1]];
        x[mult_v-1]-=(nb_x[mult_v-1]*dif[mult_v-1]);
        Nb_x[mult_v-1]=0;
        if(k[1]){ z[1]-=k[1]; k[1]=0; }
        goto ITERATOR2;
    }
    else{
        Nb_x[mult_v-1-z[1]]=1; k[1]=z[1];
        x[mult_v-1-z[1]]-=((nb_x[mult_v-1-z[1]]-1)*dif[mult_v-1-z[1]]); ++z[1];
        if(z[1]<mult_v){ goto HANDLER2; }
    }
    //end of the process
    EOP:
    str.erase(str.size()-1,-1);
    iaos_file<<str;
    iaos_file.close();

    return 0;
}