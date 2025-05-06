#pragma once
#include "api.h"

#include "List.hpp"

class EXPORT_API Board
{
public:
    using ListPointer = std::shared_ptr<List>;
    using ListArray = std::vector<ListPointer>;

    struct Data
    {
        std::string name;
    };

public:
    Board(const std::string &name);
    Board(const Data &data);

    ListArray &GetListsRef();
    const ListArray &GetLists() const;
    const std::string &GetName() const;
    Data GetData() const;

    void SetName(const std::string &name);
    void Update(const Data &data);

    void AddList(const List &list);
    void AddList(const ListPointer &list);

    void RemoveList(ListArray::iterator it);
    void MoveCard(
        ListArray::iterator src,
        List::CardArray::iterator cardsrc,
        ListArray::iterator dst,
        int index = -1);

private:
    ListArray m_lists;
    Data m_data;

private:
    void CreateBasicLists();
};