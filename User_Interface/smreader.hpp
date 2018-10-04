/*
Smart Reader library to collect the user's input and then checking it.
Handles exceptions, and supports multifunctionality to respond the user in different ways if needed.
Makes easier interface for the user, so that user interaction goes with less effort.
Containing generic class and functions to support user-dependent advanced features.
DD(Declarations+Definitions) specified library.
Easily managable, changable header file. Mostly non-static behaviours to extend functionality.

V1.1
Updated:
    -goto statement reduction
    -more of exception handling, thus safe codes
    -useless function(s) elimination
    -general code reduction
    -much better dynamic user interface
*/

#include<iostream>
#include<vector>
#include"exception.hpp"

#pragma once

#define BUFF_SIZE 70

template<class T>
class Vector{
    private:
    std::vector<T> vect;    //holds iaos
    unsigned size;          //holds size of iaos
    unsigned sys;           //holds size of single system
    
    public:
    void init();
    //initializes all the private variables
    //interacts with the user directly

    void display() const;
    //displays the current vector in a 2D plane, so that the user can see his iaos more clearly

    void insert(unsigned r_pos, unsigned c_pos);
    //inserts new elements in the position of (r_pos,c_pos) in 2D displayed iaos
    //it helps user to insert any missed inputs

    void modify(unsigned r_pos, unsigned c_pos);
    //modifies the shown element by reinitializing it

    void remove(unsigned r_pos, unsigned c_pos);
    //removes element(s) in case user have entered wrong input(s)

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
            if(!std::cin.good() || std::cin.eof()){
                std::cin.clear();
                std::cin.ignore(BUFF_SIZE,'\n');
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
            if(this->size%this->sys!=0){
                throw Exception("Incomplete IaOS!");
            } else if(u_sys==4){
                break;
            } else{
                throw Exception("Press 4 to exit.");
            }
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
            this->display();
            std::cout<<"1.Insert\n2.Modify\n3.Remove\n4.Exit\n";
            std::cin.clear();
            std::cin>>u_sys;
            switch(u_sys){
                case 1:
                    while(std::cin>>r_pos>>c_pos){
                        this->insert(r_pos,c_pos);
                    }
                    break;
                case 2:
                    while(std::cin>>r_pos>>c_pos){
                        this->modify(r_pos,c_pos);
                    }
                    break;
                case 3:
                    while(std::cin>>r_pos>>c_pos){
                        this->remove(r_pos,c_pos);
                    }
                    break;
                case 4:
                    break;
                default:
                    std::cerr<<"Non existing option!";
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
void Vector<T>::insert(unsigned r_pos, unsigned c_pos){
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
void Vector<T>::modify(unsigned r_pos, unsigned c_pos){
    T input;
    typename std::vector<T>::iterator it=vect.begin();
    it+=static_cast<int>(r_pos*sys+c_pos);
    std::cin>>input;
    it=vect.erase(it);
    it=vect.insert(it,input);
}

template<class T>
void Vector<T>::remove(unsigned r_pos, unsigned c_pos){
    typename std::vector<T>::iterator it=vect.begin();
    it+=static_cast<int>(r_pos*sys+c_pos);
    it=vect.erase(it);
    --size;
}

template<class T>
void Vector<T>::debug_print() const{
    std::cout<<"_________\n";
    std::cout<<"Debug Print:\n";
    std::cout<<"Sys : "<<sys<<"\n Size : "<<size<<"\n";
}
