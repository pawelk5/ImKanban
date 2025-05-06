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
    auto &listRef = m_board->GetElementArray();

    const float windowSize = (float)target.getSize().x / 1.5f;
    ImGui::SetNextWindowSize({windowSize, (float)target.getSize().y});
    ImGui::SetNextWindowPos({0.f, 0.f});
    if (ImGui::Begin(m_board->GetDataRef().name.c_str(), nullptr, boardWindowFlags)) {
        for (auto it = listRef.begin(); it < listRef.end(); ++it) {
            const auto deleteCallback = [this, it]() {
                m_board->RemoveElement(it);
            };

            DrawList(*(*it), deleteCallback,
                     {(int)std::distance(listRef.begin(), it)});
            ImGui::SameLine();
        }
        if (ImGui::Button("Add List", m_listSize))
            m_listPrompt.Open(std::nullopt, {-1});
    }
    ImGui::End();

    DrawListPrompt();
    DrawCardPrompt();
}

void BoardView::DrawList(List& list, const DeleteCallback& callback, const ListPromptContext &promptContext) {
    bool deleteButtonPressed = false;
    const auto &cardsRef = list.GetElementArray();

    if (ImGui::BeginChild(std::to_string(promptContext.listIndex).c_str(), m_listSize, childFlags, windowFlags)) {
        ImGui::Text("%s", list.GetDataRef().name.c_str());
        ImGui::SameLine();
        deleteButtonPressed = ImGui::Button("Delete");
        ImGui::SameLine();
        if (ImGui::Button("Edit"))
            m_listPrompt.Open(list.GetData(), promptContext);

        ImGui::Separator();
        for (auto it = cardsRef.begin(); it < cardsRef.end(); ++it){
            const auto deleteCallback = [&list, it]()
            {
                list.RemoveElement(it);
            };
            
            DrawCard(*(*it), deleteCallback, 
                {promptContext.listIndex, (int)std::distance(cardsRef.begin(), it)});
        }

        if (ImGui::Button("Add Task", {ImGui::GetContentRegionAvail().x, 0.f}))
            m_cardPrompt.Open(std::nullopt, {promptContext.listIndex, -1});


        CreateCardDragDropTarget({promptContext.listIndex, -1});
    }
    ImGui::EndChild();

    if (deleteButtonPressed)
        callback();
}

void BoardView::DrawCard(Card& card, const DeleteCallback& callback, const CardPromptContext &promptContext) {
    bool deleteButtonPressed = false;
    if (ImGui::BeginChild(std::to_string(promptContext.cardIndex).c_str(), ImVec2(0.f, 100.f), childFlags, windowFlags))
    {
        CreateCardDragDropSource(card, {promptContext.listIndex, promptContext.cardIndex});

        ImGui::Text("%s", card.GetTitle().c_str());

        if (ImGui::Button("Edit"))
            m_cardPrompt.Open(card.GetData(), promptContext);

        deleteButtonPressed = ImGui::Button("Delete");
    }
    ImGui::EndChild();

    CreateCardDragDropTarget({promptContext.listIndex, promptContext.cardIndex});

    if (deleteButtonPressed)
        callback();
}

void BoardView::DrawListPrompt()
{
    if (m_listPrompt.IsOpen())
    {
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
}

void BoardView::DrawCardPrompt()
{
    if (m_cardPrompt.IsOpen())
    {
        const auto &promptContext = m_cardPrompt.GetContextData();
        const auto &listRef = m_board->GetElementArray();
        auto &list = listRef.at(promptContext.listIndex);

        const auto submitCallback =
            [&list, &promptContext](const Card::Data &cardData)
        {
            if (promptContext.cardIndex < 0)
                list->AddElement(Card(cardData));
            else
                list->At(promptContext.cardIndex)->Update(cardData);
        };

        m_cardPrompt.Draw(submitCallback);
    }
}

void BoardView::CreateCardDragDropSource(const Card& card, const BoardView::CardDragDropPayload& payload) {
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
        ImGui::SetDragDropPayload(
            ToString(PayloadType::CardDrag).c_str(),
            &payload,
            sizeof(CardPromptContext));
            
        ImGui::Text("Moving: %s", card.GetTitle().c_str());
        ImGui::EndDragDropSource();
    }
}

void BoardView::CreateCardDragDropTarget(const BoardView::CardDragDropPayload& destination) {
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(
                ToString(PayloadType::CardDrag).c_str())) {
            if (payload->DataSize == sizeof(CardPromptContext)) {
                auto *dragPayload = static_cast<const CardPromptContext *>(payload->Data);
                m_dragdropData = { {dragPayload->listIndex, dragPayload->cardIndex},
                     destination };
            }
        }
        ImGui::EndDragDropTarget();
    }
}