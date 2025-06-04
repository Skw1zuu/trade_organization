#pragma once
#include <vector>
#include <string>
#include "supply.hpp"
#include "product.hpp"
#include "repository.hpp"

class supply_manager
{
public:
    supply_manager(supply_repository& supply_repo, supplier_repository& supplier_repo, 
        product_order_repository& product_order_repo, product_repository& product_repo);

    void create_supply(const string supplier_name, const date cooperation_start, 
        const date cooperation_end, vector<product_st>& products);
    
    vector<supply_st> get_supply_by_supplier(const string name) const;
    vector<supply_st> get_supply_by_supplier(const string name, const date start, 
        const date end) const;
    supply_st get_supply_by_number(const unsigned int number) const;

private:
    supply_repository& _supply_repo;
    supplier_repository& _supplier_repo;
    product_order_repository& _product_order_repo;
    product_repository& _product_repo;

    supplier* get_supplier_by_name(const string name) const;
    supply_st get_supply_info(supply* sup) const;
    
};
