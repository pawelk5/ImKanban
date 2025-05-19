#include "pch.h"
#include "App.hpp"
#include "notosans/noto.embed"
#include "fontawesome/fontawesome.embed"

void App::LoadFont() {
    auto& io = ImGui::GetIO();

    /// NOTE: THIS IS FONT SPECIFIC!
    /// unicode ranges
    constexpr const ImWchar notoRanges[] = {
        0x0020, 0x00FF, // basic
        0x0100, 0x017F, // latin extended a
        0x0180, 0x024F, // latin extended b
        0x0370, 0x03FF, // greek
        0x0400, 0x04FF, // cyrillic
        0x2000, 0x206F, // punctuation
        0x20A0, 0x20CF, // currency symbols
        0,
    };

    constexpr const ImWchar fontawesomeRanges[] = {
        ICON_MIN_FA, ICON_MAX_FA,
        0,
    };

    ImFontConfig fontawesomeConfig{};
    fontawesomeConfig.MergeMode = true;
    fontawesomeConfig.GlyphMinAdvanceX = 13.0f;
    
    ImFontConfig notoConfig{};
    notoConfig.MergeMode = false;


    notoConfig.FontDataOwnedByAtlas = false;
    fontawesomeConfig.FontDataOwnedByAtlas = false;

    for (const auto& size : UI::fontSizes) {
        io.Fonts->AddFontFromMemoryTTF((void*)notoFont, notoFontSize, size, 
            &notoConfig, notoRanges);


        io.Fonts->AddFontFromMemoryTTF((void*)fontawesomeFont, fontawesomeFontSize, (0.75f * size), 
            &fontawesomeConfig, fontawesomeRanges);
    }

    if (!ImGui::SFML::UpdateFontTexture())
        throw std::runtime_error(Error::updateFontTexture);
}