#include <string>
#include <vector>
#include "file_section_repository.hpp"
#include "str_util.hpp"

file_section_repository::file_section_repository()
:
file_repository_base("section_repo")
{
    load();
}
file_section_repository::~file_section_repository()
{
    save();
}

string file_section_repository::entity_to_string(section* ent)
{
    string out = to_string(ent->get_id()) + FILE_FIELDS_SEP + 
                 ent->get_manager_first_name() + FILE_FIELDS_SEP + 
                 ent->get_manager_middle_name() + FILE_FIELDS_SEP + 
                 ent->get_manager_last_name() + FILE_FIELDS_SEP + 
                 to_string(ent->get_floor_number()) + FILE_FIELDS_SEP;
    
    return out;
}
section* file_section_repository::string_to_entity(string record)
{
    vector<string> fields = str_util::split_str(record, '|');
    
    return new section(stoul(fields[0]), fields[1], 
        fields[2], fields[3], stoul(fields[4]));
}
