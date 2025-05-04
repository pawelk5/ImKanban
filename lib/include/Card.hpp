#pragma once
#include "api.h"

#include <string>

class EXPORT_API Card {
public:
    struct EXPORT_API Data {
        std::string title;
    };

public:
    Card(const std::string& title);
    
    const std::string& GetTitle() const;
    Data GetData() const;
    
    void SetTitle(const std::string& title);
    void Update(const Data& data);
    
private:
    Data m_data;
};