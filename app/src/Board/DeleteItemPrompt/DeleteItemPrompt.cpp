#include "pch.h"
#include "Core/Utils/Constants.hpp"
#include "DeleteItemPrompt.hpp"


DeleteItemPrompt::DeleteItemPrompt() {
    m_open = false;
}

const char* DeleteItemPrompt::GetPromptMessage() {
    return defs::Labels::deleteItemConfirmPromptMessage;
}