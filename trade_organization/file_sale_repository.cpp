#include <string>
#include <vector>
#include "file_sale_repository.hpp"
#include "str_util.hpp"

file_sale_repository::file_sale_repository()
:
file_repository_base("sale_repo")
{
    load();
}
file_sale_repository::~file_sale_repository()
{
    save();
}

string file_sale_repository::entity_to_string(sale* ent)
{
    string out = to_string(ent->get_id()) + FILE_FIELDS_SEP + 
                 ent->get_sale_date().to_string() + FILE_FIELDS_SEP + 
                 str_util::join(ent->get_product_order_ids()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_seller_id()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_customer_id()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_trade_point_id()) + FILE_FIELDS_SEP;
    
    return out;
}
sale* file_sale_repository::string_to_entity(string record)
{
    vector<string> fields = str_util::split_str(record, '|');
    vector<unsigned int> product_order_ids = str_util::split(fields[2]);

    return new sale(stoul(fields[0]), fields[1], product_order_ids, 
        stoul(fields[3]), stoul(fields[4]), 
        stoul(fields[5]));
}
