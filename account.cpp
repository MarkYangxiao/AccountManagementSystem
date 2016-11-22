#include "account.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>
#include <ctime>

std::map<int, std::string> StockAccount::fileNameTable = {
    {0, "Result_1.txt"},
    {1, "Result_2.txt"}
};

double StockAccount::getStockPrice(const std::string &stockSymbol)
{
    // read stock price from file randomly
    std::string fileName = getRondomResultFile();
    std::ifstream file(fileName, std::ios::in);
    if (!file) {
        std::cerr << "can not open file " << fileName << std::endl;
        std::exit(-1);
    }
    std::string stock_symbol;
    double value;
    std::string date;

    std::string line;
    while(!file.eof()) {
        std::getline(file, line);
        std::stringstream stream(line);
        stream >> stock_symbol >> value >> date;

        if (stock_symbol == stockSymbol)
            return value;
    }

    file.close();
    // not found stock
    return -1.0;
}

void StockAccount::buyShares(const std::string &/*symbol*/, int /*amount*/)
{
    // buy shares according to the symbol amount

}

void StockAccount::sellShares()
{

}

const std::string& StockAccount::getRondomResultFile()
{
    std::srand(std::time(NULL));
    int val = std::rand()% FILE_NUMBER;
    return fileNameTable[val];
}

