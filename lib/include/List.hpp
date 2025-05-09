#pragma once
#include "api.h"
#include "Card.hpp"
#include "ContainerBase.hpp"


/// Data held by a list
struct EXPORT_API ListData {
    std::string name;
};

/// List class representing a list of cards
class EXPORT_API List : public ContainerBase<Card, ListData> {
public:
    /// Constructs a list
    /// \param data data to be stored in the list
    List(const ListData& data) : ContainerBase<Card, ListData>(data) {}
};