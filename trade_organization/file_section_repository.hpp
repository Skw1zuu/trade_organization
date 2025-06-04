#pragma once
#include "file_repository_base.hpp"
#include "section.hpp"

class file_section_repository : public file_repository_base<section>
{
public:
    file_section_repository();
    ~file_section_repository();

    string entity_to_string(section* ent) override;
    section* string_to_entity(string record) override;
    
};
