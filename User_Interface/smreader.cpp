#include<iostream>
#include"smreader.hpp"

template<class T>
void Vector<T>::init(){
    int u_sys;
    T input;
    try{
        std::cout<<"Enter the number of variables : ";
        std::cin>>u_sys;
        if(u_sys<=1 || !std::cin.good()){
            throw Exception("The number of variable should be bigger than 2!\n");
        }
        this->sys=u_sys;
    } catch(Exception& exception){
        std::cerr<<exception.get_error();
        std::cin.clear();
    }
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
        goto INIT;
    }
    SIZE_TEST:
    try{
        if(this->size%this->sys!=0){
            throw Exception("Incomplete IaOS!\n");
        }
    } catch(Exception& exception){
        std::cerr<<exception.get_error();
        unsigned r_pos, c_pos;
        while(true){
            this->display();
            std::cout<<"1.Insert\n2.Modify\n3.Remove\n4.Exit\n";
            std::cin.clear();
            std::cin>>u_sys;
            if(!std::cin.good()){ break; }
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
    size=static_cast<unsigned>(vect.size());
}

template<class T>
void Vector<T>::display() const{
    std::cout<<"\n\t";
    for(unsigned i=0;i<sys;++i){
        std::cout<<i<<"\t";
    }
    for(decltype(vect.size()) i=0;i<size;++i){
        std::cout<<i<<" | ";
        for(unsigned j=0;j<sys;++j){
            if(i*sys+j>size){ break; }
            std::cout<<vect[i*sys+j]<<"\t";
        }
        std::cout<<'\n';
    }
}

template<class T>
void Vector<T>::insert(unsigned r_pos, unsigned c_pos){
    T input;
    INSERT:
    try{
        while(true){
            //std::cin.clear();
            std::cout<<"Enter an input to insert : ";
            std::cin>>input;
            if(std::cin.eof()){ std::cin.clear(); break; }
            else if(!std::cin.good()){
                std::cin.clear();
                throw Exception("Not a number!");
            }
            vect.insert(static_cast<typename std::vector<T>::iterator>(r_pos*sys+c_pos),input);
        }
    } catch(Exception& exception){
        std::cerr<<exception.get_error();
        std::cin.clear();
        goto INSERT;
    }
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
    std::cin>>input;
    vect.erase(vect.beg()+static_cast<typename std::vector<T>::iterator>(r_pos*sys+c_pos));
    vect.insert(static_cast<typename std::vector<T>::iterator>(r_pos*sys+c_pos),input);
}

template<class T>
void Vector<T>::remove(unsigned r_pos, unsigned c_pos){
    typename std::vector<T>::iterator it=vect.begin();
    it+=r_pos*sys+c_pos;
    it=vect.erase(it);
}

template<class T>
void Vector<T>::debug_print() const{
    std::cout<<"_________\n";
    std::cout<<"Debug Print:\n";
    std::cout<<"Sys : "<<sys<<"\n Size : "<<size<<"\n";
}
