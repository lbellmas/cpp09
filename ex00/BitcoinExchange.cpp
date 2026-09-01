#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};

BitcoinExchange::BitcoinExchange(const std::string& databaseFile)
{
    loadDatabase(databaseFile);
};
BitcoinExchange::~BitcoinExchange() {};

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    _databases = other._databases;
};
void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: could not open database file.");
    }

    std::string line;
    std::getline(file, line); // Skip the header line
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date;
        std::string valueStr;
        float value;

        std::getline(iss, date, ','); // Read date until comma
        std::getline(iss, valueStr); // Read value after comma
        if (valueStr.empty() || !(std::istringstream(valueStr) >> value))
        {
            throw std::runtime_error("Error: invalid line format in database file.");
        }

        if (!validateDate(date))
        {
            throw std::runtime_error("Error: invalid date format in database file.");
        }

        if (!validValue(valueStr))
        {
            throw std::runtime_error("Error: invalid value in database file.");
        }
        _databases[date] = value;
    }
};

void BitcoinExchange::processInput(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: could not open input file.");
    }

    std::string line;
    std::getline(file, line); // Skip the header line
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date;
        float value;
        std::string valueStr;

        std::getline(iss, date, '|'); // Read date until pipe
        date = date.substr(0, date.find_last_not_of(" \t") + 1); // Trim whitespace
        std::getline(iss, valueStr, ' '); // Read whitespace after pipe
        std::getline(iss, valueStr); // Read value after pipe
        if (valueStr.empty() || !(std::istringstream(valueStr) >> value))
        {
            throw std::runtime_error("Error: invalid line format in input file.");
        }
        std::cout << date << " => " << value << std::endl;
        if (!validateDate(date))
        {
            throw std::runtime_error("Error: invalid date format in input file.");
        }

        if (!validValue(valueStr) || value > 1000)
        {
            throw std::runtime_error("Error: invalid value in input file.");
        }

        float exchangeRate = findValue(date);
        if (exchangeRate < 0)
        {
            throw std::runtime_error("Error: no exchange rate found for the given date.");
        }

        float result = value * exchangeRate;
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
};
float BitcoinExchange::findValue(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = _databases.lower_bound(date);
    if (it != _databases.end() && it->first == date) // Exact match found
    {
        return it->second;
    }
    else if (it != _databases.begin()) // No exact match or end reached, check for the previous date
    {
        --it; // Move to the previous date
        return it->second;
    }
    return -1; // Return -1 if the date is no previous date in the database
};

bool BitcoinExchange::validateDate(const std::string& date) const
{
    // Validate the date format (YYYY-MM-DD)
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
    {
        return false;
    }
    for (size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        daysInMonth[1] = 29; // February has 29 days in a leap year
    }
    if (month < 1 || month > 12 || day < 1 || day > daysInMonth[month - 1])
    {
        return false;
    }
    return true;
};

bool BitcoinExchange::validValue(std::string value) const
{
    if (!value.empty() && value[0] == '-')
    {
        return false; // Value should not be negative
    }

    int dotCount = 0;
    for (size_t i = 0; i < value.size(); ++i)
    {
        if (!isdigit(static_cast<unsigned char>(value[i])) && value[i] != '.')
        {
            return false; // Value should only contain digits and at most one dot
        }
        if (value[i] == '.')
        {
            dotCount++;
            if (dotCount > 1)
            {
                return false; // More than one dot is not allowed
            }
        }
    }
    return true; // Value should be non-negative
};