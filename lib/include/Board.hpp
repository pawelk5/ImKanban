#pragma once
#include "ContainerBase.hpp"
#include "api.h"

#include "List.hpp"

struct EXPORT_API BoardData {
    std::string name;
};

class EXPORT_API Board : public ContainerBase<List, BoardData> {
public:
    struct ItemIndex {
        int list = -1;
        int card = -1;
    };

    using MoveData = ItemIndex;

public:
    Board(const BoardData& data) : ContainerBase<List, BoardData>(data) {
        CreateBasicLists();
    }
    void MoveCard(
        const MoveData& source,
        const MoveData& destination);
private:
    void CreateBasicLists();
    void ConstructorImpl();
};