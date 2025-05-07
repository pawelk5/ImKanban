#pragma once
#include "pch.h"

enum class PayloadType
{
    CardDrag,
    ListDrag
};

inline const char* ToString(PayloadType type)
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