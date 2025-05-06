#pragma once
#include "api.h"
#include "Card.hpp"
#include "ContainerBase.hpp"


struct EXPORT_API ListData {
    std::string name;
};

class EXPORT_API List : public ContainerBase<Card, ListData> {
public:
    List(const ListData& data) : ContainerBase<Card, ListData>(data) {}
};