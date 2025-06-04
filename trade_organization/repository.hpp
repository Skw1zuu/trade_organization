#pragma once
#include <vector>
#include "customer.hpp"
#include "trade_point.hpp"
#include "sale.hpp"
#include "product.hpp"
#include "product_order.hpp"
#include "supplier.hpp"
#include "supply.hpp"
#include "seller.hpp"
#include "section.hpp"

using namespace std;

template <typename T>
class repository
{
public:
    virtual ~repository() = default;

    virtual void add(T* ent) = 0;
    virtual T* get_by_id(const unsigned int id) = 0;
    virtual const vector<T*>& get_all() = 0;
    
};

using customer_repository = repository<customer>;
using sale_repository = repository<sale>;
using trade_point_repository = repository<trade_point>;
using product_repository = repository<product>;
using product_order_repository = repository<product_order>;
using supplier_repository = repository<supplier>;
using supply_repository = repository<supply>;
using seller_repository = repository<seller>;
using section_repository = repository<section>;
