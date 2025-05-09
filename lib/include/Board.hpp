#pragma once
#include "ContainerBase.hpp"
#include "api.h"

#include "List.hpp"

/// Data of the board
struct EXPORT_API BoardData {
    std::string name;
};

/// Board class representing a single board
class EXPORT_API Board : public ContainerBase<List, BoardData> {
public:
    /// Index to a card or a list
    struct ItemIndex {
        int list = -1;

        /// (TODO: change to std::optional)
        int card = -1;
    };

    /// Type alias for moving items
    using MoveData = ItemIndex;

public:
    /// Inherited constructor, additionally creates pre-defined lists
    /// \param data data of the board
    Board(const BoardData& data) : ContainerBase<List, BoardData>(data) {
        CreateBasicLists();
    }

    /// Moves an item to another location
    /// \param source position of the element to be moved
    /// \param destination target position where the element should be moved
    /// \warning if destination.card is -1 or equal to the size of target list, the element will be placed at the end
    /// \throws std::out_of_range if source or destination are invalid
    void MoveCard(
        const MoveData& source,
        const MoveData& destination);

private:
    /// Creates pre-defined lists
    void CreateBasicLists();
};