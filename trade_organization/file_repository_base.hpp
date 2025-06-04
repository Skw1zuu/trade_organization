#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "repository.hpp"

using namespace std;

#define FILE_FIELDS_SEP '|'

template <typename T>
class file_repository_base : public repository<T>
{
public:
    virtual ~file_repository_base()
    {
        for (unsigned int i = 0; i < _entities.size(); ++i)
            if (_entities[i] != nullptr)
                delete _entities[i];
    }

    void add(T* ent) override
    {
        _entities.push_back(ent);
    }
    T* get_by_id(const unsigned int id) override
    {
        for (unsigned int i = 0; i < _entities.size(); ++i)
            if (_entities[i]->get_id() == id)
                return _entities[i];

        return nullptr;
    }
    const vector<T*>& get_all() override { return _entities; }

    void save() { write_records(); }
    void load() { read_records(); }

protected:
    file_repository_base(const string file_name)
    :
    _file_name(file_name)
    {}

    virtual string entity_to_string(T* ent) = 0;
    virtual T* string_to_entity(string record) = 0;

    void write_records()
    {
        ofstream fout(_file_name);

        if (!fout.is_open())
            throw runtime_error("Failed to open file: " + _file_name);

        string record;
        for (unsigned int i = 0; i < _entities.size(); ++i)
        {
            record = entity_to_string(_entities[i]);
            fout << record << '\n';
        }

        fout.close();
    }
    void read_records()
    {
        ifstream fin(_file_name);

        if (!fin.is_open())
            return;  

        string record;
        while (getline(fin, record))
        {
            if (record.empty())
                continue;

            T* ent = string_to_entity(record);

            if (ent != nullptr)
                _entities.push_back(ent);
        }
        
        fin.close();
    }

private:
    string _file_name;
    vector<T*> _entities;
    
};
