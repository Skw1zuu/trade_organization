#pragma once
#include "command_initializer.hpp"
#include "repository.hpp"
#include "customer_manager.hpp"
#include "sale_manager.hpp"
#include "seller_manager.hpp"
#include "supplier_manager.hpp"
#include "supply_manager.hpp"
#include "trade_point_manager.hpp"

class console_app
{
public:
    console_app();
    ~console_app();

    void run();

private:
    customer_repository* _customer_repo;
    sale_repository* _sale_repo;
    trade_point_repository* _trade_point_repo;
    product_repository* _product_repo;
    product_order_repository* _product_order_repo;
    supplier_repository* _supplier_repo;
    supply_repository* _supply_repo;
    seller_repository* _seller_repo;
    section_repository* _section_repo;

    customer_manager* _customer_manager;
    sale_manager* _sale_manager;
    seller_manager* _seller_manager;
    supplier_manager* _supplier_manager;
    supply_manager* _supply_manager;
    trade_point_manager* _trade_point_manager;

    command_intializer* _command_initializer;
    
};
