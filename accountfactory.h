#ifndef ACCOUNTFACTORY_H
#define ACCOUNTFACTORY_H

#include "account.h"

#include <vector>
#include <memory>

/**
 * @brief The factory design pattern for create acoout objects
 *        There factories are alse singletons
 */

class StockAccountFactory {
    enum {DEFAULT_BALANCE = 10000 };
public:
    std::shared_ptr<StockAccount> createAccount(
            std::string name, double balance = DEFAULT_BALANCE);

    std::shared_ptr<StockAccount> getAccountByName(std::string name);

    static StockAccountFactory& getInstance()
    { return m_instance; }

private:
    std::vector<std::shared_ptr<StockAccount> > m_stock_accounts;

private:
    StockAccountFactory() { }
    static StockAccountFactory m_instance;
};



#endif // ACCOUNTFACTORY_H
