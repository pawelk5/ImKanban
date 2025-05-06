#include "Board.hpp"
#include "List.hpp"
#include <array>

void Board::ConstructorImpl() {
    CreateBasicLists();
}

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
    if (!IsValid(source.listIndex))
        throw std::out_of_range(invalidIndex);
    if (!IsValid(destination.listIndex))
        throw std::out_of_range(invalidIndex);

    auto& sourceList = At(source.listIndex);
    auto& destinationList = At(destination.listIndex);

    auto sourceCard = sourceList->At(source.cardIndex);

    sourceList->RemoveElement(source.cardIndex);

    if (destination.cardIndex == -1)
        destinationList->AddElement(sourceCard);
    else
        destinationList->InsertElement(sourceCard, destination.cardIndex);
}