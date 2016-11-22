#include "accountfactory.h"

StockAccountFactory StockAccountFactory::m_instance;


std::shared_ptr<StockAccount>
    StockAccountFactory::createAccount(std::string name, double balance)
{
    std::shared_ptr<BankAccount> bank_account( new BankAccount( name, balance) );

    std::shared_ptr<StockAccount> stock_account(
                new StockAccount(name, bank_account) );

    m_stock_accounts.push_back(stock_account);
    return stock_account;
}

std::shared_ptr<StockAccount>
    StockAccountFactory::getAccountByName(std::string name)
{
    std::vector<std::shared_ptr<StockAccount> >::iterator iter = m_stock_accounts.begin();

    for (; iter != m_stock_accounts.end(); ++iter) {
        if ( (*iter)->getAccountName() == name ) {
            return *iter;
        }
    }
    // not found
    return std::shared_ptr<StockAccount>();
}
