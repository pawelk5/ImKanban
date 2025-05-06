#include "List.hpp"
#include <iostream>
#include <memory>

List::List(const std::string &name)
{
    SetName(name);
}

List::List(const List::Data &data)
{
    Update(data);
}

List::CardArray &List::GetCardsRef()
{
    return m_cards;
}

const List::CardArray &List::GetCards() const
{
    return m_cards;
}

const std::string &List::GetName() const
{
    return m_data.name;
}

List::Data List::GetData() const
{
    return m_data;
}

void List::SetName(const std::string &name)
{
    m_data.name = name;
}

void List::Update(const List::Data &data)
{
    m_data = data;
}

void List::AddCard(const Card &card)
{
    m_cards.push_back(std::make_shared<Card>(card));
}

void List::AddCard(const List::CardPointer &card)
{
    m_cards.push_back(card);
}

// Insert a card at the specified index. If the index is out of range, the card is added to the end of the list.
void List::InsertCard(const List::CardPointer &card, int index)
{
    if (index < 0 || index > m_cards.size() - 1)
    {
        std::cout << "Index " << index << " out of range. Valid range: [0, " << m_cards.size() - 1 << "]" << std::endl;
        m_cards.push_back(card);
    }
    else
    {
        std::cout << "Inserting card at index " << index << std::endl;
        m_cards.insert(m_cards.begin() + index, card);
    }
}

void List::RemoveCard(List::CardArray::iterator it)
{
    m_cards.erase(it);
}