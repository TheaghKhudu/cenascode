/*
Exception library to support exception handling and to make the program more dynamic.
Looking forward to use standart exceptions of C++ as well.
Should have various cases and conditions to handle exception in different and efficient ways.
*/

#include<string>

#pragma once

class Exception{
    private:
    std::string message;
    public:
    Exception(std::string err_msg): message(err_msg) {}
    std::string get_error(){ return this->message+"\n"; }
};
