#include "Card.hpp"


Card::Card(const CardData& data) {
    Update(data);
}


CardData Card::GetData() const {
    return m_data;
}

const CardData& Card::GetDataRef() const {
    return m_data;
}

void Card::Update(const CardData& data) {
    m_data = data;
}

