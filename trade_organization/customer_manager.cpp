#include <algorithm>
#include <utility>
#include <vector>
#include "customer_manager.hpp"
#include "product_order.hpp"
#include "sale.hpp"
#include "product.hpp"

customer_manager::customer_manager(customer_repository& customer_repo, 
        sale_repository& sale_repo, trade_point_repository& trade_point_repo, 
        product_repository& product_repo, product_order_repository& product_order_repo)
:
_customer_repo(customer_repo),
_sale_repo(sale_repo),
_trade_point_repo(trade_point_repo),
_product_repo(product_repo),
_product_order_repo(product_order_repo)
{}

vector<customer*> customer_manager::get_customers_by_purchase(const string product_type, 
    const date start, const date end) const
{
    vector<customer*> out;
    const vector<customer*>& customers = _customer_repo.get_all();
    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        const vector<unsigned int>& sale_ids = customers[i]->get_sale_ids();
        for (unsigned int j = 0; j < sale_ids.size(); ++j)
        {
            sale* sal = _sale_repo.get_by_id(sale_ids[j]);
            const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
            for (unsigned int k = 0; k < product_order_ids.size(); ++k)
            {
                if (_product_repo.get_by_id(_product_order_repo.get_by_id(
                    product_order_ids[k])->get_product_id())->get_type() != product_type 
                    || sal->get_sale_date() < start || sal->get_sale_date() > end)
                    continue;

                out.push_back(customers[i]);
                break;
            }
        }
    }
    return out;
}
vector<customer*> customer_manager::get_customers_by_purchase(const product_st prod, 
    const unsigned int min_quantity) const
{
    vector<customer*> out;
    const vector<customer*>& customers = _customer_repo.get_all();
    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        const vector<unsigned int>& sale_ids = customers[i]->get_sale_ids();
        for (unsigned int j = 0; j < sale_ids.size(); ++j)
        {
            sale* sal = _sale_repo.get_by_id(sale_ids[j]);
            const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
            for (unsigned int k = 0; k < product_order_ids.size(); ++k)
            {
                product_order* prod_order = _product_order_repo.get_by_id(
                    product_order_ids[k]);
                product* produc = _product_repo.get_by_id(prod_order->get_product_id());
                if (produc->get_name() != prod.product_name || produc->get_type() != 
                    prod.product_type || prod_order->get_quantity() < min_quantity)
                    continue;

                out.push_back(customers[i]);
                break;
            }
        }
    }
    return out;
}
vector<customer*> customer_manager::get_customers_by_product(product_st prod, 
    const date start, const date end) const
{
    vector<customer*> out;
    const vector<customer*>& customers = _customer_repo.get_all();
    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        const vector<unsigned int>& sale_ids = customers[i]->get_sale_ids();
        for (unsigned int j = 0; j < sale_ids.size(); ++j)
        {
            sale* sal = _sale_repo.get_by_id(sale_ids[j]);
            const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
            for (unsigned int k = 0; k < product_order_ids.size(); ++k)
            {
                product_order* prod_order = _product_order_repo.get_by_id(
                    product_order_ids[k]);
                product* produc = _product_repo.get_by_id(prod_order->get_product_id());
                if (produc->get_name() != produc->get_name() || produc->get_type() != 
                    prod.product_type || sal->get_sale_date() < start || 
                    sal->get_sale_date() > end)
                    continue;

                out.push_back(customers[i]);
                break;
            }
        }
    }
    return out;
}
vector<customer*> customer_manager::get_customers_by_product_and_tp_type(const product_st prod, 
    const string trade_point_type, const date start, const date end) const
{
    vector<customer*> out;
    const vector<customer*>& customers = _customer_repo.get_all();
    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        const vector<unsigned int>& sale_ids = customers[i]->get_sale_ids();
        for (unsigned int j = 0; j < sale_ids.size(); ++j)
        {
            sale* sal = _sale_repo.get_by_id(sale_ids[j]);
            if (_trade_point_repo.get_by_id(sal->get_trade_point_id())->get_type() != trade_point_type)
                continue;
            const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
            for (unsigned int k = 0; k < product_order_ids.size(); ++k)
            {
                product_order* prod_order = _product_order_repo.get_by_id(
                    product_order_ids[k]);
                product* produc = _product_repo.get_by_id(prod_order->get_product_id());
                if (produc->get_name() != prod.product_name || produc->get_type() != 
                    prod.product_type || sal->get_sale_date() < start || sal->get_sale_date() > end)
                    continue;

                out.push_back(customers[i]);
                break;
            }
        }
    }

    return out;
}
vector<customer*> customer_manager::get_customers_by_product_and_tp_name(const product_st prod, 
    const string trade_point_name, const date start, const date end) const
{
    vector<customer*> out;
    const vector<customer*>& customers = _customer_repo.get_all();
    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        const vector<unsigned int>& sale_ids = customers[i]->get_sale_ids();
        for (unsigned int j = 0; j < sale_ids.size(); ++j)
        {
            sale* sal = _sale_repo.get_by_id(sale_ids[j]);
            if (_trade_point_repo.get_by_id(sal->get_trade_point_id())->get_name() != trade_point_name)
                continue;
            const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
            for (unsigned int k = 0; k < product_order_ids.size(); ++k)
            {
                product_order* prod_order = _product_order_repo.get_by_id(
                    product_order_ids[k]);
                product* produc = _product_repo.get_by_id(prod_order->get_product_id());
                if (produc->get_name() != prod.product_name || produc->get_type() != 
                    prod.product_type || sal->get_sale_date() < start || sal->get_sale_date() > end)
                    continue;

                out.push_back(customers[i]);
                break;
            }
        }
    }
    return out;
}
vector<pair<customer*, float>> customer_manager::get_top_active_customers() const
{
    const vector<customer*>& customers = _customer_repo.get_all();
    vector<pair<customer*, float>> out;

    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        const vector<unsigned int>& sale_ids = customers[i]->get_sale_ids();
        out.push_back({ customers[i], 0 });
        for (unsigned int j = 0; j < sale_ids.size(); ++j)
        {
            sale* sal = _sale_repo.get_by_id(sale_ids[j]);
            const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
            for (unsigned int k = 0; k < product_order_ids.size(); ++k)
            {
                product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[k]);
                out.back().second += prod_order->get_quantity() * prod_order->get_price_per_unit();
            }
        }
    }

    sort(out.begin(), out.end(),
        [](const pair<customer*, float>& a, const pair<customer*, float>& b)
        {
            return a.second > b.second;
        }
    );

    return out;
}
vector<pair<customer*, float>> customer_manager::get_top_active_customers_by_tp_type(
    const string trade_point_type) const
{
    const vector<customer*>& customers = _customer_repo.get_all();
    vector<pair<customer*, float>> out;
    bool is_add = false;

    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        const vector<unsigned int>& sale_ids = customers[i]->get_sale_ids();
        is_add = false;
        for (unsigned int j = 0; j < sale_ids.size(); ++j)
        {
            sale* sal = _sale_repo.get_by_id(sale_ids[j]);
            if (_trade_point_repo.get_by_id(sal->get_trade_point_id())->get_type() != trade_point_type)
                continue;
            if (!is_add)
            {
                out.push_back({ customers[i], 0 });
                is_add = true;
            }
            const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
            for (unsigned int k = 0; k < product_order_ids.size(); ++k)
            {
                product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[k]);
                out.back().second += prod_order->get_quantity() * prod_order->get_price_per_unit();
            }
        }
    }

    sort(out.begin(), out.end(),
        [](const pair<customer*, float>& a, const pair<customer*, float>& b)
        {
            return a.second > b.second;
        }
    );

    return out;
}
vector<pair<customer*, float>> customer_manager::get_top_active_customers_by_tp_name(
    const string trade_point_name) const
{
    const vector<customer*>& customers = _customer_repo.get_all();
    vector<pair<customer*, float>> out;
    bool is_add = false;

    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        const vector<unsigned int>& sale_ids = customers[i]->get_sale_ids();
        is_add = false;
        for (unsigned int j = 0; j < sale_ids.size(); ++j)
        {
            sale* sal = _sale_repo.get_by_id(sale_ids[j]);
            if (_trade_point_repo.get_by_id(sal->get_trade_point_id())->get_name() != 
                trade_point_name)
                continue;
            if (!is_add)
            {
                out.push_back({ customers[i], 0 });
                is_add = true;
            }
            const vector<unsigned int>& product_order_ids = sal->get_product_order_ids();
            for (unsigned int k = 0; k < product_order_ids.size(); ++k)
            {
                product_order* prod_order = _product_order_repo.get_by_id(product_order_ids[k]);
                out.back().second += prod_order->get_quantity() * prod_order->get_price_per_unit();
            }
        }
    }

    sort(out.begin(), out.end(),
        [](const pair<customer*, float>& a, const pair<customer*, float>& b)
        {
            return a.second > b.second;
        }
    );

    return out;
}
