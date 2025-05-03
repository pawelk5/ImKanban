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

constexpr int windowFlags = 
          ImGuiWindowFlags_NoSavedSettings 
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse;

constexpr int childFlags = 
          ImGuiChildFlags_FrameStyle
        | ImGuiChildFlags_Borders;

void BoardView::Draw(sf::RenderTarget& target) {
    auto& listRef = m_board->GetListsRef();

    ImGui::SetNextWindowSize({(float)target.getSize().x / 1.5f, (float)target.getSize().y });
    ImGui::SetNextWindowPos({0.f, 0.f});
    if (ImGui::Begin(m_board->GetName().c_str(), nullptr, windowFlags)){
        const ImVec2 listSize = {250.f, 0.f};

        for (auto it = listRef.begin(); it < listRef.end(); ++it){
            DrawList(*(*it), listSize);
            ImGui::SameLine();
        }
        ImGui::SameLine();
        ImGui::Button("Add List", listSize);
    }
    ImGui::End();
}

void BoardView::DrawList(List& list, const ImVec2& listSize) {
    auto& cardsRef = list.GetCardsRef();
    if (ImGui::BeginChild(list.GetName().c_str(), listSize, childFlags, windowFlags)){
        ImGui::Text("%s", list.GetName().c_str());
        ImGui::Separator();
        for (auto it = cardsRef.begin(); it < cardsRef.end(); ++it) {
            DrawCard(*(*it));
        }

        ImGui::Button("Add Task", {ImGui::GetContentRegionAvail().x, 0.f});
    }
    ImGui::EndChild();
}

void BoardView::DrawCard(Card& card) {
    if (ImGui::BeginChild("Karta", ImVec2(0.f, 100.f), childFlags, windowFlags)){
        ImGui::Text("%s", card.GetTitle().c_str());
    }
    ImGui::EndChild();
}