#include "Card.hpp"


Card::Card(const Card::Data& data) {
    Update(data);
}

const std::string& Card::GetTitle() const {
    return m_data.title;
}

Card::Data Card::GetData() const {
    return m_data;
}

void Card::SetTitle(const std::string& title) {
    m_data.title = title;
}

void Card::Update(const Card::Data& data) {
    m_data = data;
}

