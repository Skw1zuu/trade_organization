#include <string>
#include <vector>
#include "file_supplier_repository.hpp"
#include "str_util.hpp"

file_supplier_repository::file_supplier_repository()
:
file_repository_base("supplier_repo")
{
    load();
}
file_supplier_repository::~file_supplier_repository()
{
    save();
}

string file_supplier_repository::entity_to_string(supplier* ent)
{
    string out = to_string(ent->get_id()) + FILE_FIELDS_SEP + 
                 ent->get_name() + FILE_FIELDS_SEP + 
                 str_util::join(ent->get_product_order_ids()) + FILE_FIELDS_SEP + 
                 str_util::join(ent->get_supply_ids()) + FILE_FIELDS_SEP;
    
    return out;
}
supplier* file_supplier_repository::string_to_entity(string record)
{
    vector<string> fields = str_util::split_str(record, '|');
    vector<unsigned int> product_order_ids = str_util::split(fields[2]);
    vector<unsigned int> supply_ids = str_util::split(fields[3]);

    return new supplier(stoul(fields[0]), fields[1], product_order_ids, 
        supply_ids);
}
