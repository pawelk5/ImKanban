#pragma once
#include "api.h"
#include <string>

/// Data held by a card
struct CardData {
    std::string title;
};

/// Default card element class representing a single card
class EXPORT_API Card {
public:
    /// Constucts a card
    /// \param data data to be stored in the card
    explicit Card(const CardData& data);

    /// Returns a copy of stored data
    /// \return copy of stored data
    CardData GetData() const;

    /// Returns a const reference to stored data
    /// \return const reference to stored data
    const CardData& GetDataRef() const;

    /// Overwrites the card's data
    /// \param data new data to store
    void Update(const CardData& data);
    
private:
    /// Stored card data
    CardData m_data;
};