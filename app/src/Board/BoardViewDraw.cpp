#include "pch.h"
#include "Card.hpp"
#include "List.hpp"
#include "BoardView.hpp"
#include "Core/Utils/Types.hpp"


static constexpr int windowFlags =
    ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

static constexpr int boardWindowFlags =
    windowFlags | ImGuiWindowFlags_HorizontalScrollbar;

static constexpr int childFlags =
    ImGuiChildFlags_FrameStyle | ImGuiChildFlags_Borders;

void BoardView::Draw(sf::RenderTarget &target) {
    const float windowSize = (float)target.getSize().x / 1.5f;
    ImGui::SetNextWindowSize({windowSize, (float)target.getSize().y});
    ImGui::SetNextWindowPos({0.f, 0.f});
    if (ImGui::Begin(m_board->GetDataRef().name.c_str(), nullptr, boardWindowFlags)) {
        DrawAllLists();
        if (ImGui::Button("Add List", m_listSize))
            m_openPromptHandler.Trigger(
                { -1, -1, std::optional<ListData>(std::nullopt) }
            );
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

    if (ImGui::BeginChild(std::to_string(listIndex).c_str(), m_listSize, childFlags, windowFlags)) {
        ImGui::Text("%s", list.GetDataRef().name.c_str());
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
            m_deleteItemHandler.Trigger({ listIndex, -1 });
        ImGui::SameLine();
        if (ImGui::Button("Edit"))
            m_openPromptHandler.Trigger(
                { listIndex, -1, list.GetData() }
            );

        ImGui::Separator();
        DrawAllCards(iter);

        if (ImGui::Button("Add Task", {ImGui::GetContentRegionAvail().x, 0.f}))
            m_openPromptHandler.Trigger(
                { listIndex, -1, std::optional<Card::Data>(std::nullopt) }
            );

        CreateCardDragDropTarget({listIndex, -1});
    }
    ImGui::EndChild();
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
    if (ImGui::BeginChild(std::to_string(itemIndex.card).c_str(),
         ImVec2(0.f, 100.f), childFlags, windowFlags)) {
        CreateCardDragDropSource(card, (Board::MoveData)itemIndex);

        ImGui::Text("%s", card.GetDataRef().title.c_str());

        if (ImGui::Button("Edit"))
            m_openPromptHandler.Trigger(
                { itemIndex.list, itemIndex.card, card.GetData() }
            );

        if (ImGui::Button("Delete"))
            m_deleteItemHandler.Trigger({itemIndex.list, itemIndex.card});
    }
    ImGui::EndChild();

    CreateCardDragDropTarget(itemIndex);
}

void BoardView::CreateCardDragDropSource(const Card& card, const BoardView::CardDragDropPayload& payload) {
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
        ImGui::SetDragDropPayload(
            ToString(PayloadType::CardDrag),
            &payload,
            sizeof(Board::MoveData));
            
        ImGui::Text("Moving: %s", card.GetDataRef().title.c_str());
        ImGui::EndDragDropSource();
    }
}

void BoardView::CreateCardDragDropTarget(const BoardView::CardDragDropPayload& destination) {
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(
                ToString(PayloadType::CardDrag))) {
            if (payload->DataSize == sizeof(Board::MoveData)) {
                auto *dragPayload = static_cast<const Board::MoveData *>(payload->Data);
                m_dragdropHandler.Trigger({ {dragPayload->list, dragPayload->card},
                     destination });
            }
        }
        ImGui::EndDragDropTarget();
    }
}