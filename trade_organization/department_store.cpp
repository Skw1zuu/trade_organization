#include "department_store.hpp"
#include "trade_point.hpp"

departament_store::departament_store(const string name, const float area,
        const float rent, const float utilities, const unsigned int total_counters, 
        vector<unsigned int>& product_order_ids, vector<unsigned int>& section_ids, 
        const unsigned int total_floors, const unsigned int total_halls)
:
trade_point(name, "D_STORE", area, rent, utilities, total_counters, product_order_ids),
_total_floors(total_floors),
_total_halls(total_halls)
{}
departament_store::departament_store(const unsigned int id, const string name, const float area,
        const float rent, const float utilities, const unsigned int total_counters, 
        vector<unsigned int>& seller_ids, vector<unsigned int>& product_order_ids, 
        vector<unsigned int>& sale_ids, vector<unsigned int>& section_ids, 
        const unsigned int total_floors, const unsigned int total_halls)
:
trade_point(id, name, "D_STORE", area, rent, utilities, total_counters, seller_ids, 
    product_order_ids, sale_ids),
_total_floors(total_floors),
_total_halls(total_halls)
{}
    
vector<unsigned int> departament_store::get_section_ids() const { return _section_ids; }
unsigned int departament_store::get_total_floors() const { return  _total_floors; }
unsigned int departament_store::get_total_halls() const { return _total_halls; }
