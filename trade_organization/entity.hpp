#pragma once

#define NULL_ID 0

class entity
{
public:
    unsigned int get_id() const;

protected:
    entity();
    entity(const unsigned int id);

private:
    static unsigned int _id_counter;
    unsigned int _id;

};
