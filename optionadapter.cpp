#include "optionadapter.h"
#include "accountfactory.h"

OptionAdapter OptionAdapter::adapterInstance;

StockOptionAdapter StockOptionAdapter::m_instance;
BankOptionAdapter BankOptionAdapter::m_instance;
ExitOption ExitOption::instance;

bool OptionAdapter::dealWithOption(
        ScreenPrinter::Option_Type type) const
{
    bool isEnd = false;
    int option = 0;
    StockAccountPrinter& stock_printer = StockAccountPrinter::getInstance();
    StockOptionAdapter& stock_options = StockOptionAdapter::getInstance();

    BankAccountPrinter& bank_printer = BankAccountPrinter::getInstance();
    BankOptionAdapter& bank_options = BankOptionAdapter::getInstance();

    ExitOption& exit_options = ExitOption::getInstance();

    switch (type) {
    case ScreenPrinter::OP_STOCK_ACCOUNT:
        for (;;) {
            option = stock_printer.selectOptions();
            bool back = stock_options.dealWithOption(
                        (StockAccountPrinter::Option_Type) option);
            if (back) break;
        }
        break;

    case ScreenPrinter::OP_BANK_ACCOUNT:
        for (;;) {
            option = bank_printer.selectOptions();
            bool back = bank_options.dealWithOption(
                        (BankAccountPrinter::Option_Type) option);
            if (back) break;
        }
        break;

    case ScreenPrinter::OP_EXIT:
        exit_options.exitSystem();
        isEnd = true;
        break;

    default:
        break;
    }

    return isEnd;
}

bool StockOptionAdapter::dealWithOption(
        StockAccountPrinter::Option_Type type) const
{
    bool returnPrevMenu = false;

    StockAccountFactory& factory = StockAccountFactory::getInstance();
    std::shared_ptr<StockAccount> stock_account =
            factory.getAccountByName(DEFAULT_ACCOUNT_NAME);

    switch (type) {
    case StockAccountPrinter::OP_DISPLAY_PRICE:
        dispalyPriceBySymbol();
        break;
    case StockAccountPrinter::OP_DISPLAY_PORTFOLIO:
        displayCurrentPortfolio(*stock_account);
        break;

    case StockAccountPrinter::OP_BUY_SHARES:
        break;

    case StockAccountPrinter::OP_SELL_SHARES:
        break;

    case StockAccountPrinter::OP_VIEW_GRAPH:
        break;

    case StockAccountPrinter::OP_VIEW_HISTROY:
        break;

    case StockAccountPrinter::OP_RETURN_MENU:
        returnPrevMenu = true;
        break;

    default:
        break;
    }

    return returnPrevMenu;
}

void StockOptionAdapter::dispalyPriceBySymbol() const
{
    StockAccountPrinter& stock_printer = StockAccountPrinter::getInstance();
    std::ostream &out = stock_printer.getOutStream();
    std::istream &in = stock_printer.getInStream();

    std::string company_symbol;
    out << "Please enter the stock symbol: ";
    in >> company_symbol;

    double price = StockAccount::getStockPrice(company_symbol);

    if (price < 0) {    // not found
        std::cerr << "Stock Symbol cannot be found." << std::endl << std::endl;
    } else {
        out << "Company-Symbol\tPrice per share" << std::endl;
        out << company_symbol << "\t$" << price << std::endl << std::endl;
    }
}

void StockOptionAdapter::displayCurrentPortfolio
            (const StockAccount &stock_account) const
{
    StockAccountPrinter& stock_printer = StockAccountPrinter::getInstance();
    std::ostream &out = stock_printer.getOutStream();

    double portfolioValue = 0.0;

    std::shared_ptr<BankAccount> bank_account (stock_account.getBankAccount());
    double cash_balance = bank_account->getBalance();
    portfolioValue += cash_balance;

    out << "Cash balance = $" << cash_balance << std::endl;
    out << "CompanySymbol\tNumber\tPricePerShare\tTotalValue" << std::endl;

    const std::list<StockAccount::StockRecord>& portfolio = stock_account.getPortfolio();

    for (std::list<StockAccount::StockRecord>::const_iterator iter = portfolio.begin();
         iter != portfolio.end(); ++iter) {
        StockAccount::StockRecord record = *iter;
        std::string stock_symbol = record.first;
        int number = record.second;
        double price = StockAccount::getStockPrice(stock_symbol);

        std::cout << stock_symbol << "\t"
                  << number << "\t"
                  << price << "\t"
                  << number * price << std::endl;
        portfolioValue += number * price;
    }

    // print portfolio value
    std::cout << "Total portfolio value: $"
              << portfolioValue << std::endl << std::endl;

}

void ExitOption::exitSystem() const
{
    // save records

    // exit the system
    std::exit(0);
}

bool BankOptionAdapter::dealWithOption(
        BankAccountPrinter::Option_Type type) const
{
    bool returnPrevMenu = false;
    StockAccountFactory& factory = StockAccountFactory::getInstance();
    std::shared_ptr<StockAccount> stock_account =
            factory.getAccountByName(DEFAULT_ACCOUNT_NAME);
    std::shared_ptr<BankAccount> bank_account = stock_account->getBankAccount();

    switch (type) {
    case BankAccountPrinter::OP_VIEW_BALANCE:
        viewAccountBalance(*bank_account);
        break;

    case BankAccountPrinter::OP_DEPOSIT:
        depoistMoney(*bank_account);
        break;

    case BankAccountPrinter::OP_WITHDRAW:
        withdrawMoney(*bank_account);
        break;

    case BankAccountPrinter::OP_PRINT_HISTORY:
        printHistory(*bank_account);
        break;

    case BankAccountPrinter::OP_RETURN_MENU:
        returnPrevMenu = true;
        break;

    default:
        break;
    }
    return returnPrevMenu;
}

void BankOptionAdapter::viewAccountBalance(
        const BankAccount &bank_account) const
{
    BankAccountPrinter& bank_printer = BankAccountPrinter::getInstance();
    std::ostream& out = bank_printer.getOutStream();

    double left_balance = bank_account.getBalance();
    out << "You have $" << left_balance << " in your bank account." << std::endl;
}

void BankOptionAdapter::depoistMoney(
        BankAccount& bank_account) const
{
    BankAccountPrinter& bank_printer = BankAccountPrinter::getInstance();
    std::ostream& out = bank_printer.getOutStream();
    std::istream& in = bank_printer.getInStream();

    double amount = .0;
    double left_balance = bank_account.getBalance();
    out << "Please select the amount you wish to depoisit: $";
    in >> amount;

    if (amount < 0)
        std::cerr << "Invalid amount." << std::endl;
    else
        bank_account.setBalance(left_balance + amount);
}

void BankOptionAdapter::withdrawMoney(
        BankAccount& bank_account) const
{
    BankAccountPrinter& bank_printer = BankAccountPrinter::getInstance();
    std::ostream& out = bank_printer.getOutStream();
    std::istream& in = bank_printer.getInStream();

    double amount = .0;
    double left_balance = bank_account.getBalance();
    out << "Please select the amount you wish to withdraw: $";
    in >> amount;

    if (amount < 0 || amount > left_balance)
        std::cerr << "Invalid amount." << std::endl;
    else
        bank_account.setBalance(left_balance - amount);
}

void BankOptionAdapter::printHistory(
        BankAccount const& /*bank_account*/) const
{

}
