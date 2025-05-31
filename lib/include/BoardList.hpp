#pragma once
#include "api.h"
#include "Board.hpp"
#include "ContainerBase.hpp"
#include <exception>

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
    explicit BoardList(const BoardListData& data, bool loadFromFile = true) : ContainerBase<BoardData, BoardListData>(data) {
        if (loadFromFile) 
            LoadFromFile();
    }

    ~BoardList();

    /// Saves to file specified in BoardListData
    void SaveToFile();

    /// Loads from file specified in BoardListData
    void LoadFromFile();
};