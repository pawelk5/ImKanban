#pragma once
#include "api.h"

#include <string>

class EXPORT_API Card {
public:
    Card(const std::string& title);
    
    const std::string& GetTitle() const;
    void SetTitle(const std::string& title);

private:
    std::string m_title;
};