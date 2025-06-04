#include "entity.hpp"

entity::entity()
:
    _id( _id_counter++)
{}
entity::entity(const unsigned int id)
:
_id(id)
{
    if (id >= _id_counter)
        _id_counter = id + 1;
}

unsigned int entity::get_id() const { return _id; }

unsigned int entity::_id_counter = 1;
