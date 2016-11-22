#include <iostream>

#include <memory>

#include "account.h"
#include "screenprinter.h"
#include "optionadapter.h"
#include "accountfactory.h"

using namespace std;

int main()
{
    // create  StockAccout
    StockAccountFactory& factory = StockAccountFactory::getInstance();
    std::shared_ptr<StockAccount> stock_account =
            factory.createAccount(DEFAULT_ACCOUNT_NAME);

    int option = -1;

    const ScreenPrinter& screen_printer = ScreenPrinter::getInstance();
    const OptionAdapter& adaper = OptionAdapter::getInstance();

    // main loop
    for (;;) {
        option = screen_printer.selectOptions();
        if (option < 0) {
            std::cerr << "Invalid option." << std::endl;
            continue;
        }
        adaper.dealWithOption((ScreenPrinter::Option_Type) option);
    }

    return 0;
}
