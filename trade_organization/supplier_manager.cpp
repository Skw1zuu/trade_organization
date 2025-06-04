#include <stdexcept>
#include <vector>
#include "supplier_manager.hpp"
#include "product_order.hpp"
#include "supplier.hpp"
#include "product.hpp"

supplier_manager::supplier_manager(supplier_repository& supplier_repo, 
        product_order_repository& product_order_repo, product_repository& product_repo)
:
_supplier_repo(supplier_repo),
_product_order_repo(product_order_repo),
_product_repo(product_repo)
{}

void supplier_manager::create_supplier(const string name, vector<product_order_st>& orders)
{
    const vector<supplier*>& suppliers = _supplier_repo.get_all();
    for (unsigned int i = 0; i < suppliers.size(); ++i)
        if (suppliers[i]->get_name() == name)
            throw runtime_error("Failed to create supplier: name exists");

    vector<unsigned int> product_order_ids;
    const vector<product*>& products = _product_repo.get_all();
    bool is_exists = false;
    for (unsigned int i = 0; i < orders.size(); ++i)
    {
        is_exists = false;
        for (unsigned int j = 0; j < products.size(); ++j)
        {
            if (orders[i].product_name != products[j]->get_name() || 
                orders[i].product_type != products[j]->get_type())
                continue;

            add_order(products[j], orders[i], product_order_ids);
            is_exists = true;
            break;
        }
        if (is_exists)
            continue;

        product* prod = new product(orders[i].product_name, orders[i].product_type);
        _product_repo.add(prod);
        add_order(prod, orders[i], product_order_ids);
    }

    _supplier_repo.add(new supplier(name, product_order_ids));
}

vector<supplier*> supplier_manager::get_suppliers_by_product_type(const string product_type) const
{
    vector<supplier*> out;
    const vector<supplier*>& suppliers = _supplier_repo.get_all();
    for (unsigned int i = 0; i < suppliers.size(); ++i)
    {
        const vector<unsigned int>& product_order_ids = suppliers[i]->get_product_order_ids();
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            if (_product_repo.get_by_id(_product_order_repo.get_by_id(
                product_order_ids[j])->get_product_id())->get_type() != product_type)
                continue;

            out.push_back(suppliers[i]);
            break;
        }
    }
    return out;
}
vector<supplier*> supplier_manager::get_suppliers_by_product_quantity(const product_st prod, 
const unsigned int min_quantity, const unsigned int day_count) const
{
    vector<supplier*> out;
    const vector<supplier*>& suppliers = _supplier_repo.get_all();
    for (unsigned int i = 0; i < suppliers.size(); ++i)
    {
        const vector<unsigned int>& product_order_ids = suppliers[i]->get_product_order_ids();
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[j]);
            product* produc = _product_repo.get_by_id(prod_order->get_product_id());
            if (produc->get_name() != prod.product_name || produc->get_type() != prod.product_type 
                || (prod_order->get_quantity() * day_count) < min_quantity)
                continue;

            out.push_back(suppliers[i]);
            break;
        }
    }
    return out;
}

void supplier_manager::add_order(product* prod, product_order_st& prod_order_data, 
    vector<unsigned int>& prod_order_ids)
{
    product_order* prod_order = new product_order(prod->get_id(), 
        prod_order_data.quantity,prod_order_data.price_per_unit);
    _product_order_repo.add(prod_order);
    prod_order_ids.push_back(prod_order->get_id());
}
