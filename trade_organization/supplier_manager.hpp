#pragma once
#include <string>
#include <vector>
#include "repository.hpp"
#include "supplier.hpp"
#include "product_order.hpp"
#include "product.hpp"

using namespace std;

class supplier_manager
{
public:
    supplier_manager(supplier_repository& supplier_repo, 
        product_order_repository& product_order_repo, product_repository& product_repo);

    void create_supplier(const string name, vector<product_order_st>& orders);

    vector<supplier*> get_suppliers_by_product_type(const string product_type) const;
    vector<supplier*> get_suppliers_by_product_quantity(const product_st prod, 
        const unsigned int min_quantity, const unsigned int day_count) const;

private:
    supplier_repository& _supplier_repo;
    product_order_repository& _product_order_repo;
    product_repository& _product_repo;

    void add_order(product* prod, product_order_st& prod_order_data, 
        vector<unsigned int>& prod_order_ids);

};
