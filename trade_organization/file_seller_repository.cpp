#include <string>
#include <vector>
#include "file_seller_repository.hpp"
#include "str_util.hpp"

file_seller_repository::file_seller_repository()
:
file_repository_base("seller_repo")
{
    load();
}
file_seller_repository::~file_seller_repository()
{
    save();
}

string file_seller_repository::entity_to_string(seller* ent)
{
    string out = to_string(ent->get_id()) + FILE_FIELDS_SEP + 
                 ent->get_first_name() + FILE_FIELDS_SEP + 
                 ent->get_middle_name() + FILE_FIELDS_SEP + 
                 ent->get_last_name() + FILE_FIELDS_SEP + 
                 ent->get_phone_number() + FILE_FIELDS_SEP +
                 to_string(ent->get_salary()) + FILE_FIELDS_SEP;
    
    return out;
}
seller* file_seller_repository::string_to_entity(string record)
{
    vector<string> fields = str_util::split_str(record, '|');
    
    return new seller(stoul(fields[0]), fields[1], fields[2], 
        fields[3], fields[4], stof(fields[5]));
}
