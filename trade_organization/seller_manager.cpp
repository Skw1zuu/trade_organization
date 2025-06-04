#include <stdexcept>
#include <vector>
#include "seller_manager.hpp"
#include "seller.hpp"
#include "trade_point.hpp"
#include "repository.hpp"
#include "product_order.hpp"
#include "sale.hpp"

seller_manager::seller_manager(seller_repository& seller_repo, 
    trade_point_repository& trade_point_repo, sale_repository& sale_repo, 
    product_order_repository& product_order_repo)
:
_seller_repo(seller_repo),
_trade_point_repo(trade_point_repo),
_sale_repo(sale_repo),
_product_order_repo(product_order_repo)
{}

void seller_manager::create_seller(const string first_name, const string middle_name, 
    const string last_name, const string phone_number, const float salary, 
    const string trade_point_name)
{
    seller* sel = get_seller_by_phone_number(phone_number, _seller_repo.get_all());

    if (sel != nullptr)
        throw runtime_error("Failed to create seller: phone number(" + phone_number
            + ") exists");
    
    trade_point* tp = get_tp_by_name(trade_point_name);

    if (tp == nullptr)
        throw runtime_error("Failed to create seller: trade point name(" + trade_point_name 
            + ") does not exits");

    sel = new seller(first_name, middle_name, last_name, phone_number, salary);
    tp->add_seller_id(sel->get_id());
    _seller_repo.add(sel);
}

float seller_manager::get_seller_performance(const string phone_number, const date start, 
    const date end) const
{
    seller* sel = get_seller_by_phone_number(phone_number, _seller_repo.get_all());

    if (sel == nullptr)
        throw runtime_error("Failed to get seller performance: phone number(" + phone_number + 
            ") does not exists");

    float out = 0;
    const vector<sale*> sales = _sale_repo.get_all();
    for (unsigned int i = 0; i < sales.size(); ++i)
    {
        if (sales[i]->get_seller_id() != sel->get_id() || sales[i]->get_sale_date() < start || 
            sales[i]->get_sale_date() > end)
            continue;

        const vector<unsigned int>& product_order_ids = sales[i]->get_product_order_ids();
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[j]);
            out += prod_order->get_quantity() * prod_order->get_price_per_unit();
        }
    }
        
    return out / (end - start);
}
float seller_manager::get_seller_performance_by_tp_type(const string phone_number, 
    const string trade_point_type, const date start, const date end) const
{
    seller* sel = get_seller_by_phone_number(phone_number, _seller_repo.get_all());

    if (sel == nullptr)
        throw runtime_error("Failed to get seller performance: phone number(" + phone_number + 
            ") does not exists");

    vector<trade_point*> tps = get_tps_by_type(trade_point_type);
    
    float out = 0;
    for (unsigned int i = 0; i < tps.size(); ++i)
        out += get_seller_performance_by_sales(tps[i]->get_sale_ids(), sel, start, end);

    return out;
}
float seller_manager::get_seller_performance_by_tp_name(const string phone_number, 
    const string trade_point_name, const date start, const date end) const
{
    seller* sel = get_seller_by_phone_number(phone_number, _seller_repo.get_all());

    if (sel == nullptr)
        throw runtime_error("Failed to get seller performance: phone number(" + phone_number + 
            ") does not exists");
    
    trade_point* tp = get_tp_by_name(trade_point_name);

    if (tp == nullptr)
        throw runtime_error("Failed to get trade point by name: name(" + trade_point_name + 
            "does not exists");
    
    return get_seller_performance_by_sales(tp->get_sale_ids(), sel, start, end);
}
const vector<seller*>& seller_manager::get_sellers() const
{
    return _seller_repo.get_all();
}
vector<seller*> seller_manager::get_sellers_by_tp_type(const string trade_point_type) const
{
    vector<trade_point*> tps = get_tps_by_type(trade_point_type);

    if (tps.size() == 0)
        throw runtime_error("Failed to get trade points by type: type(" + trade_point_type + 
            ") does not exists");
    
    vector<seller*> out;
    for (unsigned int i = 0; i < tps.size(); ++i)
    {
        const vector<unsigned int>& seller_ids = tps[i]->get_seller_ids();
        for (unsigned int j = 0; j < seller_ids.size(); ++j)
            out.push_back(_seller_repo.get_by_id(seller_ids[j]));
    }

    return out;
}
vector<seller*> seller_manager::get_sellers_by_tp_name(const string trade_point_name) const
{
    trade_point* tp = get_tp_by_name(trade_point_name);

    if (tp == nullptr)
        throw runtime_error("Failed to get trade point by name: name(" + trade_point_name + 
            "does not exists");

    vector<seller*> out;
    const vector<unsigned int>& seller_ids = tp->get_seller_ids();
    for (unsigned int i = 0; i < seller_ids.size(); ++i)
        out.push_back(_seller_repo.get_by_id(seller_ids[i]));

    return out;
}
seller* seller_manager::get_seller_by_phone_number(const string phone_number) const
{
    seller* out = get_seller_by_phone_number(phone_number, _seller_repo.get_all());

    if (out == nullptr)
        throw runtime_error("Failed to get seller: phone number(" + phone_number + 
            ") does not exists");
    return out;
}

seller* seller_manager::get_seller_by_phone_number(const string phone_number, 
    const vector<seller*>& sellers) const
{
    for (unsigned int i = 0; i < sellers.size(); ++i)
        if (sellers[i]->get_phone_number() == phone_number)
            return sellers[i];

    return nullptr;
}
trade_point* seller_manager::get_tp_by_name(const string trade_point_name) const
{
    const vector<trade_point*> trade_points = _trade_point_repo.get_all();
    for (unsigned int i = 0; i < trade_points.size(); ++i)
        if (trade_points[i]->get_name() == trade_point_name)
            return trade_points[i];

    return nullptr;
}
vector<trade_point*> seller_manager::get_tps_by_type(const string trade_point_type) const
{
    vector<trade_point*> out;
    const vector<trade_point*>& tps = _trade_point_repo.get_all();
    for (unsigned int i = 0; i < tps.size(); ++i)
        if (tps[i]->get_type() == trade_point_type)
            out.push_back(tps[i]);
    
    return out;
}
float seller_manager::get_seller_performance_by_sales(const vector<unsigned int>& sale_ids, 
    seller* sel, const date start, const date end) const
{
    float out = 0;
    for (unsigned int i = 0; i < sale_ids.size(); ++i)
    {
        sale* sal = _sale_repo.get_by_id(sale_ids[i]);
        if (sal->get_seller_id() != sel->get_id() || sal->get_sale_date() < start || 
            sal->get_sale_date() > end)
            continue;

        const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
        for (unsigned int j = 0; j < product_order_ids.size(); ++j)
        {
            product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[j]);
            out += prod_order->get_quantity() * prod_order->get_price_per_unit();
        }
    }

    return out / (end - start);
}
