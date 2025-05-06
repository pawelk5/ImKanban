#include "pch.h"
#include "Card.hpp"
#include "Board/CardPrompt/CardPrompt.hpp"
#include "List.hpp"
#include <imgui.h>
#include "BoardView.hpp"
#include "utils/types.hpp"

BoardView::BoardView(const BoardView::BoardPointer &pointer)
    : m_board(pointer)
{
    auto &listRef = m_board->GetListsRef();
}

void BoardView::Update(float deltaTime) { ; }
void BoardView::EventUpdate(const sf::Event &event) { ; }

static constexpr int windowFlags =
    ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

static constexpr int boardWindowFlags =
    windowFlags | ImGuiWindowFlags_HorizontalScrollbar;

static constexpr int childFlags =
    ImGuiChildFlags_FrameStyle | ImGuiChildFlags_Borders;

void BoardView::Draw(sf::RenderTarget &target)
{
    auto &listRef = m_board->GetListsRef();
    const ImVec2 listSize = {250.f, 0.f};

    const float windowSize = (float)target.getSize().x / 1.5f;
    ImGui::SetNextWindowSize({windowSize, (float)target.getSize().y});
    ImGui::SetNextWindowPos({0.f, 0.f});
    if (ImGui::Begin(m_board->GetName().c_str(), nullptr, boardWindowFlags))
    {

        for (auto it = listRef.begin(); it < listRef.end(); ++it)
        {
            const auto deleteCallback = [this, it]()
            {
                m_board->RemoveList(it);
            };

            DrawList(*(*it), listSize, deleteCallback,
                     {(int)std::distance(listRef.begin(), it)});
            ImGui::SameLine();
        }
        if (ImGui::Button("Add List", listSize))
            m_listPrompt.Open(std::nullopt, {-1});
    }
    ImGui::End();

    DrawListPrompt();
    DrawCardPrompt();
}

void BoardView::DrawList(List &list, const ImVec2 &listSize, const DeleteCallback &callback, const ListPromptContext &promptContext)
{
    auto &cardsRef = list.GetCardsRef();
    bool deleteButtonPressed = false;

    if (ImGui::BeginChild(std::to_string(promptContext.listIndex).c_str(), listSize, childFlags, windowFlags))
    {
        ImGui::Text("%s", list.GetName().c_str());
        ImGui::SameLine();
        deleteButtonPressed = ImGui::Button("Delete");
        ImGui::SameLine();
        if (ImGui::Button("Edit"))
            m_listPrompt.Open(list.GetData(), promptContext);

        ImGui::Separator();
        for (auto it = cardsRef.begin(); it < cardsRef.end(); ++it)
        {
            const auto deleteCallback = [&list, it]()
            {
                list.RemoveCard(it);
            };

            // Negative value of DrawCard indicates that list content changed, and "it" is no longer valid
            if(!DrawCard(*(*it), deleteCallback, {promptContext.listIndex, (int)std::distance(cardsRef.begin(), it)}))
                break;
        }

        if (ImGui::Button("Add Task", {ImGui::GetContentRegionAvail().x, 0.f}))
            m_cardPrompt.Open(std::nullopt, {promptContext.listIndex, -1});

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(
                    ToString(PayloadType::CardDrag).c_str()))
            {
                if (payload->DataSize == sizeof(CardPromptContext))
                {
                    auto *dragPayload = static_cast<const CardPromptContext *>(payload->Data);
                    m_board->MoveCard(
                        m_board->GetListsRef().begin() + dragPayload->listIndex,
                        m_board->GetListsRef().at(dragPayload->listIndex)->GetCardsRef().begin() + dragPayload->cardIndex,
                        m_board->GetListsRef().begin() + promptContext.listIndex);
                }
            }
            ImGui::EndDragDropTarget();
        }
    }
    ImGui::EndChild();

    if (deleteButtonPressed)
        callback();
}

int BoardView::DrawCard(Card &card, const DeleteCallback &callback, const CardPromptContext &promptContext)
{
    bool deleteButtonPressed = false;

    if (ImGui::BeginChild(std::to_string(promptContext.cardIndex).c_str(), ImVec2(0.f, 100.f), childFlags, windowFlags))
    {

        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
        {
            ImGui::SetDragDropPayload(
                ToString(PayloadType::CardDrag).c_str(),
                &promptContext,
                sizeof(CardPromptContext));
            ImGui::Text("Moving: %s", card.GetTitle().c_str());
            ImGui::EndDragDropSource();
        }

        ImGui::Text("%s", card.GetTitle().c_str());

        if (ImGui::Button("Edit"))
            m_cardPrompt.Open(card.GetData(), promptContext);

        deleteButtonPressed = ImGui::Button("Delete");
    }
    ImGui::EndChild();

    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(
                ToString(PayloadType::CardDrag).c_str()))
        {
            if (payload->DataSize == sizeof(CardPromptContext))
            {
                auto *dragPayload = static_cast<const CardPromptContext *>(payload->Data);
                m_board->MoveCard(
                    m_board->GetListsRef().begin() + dragPayload->listIndex,
                    m_board->GetListsRef().at(dragPayload->listIndex)->GetCardsRef().begin() + dragPayload->cardIndex,
                    m_board->GetListsRef().begin() + promptContext.listIndex,
                    promptContext.cardIndex);
                return false;
            }
        }
        ImGui::EndDragDropTarget();
    }

    if (deleteButtonPressed)
        callback();
    return true;
}

void BoardView::DrawListPrompt()
{
    if (m_listPrompt.IsOpen())
    {
        const auto &promptContext = m_listPrompt.GetContextData();
        const auto submitCallback = [this, &promptContext](const List::Data &listData)
        {
            if (promptContext.listIndex < 0)
                m_board->AddList(List(listData));
            else
                m_board->GetListsRef().at(promptContext.listIndex)->Update(listData);
        };

        m_listPrompt.Draw(submitCallback);
    }
}

void BoardView::DrawCardPrompt()
{
    if (m_cardPrompt.IsOpen())
    {
        const auto &promptContext = m_cardPrompt.GetContextData();
        auto &listRef = m_board->GetListsRef();
        auto &list = listRef.at(promptContext.listIndex);

        const auto submitCallback =
            [&list, &promptContext](const Card::Data &cardData)
        {
            if (promptContext.cardIndex < 0)
                list->AddCard(Card(cardData));
            else
                list->GetCardsRef().at(promptContext.cardIndex)->Update(cardData);
        };

        m_cardPrompt.Draw(submitCallback);
    }
}