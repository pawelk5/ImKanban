#include "Board.hpp"
#include "List.hpp"
#include <array>

void Board::CreateBasicLists() {
    std::array<std::string, 3> baseListNames {
        "To Do",
        "In Progress",
        "Done"};
    m_array.reserve(baseListNames.size());

    for (const auto &name : baseListNames)
        AddElement(List(ListData{name}));
}

void Board::MoveCard(
    const MoveData& source,
    const MoveData& destination)
{
    if (!IsValid(source.list))
        throw std::out_of_range(invalidIndex);
    if (!IsValid(destination.list))
        throw std::out_of_range(invalidIndex);

    auto& sourceList = At(source.list);
    auto& destinationList = At(destination.list);

    auto sourceCard = sourceList->At(source.card);

    sourceList->RemoveElement(source.card);

    if (destination.card == -1)
        destinationList->AddElement(sourceCard);
    else
        destinationList->InsertElement(sourceCard, destination.card);
}

void Board::MoveList(
    const int& source,
    const int& destination) {
    
    if (!IsValid(source))
        throw std::out_of_range(invalidIndex);
    if (!IsValid(destination) && destination != -1)
        throw std::out_of_range(invalidIndex);

    auto sourceList = At(source);
    
    RemoveElement(source);

    if (destination == -1)
        AddElement(sourceList);
    else
        InsertElement(sourceList, destination);
}