#ifndef OPTIONADAPTER_H
#define OPTIONADAPTER_H

#include "account.h"
#include "screenprinter.h"

class OptionAdapter
{
public:
    virtual ~OptionAdapter() { }
    static OptionAdapter& getInstance()
    { return adapterInstance; }

    bool dealWithOption(ScreenPrinter::Option_Type type) const;

protected:
    OptionAdapter() { }
    static OptionAdapter adapterInstance;
};

class StockOptionAdapter : public OptionAdapter {
public:
    bool dealWithOption(StockAccountPrinter::Option_Type type) const;
    static StockOptionAdapter& getInstance()
    { return m_instance;}

private:
    /**
     * @brief display the price for a stock symbol
     */
    void dispalyPriceBySymbol() const;

    /**
     * @brief display the current portfolio
     * @param stock_account
     */
    void displayCurrentPortfolio(StockAccount const& stock_account) const;

private:
    StockOptionAdapter() { }
    static StockOptionAdapter m_instance;
};

class BankOptionAdapter : public OptionAdapter {
public:
    bool dealWithOption(BankAccountPrinter::Option_Type type) const;
    static BankOptionAdapter& getInstance()
    { return m_instance; }

private:
    BankOptionAdapter() { }
    static BankOptionAdapter m_instance;
};

class ExitOption {
public:
    static ExitOption& getInstance()
    { return instance; }

    void exitSystem() const;
private:
    static ExitOption instance;
};

#endif // OPTIONADAPTER_H
