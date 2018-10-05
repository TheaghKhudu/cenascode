/*
Smart Reader library to collect the user's input and then checking it.
Handles exceptions, and supports multifunctionality to respond the user in different ways if needed.
Makes easier interface for the user, so that user interaction goes with less effort.
Containing generic class and functions to support user-dependent advanced features.
DD(Declarations+Definitions) specified library.
Easily managable, changable header file. Mostly non-static behaviours to extend functionality.

V1.1 /04.10.2018
Updated:
    -goto statement reduction
    -more of exception handling, thus safe codes
    -useless function(s) elimination
    -general code reduction
    -much better dynamic user interface

V1.2 /05.10.2018
Updated:
    -new functionality to ease the transaction and processing
    -less bugs
    -more exception handling
    -better user interface(with a newly added option)
*/

#include<iostream>
#include<vector>
#include"exception.hpp"

#pragma once

#define BUFF_SIZE 70

template<class T>
class Vector{
    private:
    mutable std::vector<T> vect;    //holds iaos
    mutable unsigned size;          //holds size of iaos
    unsigned sys;                   //holds size of single system
    
    public:
    void init();
    //initializes all the private variables
    //interacts with the user directly

    void display() const;
    //displays the current vector in a 2D plane, so that the user can see his iaos more clearly

    void insert(unsigned r_pos, unsigned c_pos) const;
    //inserts new elements in the position of (r_pos,c_pos) in 2D displayed iaos
    //it helps user to insert any missed inputs

    void modify(unsigned r_pos, unsigned c_pos) const;
    //modifies the shown element by reinitializing it

    void remove(unsigned r_pos, unsigned c_pos) const;
    //removes element(s) in case user have entered wrong input(s)

    unsigned is_ready() const;
    //checks if the given system does not contain any wrong(or i-repetitive) sub-system
    //it gives true, if it does not contain such sub-system, and false, otherwise

    void debug_print() const;
    //displays all elements on the purpose of testing and debugging
};

template<class T>
void Vector<T>::init(){
    int u_sys;
    unsigned r_pos, c_pos;
    T input;
    while(true){
        try{
            std::cout<<"Enter the number of variables : ";
            std::cin>>u_sys;
            if(!std::cin.good()){
                if(!std::cin.eof()){ std::cin.clear(); std::cin.ignore(BUFF_SIZE,'\n'); }
                std::cin.clear();
                throw Exception("The number of variables should be a positive integer bigger than 2!");
            } else if(u_sys<=1){
                throw Exception("The number of variables should be bigger than 2!");
            }
            this->sys=u_sys;
            break;
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
        }
    }
    while(true){
        try{
            std::cout<<"Enter an input : ";
            std::cin>>input;
            if(std::cin.eof()){ break; }
            else if(!std::cin.good()){
                std::cin.clear();
                std::cin.ignore(BUFF_SIZE,'\n');
                throw Exception("Not a number!");
            }
            vect.push_back(input);
            ++size;
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
        }
    }   std::cout<<'\n';    u_sys=0;
    while(true){
        try{
            if(this->size%this->sys!=0 || this->size==0){
                throw Exception("Incomplete IaOS!");
            } else if(is_ready()!=1){
                throw Exception("Repetitive input occured! - in line ",is_ready()-size);
            } else if(u_sys==4){
                break;
            } else{
                throw Exception("Press 4 to submit.");
            }
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
            this->display();
            std::cout<<"1.Insert\n2.Modify\n3.Remove\n4.Done\n5.Exit\n";
            std::cin.clear();
            std::cin>>u_sys;
            if(!std::cin.good()){ u_sys=6; std::cin.clear(); std::cin.ignore(BUFF_SIZE,'\n'); }
            switch(u_sys){
                case 1:
                    while(std::cout<<"Enter a position : ", std::cin>>r_pos>>c_pos){
                        this->insert(r_pos,c_pos);
                    }
                    break;
                case 2:
                    while(std::cout<<"Enter a position : ", std::cin>>r_pos>>c_pos){
                        this->modify(r_pos,c_pos);
                    }
                    break;
                case 3:
                    while(std::cout<<"Enter a position : ", std::cin>>r_pos>>c_pos){
                        this->remove(r_pos,c_pos);
                    }
                    break;
                case 4:
                    break;
                case 5:
                    exit(0);
                default:
                    std::cerr<<"Option does not exist!\n";
                break;
            }
        }
    }
}

template<class T>
void Vector<T>::display() const{
    std::cout<<"   ";
    for(unsigned i=0;i<sys;++i){
        std::cout<<"\\"<<i<<"/\t";
    }   std::cout<<'\n';
    for(unsigned i=0;i<size;++i){
        std::cout<<i<<" | ";
        for(unsigned j=0;j<sys;++j){
            std::cout<<vect[i*sys+j]<<"\t";
            if(i*sys+j>=size-1){ i=size; break; }
        }
        std::cout<<'\n';
    }
}

template<class T>
void Vector<T>::insert(unsigned r_pos, unsigned c_pos) const{
    T input;
    typename std::vector<T>::iterator it=vect.begin()+r_pos*sys+c_pos;
    while(true){
        try{
            std::cout<<"Enter the new input : ";
            std::cin>>input;
            if(std::cin.eof()){ std::cout<<'\n'; break; }
            else if(!std::cin.good()){
                std::cin.clear();
                std::cin.ignore(BUFF_SIZE,'\n');
                throw Exception("Not a number!");
            }
            else{
                it=vect.insert(it,input)+1;
                ++size;
                this->display();
            }
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
        }
    }   std::cin.clear();
}

template<class T>
void Vector<T>::modify(unsigned r_pos, unsigned c_pos) const{
    T input;
    typename std::vector<T>::iterator it=vect.begin();
    it+=static_cast<int>(r_pos*sys+c_pos);
    std::cout<<"Enter a new input : ";
    std::cin>>input;
    it=vect.erase(it);
    it=vect.insert(it,input);
}

template<class T>
void Vector<T>::remove(unsigned r_pos, unsigned c_pos) const{
    typename std::vector<T>::iterator it=vect.begin();
    it+=static_cast<int>(r_pos*sys+c_pos);
    it=vect.erase(it);
    --size;
}

template<typename T>
unsigned Vector<T>::is_ready() const{
    unsigned counter=0;
    for(unsigned it=0;it<size/sys-1;++it){
        for(unsigned i=it+1;i<size/sys;++i){
            for(unsigned s=0;s<sys-1;++s){
                if(vect[it*sys+s]==vect[i*sys+s]){ ++counter; }
            }
        if(counter==sys-1){ return size+it; }
        counter=0;
        }
    }
    return 1;
}

template<class T>
void Vector<T>::debug_print() const{
    std::cout<<"_________\n";
    std::cout<<"Debug Print:\n";
    std::cout<<"Sys : "<<sys<<"\n Size : "<<size<<"\n";
    std::cout<<"Vector : \n";
    display();
}
