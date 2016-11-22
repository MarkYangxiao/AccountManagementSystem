#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <list>

#include "List.h"
#include "stock.h"


#define DEFAULT_ACCOUNT_NAME "Jack"

class Account {
public:

    Account(std::string name)
        : m_accountName(name) {}

    /**
     * @brief: decribe the type of account
     */
    virtual std::string description() = 0;

    /**
     * @brief get user's name
     */
    virtual std::string getAccountName() const { return m_accountName; }

    /**
     * @brief base class should need a virutal destructor
     */
    virtual ~Account() { }

private:
    std::string m_accountName;
};


class BankAccount : public Account {
public:
    /**
     * @brief default constructor with $10000 balance
     */
    BankAccount(std::string name, double balance)
        : Account(name)
        , m_balance(balance) {}

    // get bank account balance
    double getBalance() const { return m_balance; }

    void setBalance(double balance) { m_balance = balance; }

    virtual std::string description() { return "Back Account"; }

private:
    double m_balance;
};


class StockAccount : public Account {
public:
    typedef std::pair<std::string, int> StockRecord;

    // static functions
    StockAccount(std::string name, const std::shared_ptr<BankAccount>& bankAccount)
        : Account(name)
        , m_bankAccount(bankAccount) { }

    /**
     * @brief: get a stock price randomly
     */
    static double getStockPrice(const std::string& stockSymbol);

public:
    /**
     * @brief get all portfolio information, include stock symbol and number of stock
     * @return list of portfolio
     */
    const std::list<StockRecord>& getPortfolio() const
    { return m_portfolio; }

    /**
     * @brief get associated bank account
     * @return bank account
     */
    std::shared_ptr<BankAccount> getBankAccount() const
    { return m_bankAccount; }

    /**
     * @brief: buy shares
     */
    void buyShares(std::string const& symbol, int amount);

    /**
     * @brief: sell shares
     */
    void sellShares();

    virtual std::string description() { return "Stock Account"; }

private:
    static const std::string& getRondomResultFile();
    static const int FILE_NUMBER = 2;
    static std::map<int, std::string> fileNameTable;

private:
    std::shared_ptr<BankAccount> m_bankAccount;
    std::list<StockRecord> m_portfolio;
};

#endif // ACCOUNT_H
