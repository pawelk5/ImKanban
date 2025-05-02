#pragma once
#include "api.h"

#include "List.hpp"

class EXPORT_API Board {
public:
    using ListPtr = std::shared_ptr<List>;
    using ListArray = std::vector<ListPtr>;

public:
    Board(const std::string& name);

public:
    const ListArray& GetLists() const;
    const std::string& GetName() const;
    
public:
    void SetName(const std::string& name);
    void AddList(const List& list);

private:
    ListArray m_lists;
    std::string m_name;

private:
    void CreateBasicLists();
};