#include "pch.h"
#include "Card.hpp"
#include "Board/CardPrompt/CardPrompt.hpp"
#include "List.hpp"
#include <imgui.h>
#include "BoardView.hpp"


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

static constexpr int boardWindowFlags = 
        windowFlags 
      | ImGuiWindowFlags_HorizontalScrollbar;

static constexpr int childFlags = 
          ImGuiChildFlags_FrameStyle
        | ImGuiChildFlags_Borders;

void BoardView::Draw(sf::RenderTarget& target) {
    auto& listRef = m_board->GetListsRef();
    const ImVec2 listSize = {250.f, 0.f};

    const float windowSize = (float)target.getSize().x / 1.5f;
    ImGui::SetNextWindowSize({windowSize, (float)target.getSize().y });
    ImGui::SetNextWindowPos({0.f, 0.f});
    if (ImGui::Begin(m_board->GetName().c_str(), nullptr, boardWindowFlags)){
 
        for (auto it = listRef.begin(); it < listRef.end(); ++it){
            DrawList(*(*it), listSize, 
            [this, it](){
                m_board->RemoveList(it);
            }, { (int)std::distance(listRef.begin(), it) });
            ImGui::SameLine();
        }
        if (ImGui::Button("Add List", listSize))
            m_listPrompt.Open(std::nullopt, {-1});
    }
    ImGui::End();

    DrawListPrompt();
    DrawCardPrompt();
}

void BoardView::DrawList(List& list, const ImVec2& listSize, const DeleteCallback& callback, const ListPromptData& promptData) {
    auto& cardsRef = list.GetCardsRef();
    bool deleteButtonPressed = false;

    if (ImGui::BeginChild(std::to_string(promptData.listIndex).c_str(), listSize, childFlags, windowFlags)){
        ImGui::Text("%s", list.GetName().c_str());
        ImGui::SameLine();
        deleteButtonPressed = ImGui::Button("Delete");
        ImGui::SameLine();
        if (ImGui::Button("Edit"))
            m_listPrompt.Open(list.GetData(), promptData);

        ImGui::Separator();
        for (auto it = cardsRef.begin(); it < cardsRef.end(); ++it) {
            DrawCard(*(*it), [&list, it](){
                list.RemoveCard(it);
            }, { promptData.listIndex, (int)std::distance(cardsRef.begin(), it) });
        }

        if (ImGui::Button("Add Task", {ImGui::GetContentRegionAvail().x, 0.f}))
            m_cardPrompt.Open(std::nullopt, { promptData.listIndex, -1});
    }
    ImGui::EndChild();

    if (deleteButtonPressed)
        callback();
}

void BoardView::DrawCard(Card& card, const DeleteCallback& callback, const CardPromptData& promptData) {
    bool deleteButtonPressed = false;
    if (ImGui::BeginChild(std::to_string(promptData.cardIndex).c_str(), ImVec2(0.f, 100.f), childFlags, windowFlags)){
        ImGui::Text("%s", card.GetTitle().c_str());
        if (ImGui::Button("Edit"))
            m_cardPrompt.Open(card.GetData(), promptData);

        deleteButtonPressed = ImGui::Button("Delete");
    }
    ImGui::EndChild();

    if (deleteButtonPressed)
        callback();
}

void BoardView::DrawListPrompt() {
    if (m_listPrompt.IsOpen()){
        const auto& promptData = m_listPrompt.GetPromptData();

        m_listPrompt.Draw(
            [this, &promptData](const List::Data& listData) {
            if (promptData.listIndex < 0)
                m_board->AddList(List(listData));
            else
                m_board->GetListsRef().at(promptData.listIndex)->Update(listData);
        });
    }
}

void BoardView::DrawCardPrompt() {
    if (m_cardPrompt.IsOpen()) {
        const auto& promptData = m_cardPrompt.GetPromptData();
        auto& listRef = m_board->GetListsRef();
        auto& list = listRef.at(promptData.listIndex);

        m_cardPrompt.Draw(
            [&list, &promptData](const Card::Data& cardData) {
            if (promptData.cardIndex < 0)        
                list->AddCard(Card(cardData));
            else
                list->GetCardsRef().at(promptData.cardIndex)->Update(cardData);
        });
    }
}