#include "screenprinter.h"

const std::string ScreenPrinter::WELCOME_TITLE =
        "Welcome to the Account Management System";

ScreenPrinter ScreenPrinter::m_instance(std::cout, std::cin);
StockAccountPrinter StockAccountPrinter::m_instance(std::cout, std::cin);
BankAccountPrinter BankAccountPrinter::m_instance(std::cout, std::cin);


int ScreenPrinter::selectOptions() const
{
    *m_out << WELCOME_TITLE << std::endl;
    *m_out << "Please select an account to access:" << std::endl
          << "1. Stock Portfoilo Account" << std::endl
          << "2. Bank Account" << std::endl
          << "3. Exit" << std::endl
          << std::endl << "Option: ";

    int option = -1;
    *m_in >> option;

    if (option < OP_BEGIN || option > OP_END)
        return (int) OP_ERROR;
    else
        return option;
}

int StockAccountPrinter::selectOptions() const
{
    *m_out << "Stock Portfolio Account" << std::endl << std::endl;
    *m_out << "Please select an option" << std::endl;
    *m_out << "1. Display the price for a stock symbol" << std::endl
           << "2. Display the current portfolio" << std::endl
           << "3. Buy shares" << std::endl
           << "4. Sell shares" << std::endl
           << "5. View a graph for the portfolio value" << std::endl
           << "6. View transaction history" << std::endl
           << "7. Return to previous menu" << std::endl
           << std::endl << "Option: ";

    int option = -1;
    *m_in >> option;

    if (option < OP_BEGIN || option > OP_END)
        return (int) OP_ERROR;
    else
        return option;
}

int BankAccountPrinter::selectOptions() const
{
    *m_out << "Bank Account" << std::endl << std::endl;
    *m_out << "Please select an option" << std::endl;
    *m_out << "1. View account balance" << std::endl
           << "2. Depoist money" << std::endl
           << "3. Withdraw money" << std::endl
           << "4. Print out history" << std::endl
           << "5. Return to previous menu" << std::endl
           << std::endl << "Option: ";

    int option = -1;
    *m_in >> option;

    if (option < OP_BEGIN || option > OP_END)
        return (int) OP_ERROR;
    else
        return option;
}
