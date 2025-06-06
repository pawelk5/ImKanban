#include "Core/ViewNavigation/ViewNavigation.hpp"
#include "Core/Utils/Constants.hpp"
#include "Core/Widgets/Widgets.hpp"
#include "pch.h"
#include "Core/Utils/Style.hpp"
#include "Card.hpp"
#include "List.hpp"
#include "BoardView.hpp"
#include "App/App.hpp"

void BoardView::DrawSidebar(sf::RenderTarget &target)
{
    Style::WithFont(App::Settings().GetFont(+2),
                    [this]()
                    {
                        ImGui::Text("Side bar!");
                        ImGui::Separator();

                        if (ImGui::Button(ICON_FA_ARROW_LEFT " Return",
                                          ImVec2{ImGui::GetContentRegionAvail().x, 2 * ImGui::GetTextLineHeightWithSpacing()})){
                                            m_board->saveToFile();
                            m_viewNavigation = OpenMainView();
                    } });
}

void BoardView::DrawImpl(sf::RenderTarget &target)
{
    m_deleteItemPrompt.Draw(target);
    m_listPrompt.Draw(target);
    m_cardPrompt.Draw(target);
    m_subtaskPrompt.Draw(target);
    m_fullCardView.Draw(target);
}

void BoardView::DrawContent(sf::RenderTarget &target)
{
    DrawHeader();
    ImGui::Separator();
    if (ImGui::BeginChild("##board-container", ImGui::GetContentRegionAvail(),
                          UIFlags::childFlags, UIFlags::contentWindowFlags))
    {
        m_listSize.x = std::max(
            (ImGui::GetContentRegionAvail().x - 4 * ImGui::GetStyle().ItemSpacing.x) / 4, 400.f);

        DrawAllLists();
        if (ImGui::Button(Labels::addListLabel, m_listSize))
            m_openPromptHandler.Trigger(
                OpenPromptData{Board::ItemIndex{-1, -1},
                               std::optional<ListData>(std::nullopt)});

        /// drag drop target for list (add list button)
        CreateDragDropTarget({-1, -1}, UI::PayloadType::ListDrag);
    }
    ImGui::EndChild();
}

void BoardView::DrawHeader()
{
    Style::WithFont(App::Settings().GetFont(+2),
                    [this]()
                    {
                        ImGui::Text("Board: %s", m_board->GetDataRef().name.c_str());
                    });
}

void BoardView::DrawAllLists()
{
    auto &listRef = m_board->GetElementArray();

    for (auto it = listRef.begin(); it < listRef.end(); ++it)
    {
        DrawList(it);
        ImGui::SameLine();
    }
}

void BoardView::DrawList(Board::ElementArrayIterator iter)
{
    auto &list = *m_board->At(iter);
    const auto listIndex = m_board->AsIndex(iter);

    if (!ImGui::BeginChild(std::to_string(listIndex).c_str(), m_listSize,
                           UIFlags::childFlags, UIFlags::windowFlags))
        return ImGui::EndChild();

    ImVec2 currentPos, buttonSize;
    /// drag drop source for list
    CreateDragDropSource(list, Board::MoveData{listIndex, -1});
    Style::WithFont(App::Settings().GetFont(+1),
                    [&]()
                    {
                        ImGui::Text("%s", list.GetDataRef().name.c_str());

                        buttonSize = Widgets::GetHamburgerMenuSize();
                        Widgets::AlignNextItemTopRight(buttonSize);
                        currentPos = ImGui::GetCursorScreenPos();
                        if (Widgets::HamburgerMenu())
                            ImGui::OpenPopup("listHamburgerMenu");
                    });

    ImGui::SetNextWindowPos({currentPos.x + buttonSize.x / 2.f, currentPos.y + buttonSize.y / 2.f});
    if (ImGui::BeginPopupContextWindow("listHamburgerMenu"))
    {
        if (ImGui::Button(Labels::deleteItemLabel))
            m_deleteItemHandler.Trigger(DeleteItemData{{listIndex, -1}});

        if (ImGui::Button(Labels::editItemLabel))
            m_openPromptHandler.Trigger(
                OpenPromptData{Board::ItemIndex{listIndex, -1}, list.GetData()});

        ImGui::EndPopup();
    }

    ImGui::Separator();
    DrawAllCards(iter);

    if (ImGui::Button(Labels::addTaskLabel, {ImGui::GetContentRegionAvail().x, 0.f}))
        m_openPromptHandler.Trigger(
            OpenPromptData{Board::ItemIndex{listIndex, -1},
                           std::optional<CardData>(std::nullopt)});

    /// drag drop target for cards (add task button)
    CreateDragDropTarget({listIndex, -1}, UI::PayloadType::CardDrag);
    ImGui::EndChild();

    /// drag drop target for list
    CreateDragDropTarget({listIndex, -1}, UI::PayloadType::ListDrag);
}

void BoardView::DrawAllCards(Board::ElementArrayIterator iter)
{
    auto &list = *m_board->At(iter);
    const auto &cardsRef = list.GetElementArray();
    const int listIndex = m_board->AsIndex(iter);

    for (auto it = cardsRef.begin(); it < cardsRef.end(); ++it)
    {
        DrawCard(*list.At(it),
                 {m_board->AsIndex(iter), list.AsIndex(it)});
    }
}

void BoardView::DrawCard(Card &card, const Board::ItemIndex &itemIndex)
{
    if (!ImGui::BeginChild(std::to_string(itemIndex.card).c_str(),
                           ImVec2(0.f, 100.f), UIFlags::childFlags, UIFlags::windowFlags))
        return ImGui::EndChild();

    /// drag drop source for card
    CreateDragDropSource(card, (Board::MoveData)itemIndex);

    ImGui::Text("%s", card.GetDataRef().title.c_str());

    // TODO: create component for clickable text
    ImGui::TextUnformatted(card.GetDataRef().title.c_str());
    if (ImGui::IsItemHovered())
    {
        ImVec2 min = ImGui::GetItemRectMin();
        ImVec2 max = ImGui::GetItemRectMax();
        ImGui::GetWindowDrawList()->AddLine(
            ImVec2(min.x, max.y), ImVec2(max.x, max.y),
            ImGui::GetColorU32(ImGuiCol_Text), 1.0f);
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            // Handle click event: open full card view
            m_openPromptHandler.Trigger(
                OpenPromptData{Board::ItemIndex{itemIndex.list, itemIndex.card},
                               std::optional<FullCardViewData>(FullCardViewData{selectedCard : &card})});
        }
    }
    ImGui::Text("Completed: %s", card.GetDataRef().isCompleted ? "yes" : "no");                   // TODO check icon here
    ImGui::Text("Subtasks: %d/%d", card.CountCompletedSubtasks(), card.GetElementArray().size()); // TODO check icon here

    ImVec2 currentPos, buttonSize;

    buttonSize = Widgets::GetHamburgerMenuSize();
    Widgets::AlignNextItemTopRight(buttonSize);
    currentPos = ImGui::GetCursorScreenPos();
    if (Widgets::HamburgerMenu())
        ImGui::OpenPopup("cardHamburgerMenu");

    ImGui::SetNextWindowPos({currentPos.x + buttonSize.x / 2.f, currentPos.y + buttonSize.y / 2.f});
    if (ImGui::BeginPopupContextWindow("cardHamburgerMenu"))
    {
        if (ImGui::Button("View"))
        {
            m_openPromptHandler.Trigger(
                OpenPromptData{Board::ItemIndex{itemIndex.list, itemIndex.card},
                               std::optional<FullCardViewData>(FullCardViewData{selectedCard : &card})});
        }
        if (ImGui::Button(Labels::editItemLabel))
            m_openPromptHandler.Trigger(
                OpenPromptData{itemIndex, card.GetData()});

        if (ImGui::Button(Labels::deleteItemLabel))
            m_deleteItemHandler.Trigger((DeleteItemData)itemIndex);

        ImGui::EndPopup();
    }

    ImGui::EndChild();

    /// drag drop target for card
    CreateDragDropTarget(itemIndex, UI::PayloadType::CardDrag);
}

void BoardView::CreateDragDropSource(const Card &card, const DragDropPayload &payload)
{
    HandleDragDropSource(UI::PayloadType::CardDrag,
                         payload, [&card]()
                         { ImGui::Text("Moving card: %s", card.GetDataRef().title.c_str()); });
}

void BoardView::CreateDragDropSource(const List &list, const DragDropPayload &payload)
{
    HandleDragDropSource(UI::PayloadType::ListDrag,
                         payload, [&list]()
                         { ImGui::Text("Moving list: %s", list.GetDataRef().name.c_str()); });
}

void BoardView::HandleDragDropSource(UI::PayloadType payloadType, const DragDropPayload &payload, const std::function<void()> &drawTooltip)
{
    /// NOTE: this works becouse EndDragDropSource needs to be called only if BeginDragDropSource returned true
    if (!ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
        return;

    ImGui::SetDragDropPayload(
        UI::ToString(payloadType),
        &payload,
        sizeof(Board::MoveData));

    drawTooltip();
    ImGui::EndDragDropSource();
}

void BoardView::CreateDragDropTarget(const DragDropPayload &destination, UI::PayloadType payloadType)
{
    /// NOTE: this works because EndDragDropTarget needs to be called only if BeginDragDropTarget returned true
    if (!ImGui::BeginDragDropTarget())
        return;

    if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(UI::ToString(payloadType)))
    {
        if (payload->DataSize == sizeof(Board::MoveData))
        {
            auto *dragPayload = static_cast<const Board::MoveData *>(payload->Data);
            m_dragdropHandler.Trigger(DragDropData{*dragPayload, destination});
        }
    }

    ImGui::EndDragDropTarget();
}