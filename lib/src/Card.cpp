#include "Card.hpp"


Card::Card(const Card::Data& data) {
    Update(data);
}


Card::Data Card::GetData() const {
    return m_data;
}

const Card::Data& Card::GetDataRef() const {
    return m_data;
}

void Card::Update(const Card::Data& data) {
    m_data = data;
}

