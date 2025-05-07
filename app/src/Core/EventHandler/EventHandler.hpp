#pragma once
#include "pch.h"


template<typename EventData>
class EventHandler {
public:
    using Callback = std::function<void(EventData)>;

public:
    EventHandler()
        :m_eventData(std::nullopt), m_callback(nullptr) { ; }
    EventHandler(Callback eventCallback) 
        :m_eventData(std::nullopt), m_callback(eventCallback) { ; }

    void Trigger(const EventData& data) {
        m_eventData = data;
    }

    void Update() {
        if (!m_eventData)
            return;
        
        if (m_callback)
            m_callback(m_eventData.value());
        m_eventData = std::nullopt;
    }

private:
    std::optional<EventData> m_eventData;
    Callback m_callback;
};