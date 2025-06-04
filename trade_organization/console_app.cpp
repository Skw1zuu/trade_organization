#include <exception>
#include <iostream>
#include "console_app.hpp"
#include "file_customer_repository.hpp"
#include "file_product_order_repository.hpp"
#include "file_product_repository.hpp"
#include "file_sale_repository.hpp"
#include "file_section_repository.hpp"
#include "file_seller_repository.hpp"
#include "file_supplier_repository.hpp"
#include "file_supply_repository.hpp"
#include "file_trade_point_repository.hpp"

console_app::console_app()
{
    _customer_repo = new file_customer_repository();
    _sale_repo = new file_sale_repository();
    _trade_point_repo = new file_trade_point_repository();
    _product_repo = new file_product_repository();
    _product_order_repo = new file_product_order_repository();
    _supplier_repo = new file_supplier_repository();
    _supply_repo = new file_supply_repository();
    _seller_repo = new file_seller_repository();
    _section_repo = new file_section_repository();

    _customer_manager = new customer_manager(*_customer_repo, 
        *_sale_repo, *_trade_point_repo, 
        *_product_repo, *_product_order_repo);
    _sale_manager = new sale_manager(*_sale_repo, *_trade_point_repo, 
        *_product_order_repo, *_product_repo, 
        *_seller_repo, *_customer_repo);
    _seller_manager = new seller_manager(*_seller_repo, 
        *_trade_point_repo, *_sale_repo, 
        *_product_order_repo);
    _supplier_manager = new supplier_manager(*_supplier_repo, 
        *_product_order_repo, *_product_repo);
    _supply_manager = new supply_manager(*_supply_repo, 
        *_supplier_repo, *_product_order_repo, 
        *_product_repo);
    _trade_point_manager = new trade_point_manager(*_trade_point_repo, 
        *_product_repo, *_product_order_repo, 
        *_section_repo, *_sale_repo, *_seller_repo);

    _command_initializer = new command_intializer(*_supplier_manager, 
        *_customer_manager, *_trade_point_manager, 
        *_seller_manager, *_supply_manager, 
        *_sale_manager);
}
console_app::~console_app()
{
    delete _command_initializer;

    delete _customer_manager;
    delete _sale_manager;
    delete _seller_manager;
    delete _supplier_manager;
    delete _supply_manager;
    delete _trade_point_manager;

    delete _customer_repo;
    delete _sale_repo;
    delete _trade_point_repo;
    delete _product_repo;
    delete _product_order_repo;
    delete _supplier_repo;
    delete _supply_repo;
    delete _seller_repo;
    delete _section_repo;
}

void console_app::run()
{
    string cmd_str;
    while (true)
    {
        cout << "CMD$ ";
        getline(cin, cmd_str);

        command* cmd = _command_initializer->get_command(cmd_str);
        if (cmd == nullptr)
        {
            cout << "Command not found\n";
            cout << "Try again or use 'help' to see available commands\n\n";
            continue;
        }

        try 
        {
            cmd->execute();
        } 
        catch (exception& ex) 
        {
            cout << ex.what() << endl;
            return;
        }

        cout << "\n";
    }
}
