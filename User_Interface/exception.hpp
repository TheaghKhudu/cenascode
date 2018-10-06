/* /02.10.2018
Exception library to support exception handling and to make the program more dynamic.
Looking forward to use standart exceptions of C++ as well.
Should have various cases and conditions to handle exception in different and efficient ways.

V1.1 /05.10.2018
Updated:
    -new function for handling errors in more understandable way
*/

#include<cstring>

#pragma once

class Exception{
    private:
    std::string message;
    public:
    Exception(std::string err_msg): message(err_msg) {}
    Exception(std::string err_msg, int i){ message=err_msg+std::to_string(i); }
    std::string get_error(){ return this->message+"\n"; }
};
