#pragma once
#include "api.h"

#include <string>

class EXPORT_API Card {
public:
    struct Data {
        std::string title;
    };

public:
    Card(const Data& data);
    
    Data GetData() const;
    const Data& GetDataRef() const;
    void Update(const Data& data);
    
private:
    Data m_data;
};