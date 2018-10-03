/*
Smart Reader library to collect the user's input and then checking it.
Handles exceptions, and supports multifunctionality to respond the user in different ways if needed.
Makes easier interface for the user, so that user interaction goes with less effort.
Containing generic class and functions to support user-dependent advanced features.
DD(Declarations+Definitions) specified library.
Easily managable, changable header file. Mostly non-static behaviours to extend functionality.
*/

#include<iostream>
#include<vector>
#include"exception.hpp"

#pragma once

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

    void append();
    //appends new elements in the vector
    //it helps user to insert any missing inputs

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
    T input;
    try{
        std::cout<<"Enter the number of variables : ";
        std::cin>>u_sys;
        if(u_sys<=1){
            throw Exception("The number of variable should be bigger than 2!"); }
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
        }
        this->sys=u_sys;
    INIT:
    try{
        while(true){
            std::cin>>input;
            if(std::cin.eof()){ break; }
            else if(!std::cin.good()){
                std::cin.clear();
                std::cin.ignore(70,'\n');
                throw Exception("Not a number!");
            }
            vect.push_back(input);
            ++size;
        }
    } catch(Exception& exception){
        std::cerr<<exception.get_error();
        std::cin.clear();
        goto INIT;
    }
    SIZE_TEST:
    try{
        if(this->size%this->sys!=0){
            throw Exception("Incomplete IaOS!");
        }
    } catch(Exception& exception){
        std::cerr<<exception.get_error();
        unsigned r_pos, c_pos;
        while(true){
            this->display();
            std::cout<<"1.Insert\n2.Modify\n3.Remove\n4.Exit\n";
            std::cin.clear();
            std::cin>>u_sys;
            if(u_sys==4){ break; }
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
        goto SIZE_TEST;
        
    }
    //size=static_cast<unsigned>(vect.size());
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
    INSERT:
    try{
        while(true){
            std::cout<<"Enter the new input : ";
            std::cin>>input;
            if(std::cin.eof()){ std::cout<<'\n'; break; }
            else if(!std::cin.good()){
                std::cin.clear();
                std::cin.ignore(70,'\n');
                throw Exception("Not a number!");
            }
            else{
                it=vect.insert(it,input)+1;
                ++size;
                this->display();
            }
        }
    } catch(Exception& exception){
        std::cerr<<exception.get_error();
        std::cin.clear();
        goto INSERT;
    }
    std::cin.clear();
}

template<class T>
void Vector<T>::append(){
    T input;
    APPEND:
    try{
        while(std::cin>>input){
            if(!is_number(input)){
                throw Exception("Not a number!");
            }
            vect.push_back(input);
        }
    } catch(Exception& exception){
        std::cerr<<exception.get_error();
        goto APPEND;
    }
}

template<class T>
void Vector<T>::modify(unsigned r_pos, unsigned c_pos){
    T input;
    typename std::vector<T>::iterator it=vect.begin();
    it+=static_cast<int>(r_pos*sys+c_pos);
    std::cin>>input;
    vect.erase(vect.begin()+static_cast<int>(r_pos*sys+c_pos));
    vect.insert(it,input);
}

//static_cast<typename std::vector<T>::iterator>(r_pos*sys+c_pos)
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
