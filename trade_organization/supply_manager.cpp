#include <stdexcept>
#include <vector>
#include "supply_manager.hpp"
#include "supply.hpp"
#include "product_order.hpp"

supply_manager::supply_manager(supply_repository& supply_repo, supplier_repository& supplier_repo, 
    product_order_repository& product_order_repo, product_repository& product_repo)
:
_supply_repo(supply_repo),
_supplier_repo(supplier_repo),
_product_order_repo(product_order_repo),
_product_repo(product_repo)
{}

void supply_manager::create_supply(const string supplier_name, const date cooperation_start, 
    const date cooperation_end, vector<product_st>& products)
{
    supplier* sup = get_supplier_by_name(supplier_name);

    vector<unsigned int> supply_prod_order_ids;
    bool is_exists = false;
    const vector<unsigned int>& product_order_ids = sup->get_product_order_ids();
    for (unsigned int i = 0; i < products.size(); ++i)
    {
        is_exists = false;
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[j]);
            product* prod = _product_repo.get_by_id(prod_order->get_product_id());
            if (prod->get_name() != products[i].product_name || 
                prod->get_type() != products[i].product_type)
                continue;
                
            supply_prod_order_ids.push_back(prod_order->get_id());
            is_exists = true;
            break;
        }
        if (is_exists)
            continue;

        throw runtime_error("Failed to create supply: product(" + products[i].product_name 
            + " " + products[i].product_type + ") does not available");
    }

    supply* supy = new supply(cooperation_start, cooperation_end, supply_prod_order_ids);
    sup->add_supply_id(supy->get_id());
    _supply_repo.add(supy);
}

vector<supply_st> supply_manager::get_supply_by_supplier(const string name) const
{
    supplier* sup = get_supplier_by_name(name);

    vector<supply_st> out;
    const vector<unsigned int>& supply_ids = sup->get_supply_ids();
    for (unsigned int i = 0; i < supply_ids.size(); ++i)
        out.push_back(get_supply_info(_supply_repo.get_by_id(supply_ids[i])));

    return out;
}
vector<supply_st> supply_manager::get_supply_by_supplier(const string name, const date start, 
    const date end) const
{
    supplier* sup = get_supplier_by_name(name);

    vector<supply_st> out;
    const vector<unsigned int>& supply_ids = sup->get_supply_ids();
    for (unsigned int i = 0; i < supply_ids.size(); ++i)
    {
        supply* supy = _supply_repo.get_by_id(supply_ids[i]);
        if (supy->get_cooperation_start() < start || supy->get_cooperation_start() > end || 
            supy->get_cooperation_end() < start || supy->get_cooperation_end() > end)
            continue;
        
        out.push_back(get_supply_info(supy));
    }

    return out;
}
supply_st supply_manager::get_supply_by_number(const unsigned int number) const
{
    supply* sup = nullptr;
    const vector<supply*> supy = _supply_repo.get_all();
    for (unsigned int i = 0; i < supy.size(); ++i)
    {
        if (supy[i]->get_number() == number)
            sup = supy[i];
    }

    if (sup == nullptr)
        throw runtime_error("Failed to get supply by number: number(" + to_string(number) + 
            ") does not exists");
    
    return get_supply_info(sup);
}

supplier* supply_manager::get_supplier_by_name(const string name) const
{
    const vector<supplier*>& suppliers = _supplier_repo.get_all();
    supplier* sup = nullptr;
    for (unsigned int i = 0; i < suppliers.size(); ++i)
    {
        if (suppliers[i]->get_name() == name)
        {
            sup = suppliers[i];
            break;
        }
    }

    if (sup == nullptr)
        throw runtime_error("Failed to get supplier by name: supplier(" + name 
            + ") does not exists");
    
    return sup;
}
supply_st supply_manager::get_supply_info(supply* sup) const
{
    supply_st out{ sup->get_number(), 
        sup->get_cooperation_start(), 
        sup->get_cooperation_end() };

    const vector<unsigned int>& product_order_ids = sup->get_product_order_ids();
    for (unsigned int i = 0; i < product_order_ids.size(); ++i)
    {
        product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[i]);
        product* prod = _product_repo.get_by_id(prod_order->get_product_id());
        out.orders.push_back({ prod->get_name(), 
            prod->get_type(), prod_order->get_quantity(), 
            prod_order->get_price_per_unit() });
    }

    return out;
}
