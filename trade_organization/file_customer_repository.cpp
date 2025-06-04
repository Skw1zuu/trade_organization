#include <string>
#include <vector>
#include "file_customer_repository.hpp"
#include "str_util.hpp"

file_customer_repository::file_customer_repository()
:
file_repository_base("customer_repo")
{
    load();
}
file_customer_repository::~file_customer_repository()
{
    save();
}

string file_customer_repository::entity_to_string(customer* ent)
{
    string out = to_string(ent->get_id()) + FILE_FIELDS_SEP + 
                 ent->get_name() + FILE_FIELDS_SEP + 
                 ent->get_phone_number() + FILE_FIELDS_SEP + 
                 str_util::join(ent->get_sale_ids()) + FILE_FIELDS_SEP;

    return out;
}
customer* file_customer_repository::string_to_entity(string record)
{
    vector<string> fields = str_util::split_str(record, '|');
    vector<unsigned int> sale_ids = str_util::split(fields[3]);

    return new customer(stoul(fields[0]), fields[1], fields[2], 
        sale_ids);
}
