#include <string>
#include <vector>
#include "file_product_repository.hpp"
#include "str_util.hpp"

file_product_repository::file_product_repository()
:
file_repository_base("product_repo")
{
    load();
}
file_product_repository::~file_product_repository()
{
    save();
}

string file_product_repository::entity_to_string(product* ent)
{
    string out = to_string(ent->get_id()) + FILE_FIELDS_SEP + 
                 ent->get_name() + FILE_FIELDS_SEP + 
                 ent->get_type() + FILE_FIELDS_SEP;
    
    return out;
}
product* file_product_repository::string_to_entity(string record)
{
    vector<string> fields = str_util::split_str(record, '|');
    
    return new product(stoul(fields[0]), fields[1], fields[2]);
}
