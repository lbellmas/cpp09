#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "ERROR" << std::endl;
        return (1);
    }
    RPN cal;
    std::string expression = argv[1];
    if (cal.pars(expression) == 1)
    return (2);
    return (0);
}