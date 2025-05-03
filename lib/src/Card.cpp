#include "Card.hpp"

Card::Card(const std::string& title)
    :m_title(title)
{

}

const std::string& Card::GetTitle() const {
    return m_title;
}

void Card::SetTitle(const std::string& title) {
    m_title = title;
}