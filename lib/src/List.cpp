#include "List.hpp"
#include <memory>

List::List(const std::string& name) 
    :m_name(name)
{
    
}

List::CardArray& List::GetCardsRef() {
    return m_cards;
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
    m_cards.push_back(std::make_shared<Card>(card));
}

void List::AddCard(const List::CardPointer& card){
    m_cards.push_back(card);
}

void List::RemoveCard(List::CardArray::iterator it) {
    m_cards.erase(it);
}