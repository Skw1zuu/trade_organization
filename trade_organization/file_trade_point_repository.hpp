#pragma once
#include "file_repository_base.hpp"
#include "trade_point.hpp"

class file_trade_point_repository : public file_repository_base<trade_point>
{
public:
    file_trade_point_repository();
    ~file_trade_point_repository();

    string entity_to_string(trade_point* ent) override;
    trade_point* string_to_entity(string record) override;
    
};
