#include "stock.h"

Stock::Stock(const std::string &companySymbol,
             double pricePerShare)
    : m_companySymbol(companySymbol)
    , m_pricePerShare(pricePerShare)
{

}
