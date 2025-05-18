#pragma once
#include "api.h"
#include "Board.hpp"
#include "ContainerBase.hpp"

/// Data held by a board list
struct EXPORT_API BoardListData {
    /// Filepath to json file containing data about existing boards
    std::string filepath;
};

/// BoardList class representing a list of boards
class EXPORT_API BoardList : public ContainerBase<BoardData, BoardListData> {
public:
    /// Constructs a board list
    /// \param data data of the board list
    explicit BoardList(const BoardListData& data) : ContainerBase<BoardData, BoardListData>(data) {}
};