#include <stdexcept>
#include "trade_point_manager.hpp"
#include "department_store.hpp"
#include "kiosk.hpp"
#include "store.hpp"
#include "trade_point.hpp"

trade_point_manager::trade_point_manager(trade_point_repository& trade_point_repo, 
    product_repository& product_repo, product_order_repository& product_order_repo, 
    section_repository& section_repo, sale_repository& sale_repo, seller_repository& seller_repo)
:
_trade_point_repo(trade_point_repo),
_product_repo(product_repo),
_product_order_repo(product_order_repo),
_section_repo(section_repo),
_sale_repo(sale_repo),
_seller_repo(seller_repo)
{}

void trade_point_manager::create_kiosk(const string name, const float area, const float rent, 
    const float utilities, const unsigned int total_counters, vector<product_order_st>& product_orders)
{
    vector<unsigned int> product_order_ids = create_and_validate_tp_product_orders(name, 
        product_orders);
    
    _trade_point_repo.add(new kiosk(name, area, rent, utilities, total_counters, product_order_ids));
}
void trade_point_manager::create_store(const string name, const float area, const float rent, 
    const float utilities, const unsigned int total_counters, const unsigned int total_halls, 
    vector<product_order_st>& product_orders)
{
    vector<unsigned int> product_order_ids = create_and_validate_tp_product_orders(name, 
        product_orders);
    
    _trade_point_repo.add(new store(name, area, rent, utilities, total_counters, product_order_ids, 
        total_halls));
}
void trade_point_manager::create_department_store(const string name, const float area, const float rent, 
    const float utilities, const unsigned int total_counters, const unsigned int total_halls, 
    const unsigned int total_floors, vector<section_st>& sections, 
    vector<product_order_st>& product_orders)
{
    for (unsigned int i = 0; i < sections.size(); ++i)
        if (sections[i].floor_number > total_floors)
            throw runtime_error("Failed to create department store: section floor number(" + 
                to_string(sections[i].floor_number) + ") is larger than total floors");
    
    vector<unsigned int> section_ids;
    for (unsigned int i = 0; i < sections.size(); ++i)
    {
        section* sec = new section(sections[i].manager_first_name, 
            sections[i].manager_middle_name, sections[i].manager_last_name, 
            sections[i].floor_number);
        _section_repo.add(sec);
        section_ids.push_back(sec->get_id());
    }

    vector<unsigned int> product_order_ids = create_and_validate_tp_product_orders(name, 
        product_orders);
    
    _trade_point_repo.add(new departament_store(name, area, rent, utilities, total_counters, 
        product_order_ids, section_ids, total_floors, total_halls));
}

vector<product_order_st> trade_point_manager::get_stock_by_tp_name(const string name) const
{
    trade_point* tp = get_tp_by_name(name);

    if (tp == nullptr)
        throw runtime_error("Failed to get stock: name(" + name + ") does not exists");

    vector<product_order_st> out;
    const vector<unsigned int>& product_order_ids = tp->get_product_order_ids();
    for (unsigned int i = 0; i < product_order_ids.size(); ++i)
    {
        product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[i]);
        product* prod = _product_repo.get_by_id(prod_order->get_product_id());
        out.push_back({ prod->get_name(), prod->get_type(), 
            prod_order->get_quantity(), prod_order->get_price_per_unit() });
    }

    return out;
}
vector<pair<trade_point*, product_order_st>> trade_point_manager::get_orders_by_product(
    const product_st prod) const
{
    vector<pair<trade_point*, product_order_st>> out;
    const vector<trade_point*>& tps = _trade_point_repo.get_all();
    for (unsigned int i = 0; i < tps.size(); ++i)
    {
        product_order_st prod_info = get_product_order_by_tp(tps[i], prod);
        if (prod_info.product_name == "" || prod_info.product_type == "")
            continue;

        out.push_back({ tps[i], prod_info });
    }

    return out;
}
vector<pair<trade_point*, product_order_st>> trade_point_manager::get_orders_by_product_and_tp_type(
    const product_st prod, const string trade_point_type) const
{
    vector<pair<trade_point*, product_order_st>> out;
    const vector<trade_point*>& tps = _trade_point_repo.get_all();
    for (unsigned int i = 0; i < tps.size(); ++i)
    {
        if (tps[i]->get_type() != trade_point_type)
            continue;

        product_order_st prod_info = get_product_order_by_tp(tps[i], prod);
        if (prod_info.product_name == "" || prod_info.product_type == "")
            continue;

        out.push_back({ tps[i], prod_info });
    }

    return out;
}
pair<trade_point*, product_order_st> trade_point_manager::get_order_by_product_and_tp_name(
    const product_st prod, const string trade_point_name) const
{
    trade_point* tp = get_tp_by_name(trade_point_name);

    if (tp == nullptr)
        throw runtime_error("Failed to get trade point: name(" + trade_point_name + 
            ") does not exists");
    
    return { tp, get_product_order_by_tp(tp, prod) };
}
vector<pair<trade_point*, float>> trade_point_manager::get_area_amount_relation(
    const string trade_point_type) const
{
    vector<pair<trade_point*, float>> out;
    const vector<trade_point*>& tps = _trade_point_repo.get_all();
    for (unsigned int i = 0; i < tps.size(); ++i)
        if (tps[i]->get_type() == trade_point_type)
            out.push_back({ tps[i], get_tp_sale_amount(tps[i]) / tps[i]->get_area() });
    
    return out;
}
vector<pair<trade_point*, float>> trade_point_manager::get_hall_amount_relation(
    const string trade_point_type) const
{
    vector<pair<trade_point*, float>> out;
    const vector<trade_point*>& tps = _trade_point_repo.get_all();
    if (trade_point_type == "D_STORE")
    {
        for (unsigned int i = 0; i < tps.size(); ++i)
            if (tps[i]->get_type() == trade_point_type)
                out.push_back({ tps[i], get_tp_sale_amount(tps[i]) /
                    ((departament_store*)tps[i])->get_total_halls() });
    }
    else if (trade_point_type == "STORE")
    {
        for (unsigned int i = 0; i < tps.size(); ++i)
            if (tps[i]->get_type() == trade_point_type)
                out.push_back({ tps[i], get_tp_sale_amount(tps[i]) /
                    ((store*)tps[i])->get_total_halls() });
    }
    else
    {
        throw runtime_error("Failed to get hall amount relation: trade point type(" + trade_point_type
            + ") should be D_STORE or STORE");
    }
    
    return out;
}
vector<pair<trade_point*, float>> trade_point_manager::get_counters_amount_relation(
    const string trade_point_type) const
{
    vector<pair<trade_point*, float>> out;
    const vector<trade_point*>& tps = _trade_point_repo.get_all();
    for (unsigned int i = 0; i < tps.size(); ++i)
        if (tps[i]->get_type() == trade_point_type)
            out.push_back({ tps[i], get_tp_sale_amount(tps[i]) / tps[i]->get_total_counters() });
    
    return out;
}
float trade_point_manager::get_tp_profitability(const string trade_point_name, const date start, 
    const date end) const
{
    trade_point* tp = get_tp_by_name(trade_point_name);

    if (tp == nullptr)
        throw runtime_error("Failed to get trade point: name(" + trade_point_name + 
            ") does not exists");
    
    float salary_amount = 0;
    const vector<unsigned int>& seller_ids = tp->get_seller_ids();
    for (unsigned int i = 0; i < seller_ids.size(); ++i)
        salary_amount += _seller_repo.get_by_id(seller_ids[i])->get_salary();

    float day_count = end - start;
    return get_tp_sale_amount(tp, start, end) / (salary_amount * day_count + tp->get_utilities() * 
        day_count + tp->get_rent() * day_count);
}
trade_point* trade_point_manager::get_trade_point_by_name(const string trade_point_name) const
{
    trade_point* tp = get_tp_by_name(trade_point_name);

    if (tp == nullptr)
        throw runtime_error("Failed to get trade point: name(" + trade_point_name + 
            ") does not exists");

    return tp;
}

vector<unsigned int> trade_point_manager::create_and_validate_tp_product_orders(const string name, 
    vector<product_order_st>& product_orders) const
{
    trade_point* tp = get_tp_by_name(name);
    
    if (tp != nullptr)
        throw runtime_error("Failed to create trade point: name(" + name + ") exists");
    
    const vector<product*>& products = _product_repo.get_all();
    bool is_exists = false;
    vector<pair<unsigned int, product_order_st&>> tp_prod_map;
    for (unsigned int i = 0; i < product_orders.size(); ++i)
    {
        is_exists = false;
        for (unsigned int j = 0; j < products.size(); ++j)
        {
            if (products[j]->get_name() != product_orders[i].product_name || 
                products[j]->get_type() != product_orders[i].product_type)
                continue;

            tp_prod_map.push_back({ products[j]->get_id(), product_orders[i] });
            is_exists = true;
            break;
        }
        if (is_exists)
            continue;

        throw runtime_error("Failed to create trade point: product(" + 
            product_orders[i].product_name + " " + product_orders[i].product_type + ") does not exists");
    }

    vector<unsigned int> tp_prod_order_ids;
    for (unsigned int i = 0; i < tp_prod_map.size(); ++i)
    {
        product_order* prod_order = new product_order(tp_prod_map[i].first, 
            tp_prod_map[i].second.quantity, tp_prod_map[i].second.price_per_unit);
        _product_order_repo.add(prod_order);
        tp_prod_order_ids.push_back(prod_order->get_id());
    }

    return tp_prod_order_ids;
}
trade_point* trade_point_manager::get_tp_by_name(const string trade_point_name) const
{
    const vector<trade_point*> trade_points = _trade_point_repo.get_all();
    for (unsigned int i = 0; i < trade_points.size(); ++i)
        if (trade_points[i]->get_name() == trade_point_name)
            return trade_points[i];

    return nullptr;
}
product_order_st trade_point_manager::get_product_order_by_tp(trade_point* tp, 
    const product_st& prod) const
{    
    const vector<unsigned int>& product_order_ids = tp->get_product_order_ids();
    for (unsigned int i = 0; i < product_order_ids.size(); ++i)
    {
        product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[i]);
        product* produc = _product_repo.get_by_id(prod_order->get_product_id());
        if (produc->get_name() == prod.product_name && produc->get_type() == prod.product_type)
            return { produc->get_name(), produc->get_type(), 
                prod_order->get_quantity(), prod_order->get_price_per_unit() };
    }

    return { "", "", 0, 0 };
}
float trade_point_manager::get_tp_sale_amount(trade_point* tp) const
{
    float out = 0;
    const vector<unsigned int>& sale_ids = tp->get_sale_ids();
    for (unsigned int i = 0; i < sale_ids.size(); ++i)
    {
        sale* sal = _sale_repo.get_by_id(sale_ids[i]);
        const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[j]);
            out += prod_order->get_quantity() * prod_order->get_price_per_unit();
        }
    }
    return out;
}
float trade_point_manager::get_tp_sale_amount(trade_point* tp, const date start, const date end) const
{
    float out = 0;
    const vector<unsigned int>& sale_ids = tp->get_sale_ids();
    for (unsigned int i = 0; i < sale_ids.size(); ++i)
    {
        sale* sal = _sale_repo.get_by_id(sale_ids[i]);
        if (sal->get_sale_date() < start || sal->get_sale_date() > end)
            continue;

        const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[j]);
            out += prod_order->get_quantity() * prod_order->get_price_per_unit();
        }
    }
    return out;
}
