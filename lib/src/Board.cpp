#include "Board.hpp"
#include <memory>
#include <array>
#include <stdexcept>

Board::Board(const std::string& name)
    :m_name(name)
{
    CreateBasicLists();
}

void Board::CreateBasicLists() {
    std::array<std::string, 3> baseListNames {
        "To Do",
        "In Progress",
        "Done"
    };
    m_lists.reserve(baseListNames.size());

    for (const auto& name : baseListNames)
        AddList(List(name));
}

Board::ListArray& Board::GetListsRef() {
    return m_lists;
}

const Board::ListArray& Board::GetLists() const {
    return m_lists;
}

const std::string& Board::GetName() const {
    return m_name;
}

void Board::SetName(const std::string& name) {
    m_name = name;
}

void Board::AddList(const List& list) {
    m_lists.push_back(std::make_unique<List>(list));
}

void Board::AddList(const Board::ListPointer& list) {
    m_lists.push_back(list);
}

void Board::RemoveList(Board::ListArray::iterator it) {
    m_lists.erase(it);
}

void Board::MoveCard(
    Board::ListArray::iterator src, List::CardArray::iterator cardsrc,
    Board::ListArray::iterator dst) {
    
    if (src == dst)
        throw std::out_of_range("src and dst are equal");

    if (src == m_lists.end())
        throw std::out_of_range("src is equal to lists.end()");

    if (cardsrc == (*src)->GetCards().end())
        throw std::out_of_range("cardsrc is equal to cards.end()");
    
    const List::CardPointer card = (*cardsrc);
    (*src)->RemoveCard(cardsrc);
    (*dst)->AddCard(card);
}