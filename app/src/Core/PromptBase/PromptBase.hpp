#pragma once

/// Base class for all modal popups
///
/// Defines basic logic for opening and closing a prompt and managing data and callbacks
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
template<typename InputData, typename ContextData>
class PromptBase {
public:
    /// Callback to be called when the prompt is confirmed/filled by a user
    using Callback = std::function<void(const InputData&, const ContextData&)>;

public:
    virtual ~PromptBase() = default;

    /// Opens a prompt
    /// \param data optional data (eg. to be edited), 
    /// \warning if std::nullopt then it will be initialized with default constructor
    /// \param contextData additional data, later passed to onExit callback (non-editable)
    void Open(const std::optional<InputData>& data, const ContextData& contextData) {
        if (data)
            m_data = *data;
        else
            m_data = {};
        m_contextData = contextData;
        m_open = true;
    
        OpenImpl();
    }
    
    /// Draws a prompt
    virtual void Draw(sf::RenderTarget& target) = 0;

    /// Function for handling events (closing with escape)
    void EventUpdate(const sf::Event& event, bool closeOnEscape = true) {
        if (!closeOnEscape)
            return;

        if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Escape)
                Close();
        }
    }


    /// Closes the prompt
    /// \warning Close OUTSIDE ImGui rendering context, otherwise it may lead to undefined behavior
    void Close() {
        m_open = false;
    }

    /// \return Returns true if the prompt is open
    bool IsOpen() {
        return m_open;
    }

    /// \return returns copy of contextData
    ContextData GetContextData() {
        return m_contextData;
    }

    /// \return returns const reference to contextData
    const ContextData& GetContextDataRef() {
        return m_contextData;
    }

    /// Sets callback to be called when the prompt is confirmed/filled by a user
    /// \param onExitCallback callback to be called
    void SetOnExitCallback(const Callback& onExitCallback) {
        m_onExit = onExitCallback;
    }
    
protected:
    /// Stores flag if the popup is open
    bool m_open;

    /// Data to be passed to onExit callback (eg. data to be edited)
    InputData m_data;
    
    /// Additional data to be passed to onExit callback, should not be edited
    ContextData m_contextData;

    /// Callback to be called on success
    Callback m_onExit;
protected:
    PromptBase() = default;

    /// OpenImpl is called in Open function and handles data initialization for a prompt
    virtual void OpenImpl() = 0;
    /// Returns ImGui ID of the popup (title displayed at the top of the popup)
    virtual const char* GetPopupID() = 0;

    /// Closes popup
    /// \warning This should be used only in draw function
    void ClosePopup() {
        m_open = false;
        ImGui::CloseCurrentPopup();
    }    
};