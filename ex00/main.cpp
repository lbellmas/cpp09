#include "BitcoinExchange.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <database_file> <input_file>" << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange bitcoinExchange(argv[1]);
        bitcoinExchange.processInput(argv[2]);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}