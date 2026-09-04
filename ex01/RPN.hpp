#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <stdlib.h>

class RPN
{
    private:
        std::stack<int> _nums;
    public:
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

        int pars(std::string &expression);
        int calculate(char token);
};

#endif