#include "RPN.hpp"

RPN::RPN()
{

}
RPN::RPN(const RPN& other)
{
    _nums = other._nums;
}
RPN& RPN::operator=(const RPN& other)
{
    _nums = other._nums;
    return (*this);
}

RPN::~RPN()
{

}

int RPN::pars(std::string &expression)
{
    std::istringstream iss(expression);
    std::string token = "";
    size_t count = 0;
    size_t counti = 0;

    while (iss >> token)
    {
        if (token.size() == 1 && isdigit(token[0]))
        {
            int numb;
            numb = std::atoi(std::string(1,token[0]).c_str());
            _nums.push(numb);
            counti++;
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (_nums.size() < 2)
            {
                std::cout << "ERROR wrong input" << std::endl;
                return (1);
            }
            if (calculate(token[0]))
            {
                std::cout << "ERROR / 0 is not possible" << std::endl;
                return (1);
            }
            count++;
        }
        else
        {
            std::cout << "ERROR wrong input" << std::endl;
            return (1);
        }
    }
    if (counti -1 != count)
    {
        std::cout << "ERROR wrong input" << std::endl;
        return (1);
    }
    std::cout << "Resut: " << _nums.top() << std::endl;
    return (0);
}

int RPN::calculate(char token)
{
    /*
    std::cout << "NUMS:" << std::endl;
    while (!_nums.empty())
    {
        std::cout << _nums.top() << std::endl;
        _nums.pop();
    }
    std::cout << "OPERATORS:" << std::endl;
    for (size_t p = 0; p < _oper.size(); p++)
        std::cout << _oper[p] << std::endl;*/

    int num1 = _nums.top();
    _nums.pop();
    int num2 = _nums.top();
    _nums.pop();
    if (token == '+')
        _nums.push(num2 + num1);
    else if (token == '-')
        _nums.push(num2 - num1);
    else if (token == '/')
    {
        if (num1 == 0)
            return (1);
        _nums.push(num2 / num1);
    }
    else if (token == '*')
        _nums.push(num2 * num1);
    return (0);
}