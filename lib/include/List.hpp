#pragma once
#include "api.h"
#include "Card.hpp"
#include "ContainerBase.hpp"
#include <nlohmann/json.hpp>

/// Data held by a list
struct EXPORT_API ListData
{
    std::string name;

    /// Exports ListData to JSON
    nlohmann::json exportBoard() const;

    /// Imports ListData from JSON
    static ListData importBoard(const nlohmann::json &j);
};

/// List class representing a list of cards
class EXPORT_API List : public ContainerBase<Card, ListData>
{
public:
    /// Constructs a list
    /// \param data data to be stored in the list
    explicit List(const ListData &data) : ContainerBase<Card, ListData>(data) {}

    /// Exports List to JSON
    nlohmann::json exportBoard() const;

    /// Imports List from JSON
    static List importBoard(const nlohmann::json &j);
};