#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _databases;

        float findValue(const std::string& date) const;
        bool validateDate(const std::string& date) const;
        bool validValue(std::string value) const;
    public:
        BitcoinExchange();
        BitcoinExchange(const std::string& databaseFile);
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        void loadDatabase(const std::string& filename);
        void processInput(const std::string& filename);
};

#endif