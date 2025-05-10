#include "pch.h"
#include "Core/Utils/Constants.hpp"
#include "Card.hpp"
#include "List.hpp"
#include "BoardView.hpp"


void BoardView::Draw(sf::RenderTarget &target) {
    const float windowSize = (float)target.getSize().x / 1.5f;
    ImGui::SetNextWindowSize({windowSize, (float)target.getSize().y});
    ImGui::SetNextWindowPos({0.f, 0.f});
    if (ImGui::Begin(m_board->GetDataRef().name.c_str(), nullptr, defs::UIFlags::boardWindowFlags)) {
        DrawAllLists();
        if (ImGui::Button(defs::Labels::addListLabel, m_listSize))
            m_openPromptHandler.Trigger(
                OpenPromptData{ Board::ItemIndex{-1, -1},
                std::optional<ListData>(std::nullopt) 
            });
        
        /// drag drop target for list (add list button)
        CreateDragDropTarget({-1, -1}, defs::UI::PayloadType::ListDrag);
    }
    ImGui::End();

    m_listPrompt.Draw();
    m_cardPrompt.Draw();
}

void BoardView::DrawAllLists() {
    auto &listRef = m_board->GetElementArray();

    for (auto it = listRef.begin(); it < listRef.end(); ++it) {
        DrawList(it);
        ImGui::SameLine();
    }
}

void BoardView::DrawList(Board::ElementArrayIterator iter) {
    auto& list = *m_board->At(iter);
    const auto listIndex = m_board->AsIndex(iter);

    if (!ImGui::BeginChild(std::to_string(listIndex).c_str(), m_listSize, 
        defs::UIFlags::childFlags, defs::UIFlags::windowFlags)) 
        return;
        
    /// drag drop source for list
    CreateDragDropSource(list, (Board::MoveData){listIndex, -1});

    ImGui::Text("%s", list.GetDataRef().name.c_str());
    ImGui::SameLine();
    if (ImGui::Button(defs::Labels::deleteItemLabel))
        m_deleteItemHandler.Trigger(DeleteItemData{ {listIndex, -1} });
    
    ImGui::SameLine();

    if (ImGui::Button(defs::Labels::editItemLabel))
        m_openPromptHandler.Trigger(
        OpenPromptData{ Board::ItemIndex{listIndex, -1}, list.GetData() 
    });

    ImGui::Separator();
    DrawAllCards(iter);

    if (ImGui::Button(defs::Labels::addTaskLabel, {ImGui::GetContentRegionAvail().x, 0.f}))
        m_openPromptHandler.Trigger(
        OpenPromptData{ Board::ItemIndex{listIndex, -1},
        std::optional<CardData>(std::nullopt) 
    });
        
    /// drag drop target for cards (add task button)
    CreateDragDropTarget({listIndex, -1}, defs::UI::PayloadType::CardDrag);
    ImGui::EndChild();

    /// drag drop target for list
    CreateDragDropTarget({listIndex, -1}, defs::UI::PayloadType::ListDrag);
}

void BoardView::DrawAllCards(Board::ElementArrayIterator iter) {
    auto& list = *m_board->At(iter);
    const auto &cardsRef = list.GetElementArray();
    const int listIndex = m_board->AsIndex(iter);

    for (auto it = cardsRef.begin(); it < cardsRef.end(); ++it){
        DrawCard(*list.At(it),
            { m_board->AsIndex(iter), list.AsIndex(it) });
    }
}

void BoardView::DrawCard(Card& card, const Board::ItemIndex& itemIndex) {
    if (!ImGui::BeginChild(std::to_string(itemIndex.card).c_str(),
        ImVec2(0.f, 100.f), defs::UIFlags::childFlags, defs::UIFlags::windowFlags))
        return;

    /// drag drop source for card
    CreateDragDropSource(card, (Board::MoveData)itemIndex);

    ImGui::Text("%s", card.GetDataRef().title.c_str());

    if (ImGui::Button(defs::Labels::editItemLabel))
        m_openPromptHandler.Trigger(
        OpenPromptData{ itemIndex, card.GetData() 
    });

    if (ImGui::Button(defs::Labels::deleteItemLabel))
        m_deleteItemHandler.Trigger((DeleteItemData)itemIndex);
    ImGui::EndChild();

    /// drag drop target for card
    CreateDragDropTarget(itemIndex, defs::UI::PayloadType::CardDrag);
}


void BoardView::CreateDragDropSource(const Card& card, const DragDropPayload& payload) {
    HandleDragDropSource(defs::UI::PayloadType::CardDrag,
        payload, [&card]() {
        
        ImGui::Text("Moving card: %s", card.GetDataRef().title.c_str());
    });
}

void BoardView::CreateDragDropSource(const List& list, const DragDropPayload& payload) {
    HandleDragDropSource(defs::UI::PayloadType::ListDrag,
        payload, [&list]() {
        
        ImGui::Text("Moving list: %s", list.GetDataRef().name.c_str());
    });
}

void BoardView::HandleDragDropSource(defs::UI::PayloadType payloadType, const DragDropPayload& payload, const std::function<void()>& drawTooltip) {
    /// NOTE: this works becouse EndDragDropSource needs to be called only if BeginDragDropSource returned true
    if (!ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
        return;
   
    ImGui::SetDragDropPayload(
        defs::UI::ToString(payloadType),
        &payload,
        sizeof(Board::MoveData));
        
    drawTooltip();
    ImGui::EndDragDropSource();

}

void BoardView::CreateDragDropTarget(const DragDropPayload& destination, defs::UI::PayloadType payloadType) {
    /// NOTE: this works because EndDragDropTarget needs to be called only if BeginDragDropTarget returned true
    if (!ImGui::BeginDragDropTarget())
        return;

    if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(defs::UI::ToString(payloadType))) {
        if (payload->DataSize == sizeof(Board::MoveData)) {
            auto *dragPayload = static_cast<const Board::MoveData *>(payload->Data);
            m_dragdropHandler.Trigger(DragDropData{  *dragPayload, destination });
        }
    }

    ImGui::EndDragDropTarget();
}