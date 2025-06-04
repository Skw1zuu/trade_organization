#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "command.hpp"
#include "supplier_manager.hpp"
#include "customer_manager.hpp"
#include "trade_point_manager.hpp"
#include "seller_manager.hpp"
#include "supply_manager.hpp"
#include "sale_manager.hpp"

using namespace std;

class command_intializer
{
public:
    command_intializer(
        supplier_manager& supp_manager,
        customer_manager& cust_manager,
        trade_point_manager& tp_manager,
        seller_manager& sell_manager,
        supply_manager& suly_manager,
        sale_manager& sal_manager
    );
    ~command_intializer();

    command* get_command(const string& key);
    vector<string> get_keys() const;

private:
    unordered_map<string, command*> _commands;

};
