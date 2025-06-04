#include <vector>
#include "command_initializer.hpp"
#include "get_suppliers_command.hpp"
#include "add_sale_command.hpp"
#include "add_seller_command.hpp"
#include "add_supplier_command.hpp"
#include "add_supply_command.hpp"
#include "add_trade_point_command.hpp"
#include "get_customers_by_product_command.hpp"
#include "get_customers_by_tp_product_command.hpp"
#include "get_prices_command.hpp"
#include "get_profitability_command.hpp"
#include "get_salaries_command.hpp"
#include "get_sales_command.hpp"
#include "get_sales_efficiency_command.hpp"
#include "get_seller_performance_command.hpp"
#include "get_stock_command.hpp"
#include "get_supply_by_number_command.hpp"
#include "get_top_customers_command.hpp"
#include "get_turnover_command.hpp"
#include "help_command.hpp"
#include "exit_command.hpp"
#include "get_supply_command.hpp"

command_intializer::command_intializer(
    supplier_manager& supp_manager,
    customer_manager& cust_manager,
    trade_point_manager& tp_manager,
    seller_manager& sell_manager,
    supply_manager& suly_manager,
    sale_manager& sal_manager
)
{
    _commands["add-supplier"] = new add_supplier_command(supp_manager);
    _commands["add-trade-point"] = new add_trade_point_command(tp_manager);
    _commands["add-seller"] = new add_seller_command(sell_manager);
    _commands["add-supply"] = new add_supply_command(suly_manager);
    _commands["add-sale"] = new add_sale_command(sal_manager);

    _commands["get-suppliers"] = new get_suppliers_command(supp_manager);
    _commands["get-customers-by-product"] = new get_customers_by_product_command(
        cust_manager);
    _commands["get-customers-by-tp-product"] = new get_customers_by_tp_product_command(
        cust_manager);
    _commands["get-stock"] = new get_stock_command(tp_manager);
    _commands["get-prices"] = new get_prices_command(tp_manager);
    _commands["get-seller-performance"] = new get_seller_performance_command(sell_manager);
    _commands["get-sales"] = new get_sales_command(sal_manager);
    _commands["get-salaries"] = new get_salaries_command(sell_manager);
    _commands["get-sales-efficiency"] = new get_sales_efficiency_command(tp_manager);
    _commands["get-profitability"] = new get_profitability_command(tp_manager);
    _commands["get-supply-by-number"] = new get_supply_by_number_command(suly_manager);
    _commands["get-supply"] = new get_supply_command(suly_manager);
    _commands["get-top-customers"] = new get_top_customers_command(cust_manager);
    _commands["get-turnover"] = new get_turnover_command(sal_manager);
    _commands["exit"] = new exit_command();
    _commands["help"] = new help_command(get_keys());
}
command_intializer::~command_intializer()
{
    for (auto it : _commands)
        if (it.second != nullptr)
            delete it.second;
}

command* command_intializer::get_command(const string& key)
{
    const auto com = _commands.find(key);

    if (com != _commands.end())
        return com->second;

    return nullptr;
}
vector<string> command_intializer::get_keys() const
{
    vector<string> keys;

    for (auto it : _commands)
        keys.push_back(it.first);

    return keys;
}
