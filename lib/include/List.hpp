#pragma once
#include "api.h"
#include <memory>
#include <vector>

#include "Card.hpp"

class EXPORT_API List {
public:
    using CardPtr = std::shared_ptr<Card>;
    using CardArray = std::vector<CardPtr>;

public:
    List(const std::string& name);

public:
    const CardArray& GetCards() const;
    const std::string& GetName() const;

public:
    void SetName(const std::string& name);
    void AddCard(const Card& card);

private:
    CardArray m_cards;
    std::string m_name;
};