#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock
{
public:
    // default constructor for Stock
    Stock()
        : m_companySymbol("unkown")
        , m_pricePerShare(-1.0) {}

    Stock(std::string const& companySymbol, double pricePerShare);

    // getter and setter for pricePerShare
    void setPricePerShare(double price) { m_pricePerShare = price; }
    double pricePerShare() const { return m_pricePerShare; }

    // getter for CompanySymbol
    std::string companySymbol() const { return m_companySymbol; }
private:
    // Company Symbol
    std::string m_companySymbol;
    // Price of per share
    double m_pricePerShare;
};

#endif // STOCK_H
