#pragma once
#include "ContainerBase.hpp"
#include "api.h"

#include "List.hpp"

struct EXPORT_API BoardData {
    std::string name;
};

class EXPORT_API Board : public ContainerBase<List, BoardData> {
public:
    struct MoveData {
        int listIndex = -1;
        int cardIndex = -1;
    };

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