#include <string>
#include <vector>
#include "file_product_order_repository.hpp"
#include "str_util.hpp"

file_product_order_repository::file_product_order_repository()
:
file_repository_base("product_order_repo")
{
    load();
}
file_product_order_repository::~file_product_order_repository()
{
    save();
}

string file_product_order_repository::entity_to_string(product_order* ent)
{
    string out = to_string(ent->get_id()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_product_id()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_quantity()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_price_per_unit()) + FILE_FIELDS_SEP;
    
    return out;
}
product_order* file_product_order_repository::string_to_entity(string record)
{
    vector<string> fields = str_util::split_str(record, '|');
    
    return new product_order(stoul(fields[0]), stoul(fields[1]), 
        stoul(fields[2]), stoul(fields[3]));
}
