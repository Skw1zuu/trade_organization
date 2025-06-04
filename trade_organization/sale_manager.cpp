#include <stdexcept>
#include <utility>
#include "sale_manager.hpp"
#include "sale.hpp"
#include "trade_point.hpp"
#include "customer.hpp"
#include "entity.hpp"

sale_manager::sale_manager(sale_repository& sale_repo, trade_point_repository& trade_point_repo, 
    product_order_repository& product_order_repo, product_repository& product_repo, 
    seller_repository& seller_repo, customer_repository& customer_repo)
:
_sale_repo(sale_repo),
_trade_point_repo(trade_point_repo),
_product_order_repo(product_order_repo),
_product_repo(product_repo),
_seller_repo(seller_repo),
_customer_repo(customer_repo)
{}

void sale_manager::create_sale(const date sale_date, vector<product_order_quantity_st>& product_orders, 
    const string customer_name, const string customer_phone_number, 
    const string seller_phone_number, const string trade_point_name)
{
    trade_point* tp = get_tp_by_name(trade_point_name);

    if (tp == nullptr)
        throw runtime_error("Failed to get trade point by name: name(" + trade_point_name + 
            ") does not exists");
    
    seller* sel = nullptr;
    const vector<unsigned int>& seller_ids = tp->get_seller_ids();
    for (unsigned int i = 0; i < seller_ids.size(); ++i)
    {
        seller* tmp = _seller_repo.get_by_id(seller_ids[i]);
        if (tmp->get_phone_number() == seller_phone_number)
            sel = tmp;
    }

    if (sel == nullptr)
        throw runtime_error("Feiled to get seller from trade point: phone number(" + 
            seller_phone_number + ") does not exists");
    
    const vector<unsigned int>& prod_order_ids = tp->get_product_order_ids();
    bool is_exists = false;
    vector<pair<product_order*, product_order_quantity_st&>> sale_map;
    for (unsigned int i = 0; i < product_orders.size(); ++i)
    {
        is_exists = false;
        for (unsigned int j = 0; j < prod_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(prod_order_ids[j]);
            product* prod = _product_repo.get_by_id(prod_order->get_product_id());
            if (product_orders[i].product_name == prod->get_name() && 
                product_orders[i].product_type == prod->get_type())
            {
                if (prod_order->get_quantity() < product_orders[i].quantity)
                    throw runtime_error("Failed to create sale: product quantity(" + 
                        product_orders[i].product_name + " " + product_orders[i].product_type + 
                        " " + to_string(product_orders[i].quantity) + ") is larger than available");
                
                sale_map.push_back({ prod_order, product_orders[i] });

                is_exists = true;
                break;
            }
        }
        if (is_exists)
            continue;

        throw runtime_error("Failed to create sale: product(" + product_orders[i].product_name + 
            " " + product_orders[i].product_type + ") does not exists");
    }

    vector<unsigned int> sale_prod_order_ids;
    for (unsigned int i = 0; i < sale_map.size(); ++i)
    {
        sale_map[i].first->set_quantity(sale_map[i].first->get_quantity() - 
            sale_map[i].second.quantity);
            
        product_order* sale_prod_order = new product_order(sale_map[i].first->get_product_id(), 
            sale_map[i].second.quantity, sale_map[i].first->get_price_per_unit());
        _product_order_repo.add(sale_prod_order);
        sale_prod_order_ids.push_back(sale_prod_order->get_id());
    }

    if (tp->get_type() == "KIOSK")
    {
        sale* sal = new sale(sale_date, sale_prod_order_ids, sel->get_id(), NULL_ID, tp->get_id());
        tp->add_sale_id(sal->get_id());
        _sale_repo.add(sal);
        return;
    }

    const vector<customer*>& customers = _customer_repo.get_all();
    customer* cust = nullptr;
    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        if (customers[i]->get_phone_number() == customer_phone_number)
        {
            cust = customers[i];
            break;
        }
    }

    if (cust == nullptr)
    {
        cust = new customer(customer_name, customer_phone_number);
        _customer_repo.add(cust);
    }

    sale* sal = new sale(sale_date, sale_prod_order_ids, sel->get_id(),
        cust->get_id(), tp->get_id());
    tp->add_sale_id(sal->get_id());
    cust->add_sale_id(sal->get_id());
    _sale_repo.add(sal);
}

unsigned int sale_manager::get_sale_amount_by_product(const product_st prod,
    const date start, const date end) const
{
    unsigned int out = 0;
    const vector<sale*> sales = _sale_repo.get_all();
    for (unsigned int i = 0; i < sales.size(); ++i)
    {
        const vector<unsigned int>& product_order_ids = sales[i]->get_product_order_ids();
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[j]);
            product* p = _product_repo.get_by_id(prod_order->get_product_id());
            if (prod.product_name != p->get_name() || prod.product_type != p->get_type())
                continue;

            out += prod_order->get_quantity();
        }
    }

    return out;
}
unsigned int sale_manager::get_sale_amount_by_product_and_tp_type(const product_st prod, 
    const string trade_point_type, const date start, const date end) const
{
    unsigned int out = 0;
    const vector<trade_point*>& tps = _trade_point_repo.get_all();
    for (unsigned int i = 0; i < tps.size(); ++i)
        if (tps[i]->get_type() == trade_point_type)
            out += get_sale_amount_by_prod(tps[i]->get_sale_ids(), prod, start, end);
    
    return out;
}
unsigned int sale_manager::get_sale_amount_by_product_and_tp_name(const product_st prod, 
    const string trade_point_name, const date start, const date end) const
{
    trade_point* tp = get_tp_by_name(trade_point_name);

    if (tp == nullptr)
        throw runtime_error("Failed to get trade point by name: name(" + trade_point_name + 
            ") does not exists");
    
    return get_sale_amount_by_prod(tp->get_sale_ids(), prod, start, end);
}
float sale_manager::get_tp_turnover(const string trade_point_name, const date start, 
    const date end) const
{
    trade_point* tp = get_tp_by_name(trade_point_name);

    if (tp == nullptr)
        throw runtime_error("Failed to get trade point by name: name(" + trade_point_name + 
            ") does not exists");
    
    float out = 0;
    const vector<unsigned int>& sale_ids = tp->get_sale_ids();
    for (unsigned int i = 0; i < sale_ids.size(); ++i)
    {
        sale* sal = _sale_repo.get_by_id(sale_ids[i]);
        if (sal->get_sale_date() < start || sal->get_sale_date() > end)
            continue;

        const vector<unsigned int> product_order_ids = sal->get_product_order_ids();
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[j]);
            out += prod_order->get_quantity() * prod_order->get_price_per_unit();
        }
    }

    return out;
}
float sale_manager::get_tp_turnover(const vector<string>& trade_point_names, const date start, 
        const date end) const
{
    float out = 0;
    for (unsigned int i = 0; i < trade_point_names.size(); ++i)
        out += get_tp_turnover(trade_point_names[i], start, end);

    return out;
}

unsigned int sale_manager::get_sale_amount_by_prod(const vector<unsigned int>& sale_ids, 
    const product_st& prod, const date start, const date end) const
{
    unsigned int out = 0;
    for (unsigned int i = 0; i < sale_ids.size(); ++i)
    {
        sale* sal = _sale_repo.get_by_id(sale_ids[i]);
        if (sal->get_sale_date() < start || sal->get_sale_date() > end)
            continue;

        const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[j]);
            product* p = _product_repo.get_by_id(prod_order->get_product_id());
            if (prod.product_name != p->get_name() || prod.product_type != p->get_type())
                continue;

            out += prod_order->get_quantity();
        }
    }

    return out;
}
trade_point* sale_manager::get_tp_by_name(const string trade_point_name) const
{
    const vector<trade_point*> trade_points = _trade_point_repo.get_all();
    for (unsigned int i = 0; i < trade_points.size(); ++i)
        if (trade_points[i]->get_name() == trade_point_name)
            return trade_points[i];

    return nullptr;
}
