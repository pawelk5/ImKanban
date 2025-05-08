#pragma once
#include "pch.h"

/// Event handler for delayed event execution
///
/// This is useful for queuing events and executing them between drawing frames for safety
template<typename EventData>
class EventHandler {
public:
    /// Type alias for the callback function
    using Callback = std::function<void(EventData)>;

public:
    /// Default constructor
    /// \warning Should not be used, as no callback is set as default
    EventHandler()
        :m_eventData(std::nullopt), m_callback(nullptr) { ; }
    
    /// Constructs the handler with the callback
    /// \param eventCallback callback to be called in Update() function if an event was triggered
    EventHandler(const Callback& eventCallback) 
        :m_eventData(std::nullopt), m_callback(eventCallback) { ; }

    /// Triggers an event
    /// \param data The event data to store and pass to the callback
    void Trigger(const EventData& data) {
        m_eventData = data;
    }

    /// Calls the callback if an event was triggered
    void Update() {
        if (!m_eventData)
            return;
        
        if (m_callback)
            m_callback(m_eventData.value());
        m_eventData = std::nullopt;
    }

private:
    /// Stores current event data
    std::optional<EventData> m_eventData;

    /// Callback to call when an event was triggered
    Callback m_callback;
};