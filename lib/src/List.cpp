#include "List.hpp"
#include <memory>

List::List(const std::string& name) 
    :m_name(name)
{
    
}

const List::CardArray& List::GetCards() const {
    return m_cards;
}

const std::string& List::GetName() const {
    return m_name;
}

void List::SetName(const std::string& name) {
    m_name = name;
}

void List::AddCard(const Card& card) {
    m_cards.push_back(std::make_unique<Card>(card));
}