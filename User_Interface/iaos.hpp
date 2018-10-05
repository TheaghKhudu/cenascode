/* /05.10.2018
IaOS library with default mathematical operations.
Contains static operations and static information about them since they are not changable.
High functionality with full of various "smart" functions.
*/

#include"smreader.hpp"

#pragma once

#define MAX_NB_OPR 25
#define M MAX_NB_OPR
#define MAX_NB_RORD 19

#define SOLVE_FOR_FUNCTION true
#define SOLVE_FOR_OUPUT false

typedef long double** Matrix;

typedef struct OPERATION{
    private:
    const static std::string name[MAX_NB_OPR];
    const static unsigned priority[MAX_NB_OPR];
    const static unsigned length[MAX_NB_OPR];
    const static unsigned order[MAX_NB_OPR][MAX_NB_RORD];

    public:
    static unsigned get_index(const std::string& opr);
    static unsigned jump_length(unsigned index);
    static unsigned get_priority(unsigned index);
    static unsigned is_opr(const std::string& str, unsigned left);
    static bool is_ordered(unsigned opr_index, unsigned index);
}Operation;

class Calculator{
    private:
    std::string expr;   //holds mathematical expression
    unsigned size;      //holds the size of expr

    public:
    Calculator(){}
    //default constructer if no pre-initialization is needed

    Calculator(const std::string& str): expr(str) , size(str.size()) {}
    //pre-initialization of 'expression' and its size via the constructer

    void set_expr(const std::string& str);
    //post-initialization of 'expression' string and its size

    std::string get_expr() const;
    //returs the 'expr' string for user

    bool MeMeo_test() const;
    //first, tests if the given expression only contains mathematical symbols and numbers
    //second, tests if all terms in the expression are in the right mathematical order
    //finally, gives "true" if passes through first 2 sub-tests succesfully, and "false" otherwise

    long double calculate() const;
    //after getting "true" from MeMeo_test this function treats the expression as a mathematical expression
    //and then calculates the expression, returns the final result of calculation

    void debug_print() const;
    //displays all the variables clearly
};

class IaOS{
    private:
    std::string function;   //holds function
    Matrix io;              //holds iaos as numbers
    unsigned sys;           //holds size of a single system
    Calculator C;           //holds a calculator to be able to calculate any expression

    public:
    IaOS(const Vector<long double>& vector);
    //initializes the IaOS class variables with a const 'vector' Vector<long double> class

    IaOS(const Vector<std::string>& vector);
    //initializes the IaOS class variables with a const 'vector' Vector<std::string> class

    std::string& find_function();
    //returns the appropriate 1D function for 1D 'io' matrix
    //assigns the 'function' string to the found function

    void init_matrix(Matrix matrix);
    //initializes the 'io' matrix with 'matrix' matrix

    void display_matrix() const;
    //displays all the elements of matrix
    //matrix can be either a collection of iaos of a known function
    //or a collection of iaos of an unknown function 

    void display_function() const;
    //displays the current function

    void sbtr_row(unsigned r, unsigned r1);
    //row subtraction in matrix

    void mult_row(unsigned r, long double k);
    //row multiplication in matrix

    void swap_row(unsigned r1, unsigned r2);
    //row swapping in matrix

    void solve_matrix(bool SOLVE_FOR);
    //there are 2 main types of solution: solving for function output and solving for number output

    std::string get_func() const;
    //function getter

    Matrix get_matrix() const;
    //matix getter

    void debug_print() const;
    //shows all the variables clearly
};

#define a true
#define b false

namespace smart_sort{
    template<typename T>void vector_(std::vector<T>& vect, bool sort_for);
    //

    template<typename T>void vector(std::vector<T>& vect);
    //

    template<typename T>void matrix(T matrix, unsigned nb_column, unsigned nb_row=1);
    //
}
