#include <string>
#include <vector>
#include "file_trade_point_repository.hpp"
#include "str_util.hpp"
#include "department_store.hpp"
#include "store.hpp"
#include "kiosk.hpp"

file_trade_point_repository::file_trade_point_repository()
:
file_repository_base("trade_point_repo")
{
    load();
}
file_trade_point_repository::~file_trade_point_repository()
{
    save();
}

string file_trade_point_repository::entity_to_string(trade_point* ent)
{
    string out = to_string(ent->get_id()) + FILE_FIELDS_SEP + 
                 ent->get_name() + FILE_FIELDS_SEP + 
                 ent->get_type() + FILE_FIELDS_SEP + 
                 to_string(ent->get_area()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_rent()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_utilities()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_total_counters()) + FILE_FIELDS_SEP + 
                 str_util::join(ent->get_seller_ids()) + FILE_FIELDS_SEP + 
                 str_util::join(ent->get_product_order_ids()) + FILE_FIELDS_SEP + 
                 str_util::join(ent->get_sale_ids()) + FILE_FIELDS_SEP;
    
    if (ent->get_type() == "D_STORE")
    {
        departament_store* d_store_ent = (departament_store*)ent;
        out += str_util::join(d_store_ent->get_section_ids()) + FILE_FIELDS_SEP + 
               to_string(d_store_ent->get_total_floors()) + FILE_FIELDS_SEP + 
               to_string(d_store_ent->get_total_halls()) + FILE_FIELDS_SEP;
    }
    else if (ent->get_type() == "STORE") 
        out += to_string(((store*)ent)->get_total_halls()) + FILE_FIELDS_SEP;
    
    return out;
}
trade_point* file_trade_point_repository::string_to_entity(string record)
{
    vector<string> fields = str_util::split_str(record, '|');
    vector<unsigned int> seller_ids = str_util::split(fields[7]);
    vector<unsigned int> product_order_ids = str_util::split(fields[8]);
    vector<unsigned int> sale_ids = str_util::split(fields[9]);

    if (fields[2] == "D_STORE")
    {
        vector<unsigned int> section_ids = str_util::split(fields[10]);
        return new departament_store(stoul(fields[0]), fields[1], 
            stof(fields[3]), stof(fields[4]), stof(fields[5]),
            stoul(fields[6]), seller_ids, product_order_ids, sale_ids, 
            section_ids, stoul(fields[11]), stoul(fields[12]));
    }
    else if (fields[2] == "STORE")
    {
        return new store(stoul(fields[0]), fields[1], stof(fields[3]), 
            stof(fields[4]), stof(fields[5]), 
            stoul(fields[6]), seller_ids, product_order_ids, sale_ids, 
            stoul(fields[10]));
    }

    return new kiosk(stoul(fields[0]), fields[1], stof(fields[3]), 
        stof(fields[4]), stof(fields[5]), 
        stoul(fields[6]), seller_ids, product_order_ids, sale_ids);
}
