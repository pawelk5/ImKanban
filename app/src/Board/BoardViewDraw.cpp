#include "pch.h"
#include "Card.hpp"
#include "List.hpp"
#include "BoardView.hpp"
#include "utils/types.hpp"


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
            m_listPrompt.Open(std::nullopt, {-1});
    }
    ImGui::End();

    DrawListPrompt();
    DrawCardPrompt();
}

void BoardView::DrawAllLists() {
    auto &listRef = m_board->GetElementArray();

    for (auto it = listRef.begin(); it < listRef.end(); ++it) {
        const auto deleteCallback = 
            [this, it]() {
            DeleteItem({ m_board->AsIndex(it), -1 });
        };

        const auto promptCallback = 
            [this, it]()
        {
            OpenListPrompt(m_board->AsIndex(it), m_board->At(it)->GetData());
        };

        DrawList(it, deleteCallback, promptCallback);
        ImGui::SameLine();
    }
}

void BoardView::DrawList(Board::ElementArrayIterator iter, const Callback& deleteCallback,
        const Callback& openPromptCallback) {
    auto& list = *m_board->At(iter);
    const auto listIndex = m_board->AsIndex(iter);

    if (ImGui::BeginChild(std::to_string(listIndex).c_str(), m_listSize, childFlags, windowFlags)) {
        ImGui::Text("%s", list.GetDataRef().name.c_str());
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
            deleteCallback();
        ImGui::SameLine();
        if (ImGui::Button("Edit"))
            openPromptCallback();

        ImGui::Separator();
        DrawAllCards(iter);

        if (ImGui::Button("Add Task", {ImGui::GetContentRegionAvail().x, 0.f}))
            OpenCardPrompt(listIndex, -1, std::nullopt);

        CreateCardDragDropTarget({listIndex, -1});
    }
    ImGui::EndChild();
}

void BoardView::DrawAllCards(Board::ElementArrayIterator iter) {
    auto& list = *m_board->At(iter);
    const auto &cardsRef = list.GetElementArray();
    const int listIndex = m_board->AsIndex(iter);

    for (auto it = cardsRef.begin(); it < cardsRef.end(); ++it){
        const auto deleteCallback = 
            [this, &list, listIndex, it]()
        {
            DeleteItem({listIndex, list.AsIndex(it)});
        };

        const auto promptCallback = 
            [this, &list, listIndex, it]()
        {
            OpenCardPrompt(listIndex, list.AsIndex(it), list.At(it)->GetData());
        };
        
        DrawCard(*list.At(it), deleteCallback, promptCallback,
            { m_board->AsIndex(iter), list.AsIndex(it) });
    }
}

void BoardView::DrawCard(Card& card, const Callback& deleteCallback,
            const Callback& openPromptCallback, const Board::ItemIndex& itemIndex) {
    if (ImGui::BeginChild(std::to_string(itemIndex.card).c_str(),
         ImVec2(0.f, 100.f), childFlags, windowFlags)) {
        CreateCardDragDropSource(card, (Board::MoveData)itemIndex);

        ImGui::Text("%s", card.GetDataRef().title.c_str());

        if (ImGui::Button("Edit"))
            openPromptCallback();

        if (ImGui::Button("Delete"))
            deleteCallback();
    }
    ImGui::EndChild();

    CreateCardDragDropTarget(itemIndex);
}

void BoardView::DrawListPrompt()
{
    if (!m_listPrompt.IsOpen())
        return;
    
    const auto &promptContext = m_listPrompt.GetContextData();
    const auto submitCallback = [this, &promptContext](const ListData &listData)
    {
        if (promptContext.listIndex < 0)
            m_board->AddElement(List(listData));
        else
            m_board->At(promptContext.listIndex)->Update(listData);
    };
    m_listPrompt.Draw(submitCallback);
}

void BoardView::DrawCardPrompt()
{
    if (!m_cardPrompt.IsOpen())
        return;
    
    const auto &promptContext = m_cardPrompt.GetContextData();
    const auto &listRef = m_board->GetElementArray();
    auto &list = listRef.at(promptContext.list);

    const auto submitCallback =
        [&list, &promptContext](const Card::Data &cardData)
    {
        if (promptContext.card < 0)
            list->AddElement(Card(cardData));
        else
            list->At(promptContext.card)->Update(cardData);
    };

    m_cardPrompt.Draw(submitCallback);
}

void BoardView::CreateCardDragDropSource(const Card& card, const BoardView::CardDragDropPayload& payload) {
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
        ImGui::SetDragDropPayload(
            ToString(PayloadType::CardDrag).c_str(),
            &payload,
            sizeof(Board::MoveData));
            
        ImGui::Text("Moving: %s", card.GetDataRef().title.c_str());
        ImGui::EndDragDropSource();
    }
}

void BoardView::CreateCardDragDropTarget(const BoardView::CardDragDropPayload& destination) {
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(
                ToString(PayloadType::CardDrag).c_str())) {
            if (payload->DataSize == sizeof(Board::MoveData)) {
                auto *dragPayload = static_cast<const Board::MoveData *>(payload->Data);
                m_dragdropData = { {dragPayload->list, dragPayload->card},
                     destination };
            }
        }
        ImGui::EndDragDropTarget();
    }
}