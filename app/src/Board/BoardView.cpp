#include "Card.hpp"
#include "pch.h"
#include "List.hpp"
#include "BoardView.hpp"
#include "Board.hpp"
#include "App/App.hpp"

BoardView::BoardView(const BoardView::BoardPointer& pointer) 
    :m_board(pointer)
{
    auto& listRef = m_board->GetListsRef();
}

void BoardView::Update(float deltaTime) { ; }
void BoardView::EventUpdate(const sf::Event& event) { ; }

static constexpr int windowFlags = 
          ImGuiWindowFlags_NoSavedSettings 
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse;

static constexpr int childFlags = 
          ImGuiChildFlags_FrameStyle
        | ImGuiChildFlags_Borders;

void BoardView::Draw(sf::RenderTarget& target) {
    auto& listRef = m_board->GetListsRef();
    const ImVec2 listSize = {250.f, 0.f};

    const float windowSize = (float)target.getSize().x / 1.5f;
    ImGui::SetNextWindowSize({windowSize, (float)target.getSize().y });
    ImGui::SetNextWindowPos({0.f, 0.f});
    if (ImGui::Begin(m_board->GetName().c_str(), nullptr, windowFlags 
        | ImGuiWindowFlags_HorizontalScrollbar)){

        for (auto it = listRef.begin(); it < listRef.end(); ++it){
            DrawList(*(*it), listSize, std::distance(listRef.begin(), it));
            ImGui::SameLine();
        }
        if (ImGui::Button("Add List", listSize))
            m_listPrompt.Open();
    }
    ImGui::End();

    if (m_listPrompt.IsOpen())
        m_listPrompt.Draw(
        [this](const List& newlist) {
        m_board->AddList(newlist);
    });
}

void BoardView::DrawList(List& list, const ImVec2& listSize, uint32_t index) {
    auto& cardsRef = list.GetCardsRef();
    if (ImGui::BeginChild(std::to_string(index).c_str(), listSize, childFlags, windowFlags)){
        ImGui::Text("%s", list.GetName().c_str());
        ImGui::Separator();
        for (auto it = cardsRef.begin(); it < cardsRef.end(); ++it) {
            DrawCard(*(*it), std::distance(cardsRef.begin(), it));
        }

        if (ImGui::Button("Add Task", {ImGui::GetContentRegionAvail().x, 0.f}))
            m_cardPrompt.Open(index);
    }
    ImGui::EndChild();

    if (m_cardPrompt.IsOpen() && index == m_cardPrompt.GetIndex())
        m_cardPrompt.Draw(
        [&list](const Card& newCard) {
        list.AddCard(newCard);
    });
}

void BoardView::DrawCard(Card& card, uint32_t index) {
    if (ImGui::BeginChild(std::to_string(index).c_str(), ImVec2(0.f, 100.f), childFlags, windowFlags)){
        ImGui::Text("%s", card.GetTitle().c_str());
    }
    ImGui::EndChild();
}