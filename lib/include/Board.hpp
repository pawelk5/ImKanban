#pragma once
#include "api.h"

#include "List.hpp"

class EXPORT_API Board {
public:
    using ListPointer = std::shared_ptr<List>;
    using ListArray = std::vector<ListPointer>;

public:
    Board(const std::string& name);

    ListArray& GetListsRef();
    const ListArray& GetLists() const;
    const std::string& GetName() const;
    
    void SetName(const std::string& name);
    void AddList(const List& list);
    void AddList(const ListPointer& list);

    void RemoveList(ListArray::iterator it);
    void MoveCard(
        ListArray::iterator src, List::CardArray::iterator cardsrc,
        ListArray::iterator dst);

private:
    ListArray m_lists;
    std::string m_name;

private:
    void CreateBasicLists();
};