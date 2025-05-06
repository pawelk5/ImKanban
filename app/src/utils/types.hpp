#pragma once
#include <string>

enum class PayloadType
{
    CardDrag,
    ListDrag
};

inline std::string ToString(PayloadType type)
{
    switch (type)
    {
    case PayloadType::CardDrag:
        return "CARD_DRAG";
    case PayloadType::ListDrag:
        return "LIST_DRAG";
    default:
        return "UNKNOWN_PAYLOAD";
    }
}