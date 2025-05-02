#include "Board.hpp"
#include <memory>
#include <array>

Board::Board(const std::string& name)
    :m_name(name)
{
    CreateBasicLists();
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


void Board::CreateBasicLists() {
    std::array<std::string, 3> baseListNames {
        "To Do",
        "Doing",
        "Done"
    };

    for (const auto& name : baseListNames)
        AddList(List(name));
}