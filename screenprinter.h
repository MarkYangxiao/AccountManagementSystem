#ifndef SCREENPRINTER_H
#define SCREENPRINTER_H

#include <iostream>

/**
 * @brief The ScreenPrinter class - a singleton class
 */

class ScreenPrinter
{
public:
    enum Option_Type {
        OP_BEGIN   = 1,

        OP_STOCK_ACCOUNT   = OP_BEGIN,
        OP_BANK_ACCOUNT    =  2,
        OP_EXIT            =  3,

        OP_END             = OP_EXIT,
        OP_ERROR           = -1
    };

public:
    /**
     * @brief print select menu
     * @return selected option
     */
    virtual int selectOptions() const;
    virtual ~ScreenPrinter() { }

    /**
     * @brief change out stream
     * @param out - new out stream
     */
    virtual void setOutStream(std::ostream& out) { m_out = &out; }
    /**
     * @brief change in stream
     * @param in - new in stream
     */
    virtual void setInStream(std::istream& in) { m_in = &in; }

    virtual std::ostream& getOutStream() { return *m_out; }

    virtual std::istream& getInStream() { return *m_in; }

    /**
     * @brief get sigleton instance of ScreenPrinter
     * @return the instance
     */
    static ScreenPrinter& getInstance() { return m_instance; }

protected:
    std::ostream* m_out;
    std::istream* m_in;

    static const std::string WELCOME_TITLE;

    static ScreenPrinter m_instance;

protected:
    ScreenPrinter(std::ostream& out = std::cout,
                  std::istream& in = std::cin)
        : m_out(&out)
        , m_in(&in) { }
};


class StockAccountPrinter : public ScreenPrinter {
public:
    enum Option_Type {
        OP_DISPLAY_PRICE     = 1,
        OP_BEGIN             = OP_DISPLAY_PRICE,
        OP_DISPLAY_PORTFOLIO = 2,
        OP_BUY_SHARES        = 3,
        OP_SELL_SHARES       = 4,
        OP_VIEW_GRAPH        = 5,
        OP_VIEW_HISTROY      = 6,
        OP_RETURN_MENU       = 7,
        OP_END               = OP_RETURN_MENU,
        OP_ERROR             = -1
    };

    static StockAccountPrinter& getInstance()
    { return m_instance; }

    virtual int selectOptions() const;
private:
    StockAccountPrinter(std::ostream& out = std::cout,
                        std::istream& in = std::cin)
        : ScreenPrinter(out, in) { }

    static StockAccountPrinter m_instance;
};

class BankAccountPrinter : public ScreenPrinter {
public:
    enum Option_Type {
        OP_VIEW_BALANCE  = 1,
        OP_BEGIN         = OP_VIEW_BALANCE,
        OP_DEPOSIT       = 2,
        OP_WIDTHDRAW     = 3,
        OP_PRINT_HISTORY = 4,
        OP_RETURN_MENU   = 5,
        OP_END           = OP_RETURN_MENU,
        OP_ERROR         = -1,
    };

    static BankAccountPrinter& getInstance()
    { return m_instance; }

    virtual int selectOptions() const;

private:
    BankAccountPrinter(std::ostream& out = std::cout,
                       std::istream& in = std::cin)
        : ScreenPrinter(out, in) { }

    static BankAccountPrinter m_instance;
};

#endif // SCREENPRINTER_H
