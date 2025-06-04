#include <string>
#include <vector>
#include "file_supply_repository.hpp"
#include "str_util.hpp"

file_supply_repository::file_supply_repository()
:
file_repository_base("supply_repo")
{
    load();
}
file_supply_repository::~file_supply_repository()
{
    save();
}

string file_supply_repository::entity_to_string(supply* ent)
{
    string out = to_string(ent->get_id()) + FILE_FIELDS_SEP + 
                 to_string(ent->get_number()) + FILE_FIELDS_SEP + 
                 ent->get_cooperation_start().to_string() + FILE_FIELDS_SEP + 
                 ent->get_cooperation_end().to_string() + FILE_FIELDS_SEP + 
                 str_util::join(ent->get_product_order_ids()) + FILE_FIELDS_SEP;
    
    return out;
}
supply* file_supply_repository::string_to_entity(string record)
{
    vector<string> fields = str_util::split_str(record, '|');
    vector<unsigned int> product_order_ids = str_util::split(fields[4]);

    return new supply(stoul(fields[0]), stoul(fields[1]), 
        fields[2], fields[3], product_order_ids);
}
