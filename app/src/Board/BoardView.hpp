#pragma once
#include "DeleteItemPrompt/DeleteItemPrompt.hpp"
#include "ListPrompt/ListPrompt.hpp"
#include "CardPrompt/CardPrompt.hpp"
#include "Core/View/ViewBase.hpp"
#include "Core/EventHandler/EventHandler.hpp"
#include "Board.hpp"

/// View displaying a board's content
class BoardView : public ViewBase {
private:
    /// Type alias for drag and drop payloads
    using DragDropPayload = Board::MoveData;

    /// Type alias for board shared pointer
    using BoardPointer = std::shared_ptr<Board>;

public:
    /// Constructs a new board view with a board
    /// \param pointer board to be displayed
    explicit BoardView(const BoardPointer& pointer);

    /// Draw board in the main container
    /// \param target SFML render target
    void DrawContent(sf::RenderTarget& target) override;

    /// Draw main container header
    void DrawHeader();

    /// Draw sidebar content
    /// \param target SFML render target to draw on
    void DrawSidebar(sf::RenderTarget& target) override;

    /// Draw popups
    /// \param target SFML render target to draw on
    void DrawImpl(sf::RenderTarget& target) override;

    /// Update function to be called every frame
    /// \param deltaTime time passed since last frame
    void Update(float deltaTime) override;

    /// Event Update function to be called every time a SFML event took place
    /// \param event SFML event
    void EventUpdate(const sf::Event& event) override;

    /// Check if the app should return to main view
    bool GoToMainView();

private:
    /// Pointer to current board
    BoardPointer m_board;

    /// Prompt for editing or adding lists
    ListPrompt m_listPrompt;

    /// Prompt for editing or adding cards
    CardPrompt m_cardPrompt;

    /// Confirm prompt for deleting items
    /// Uses int to satisfy template requirements
    DeleteItemPrompt m_deleteItemPrompt;

    /// Size of list window (updated every frame in the beginning of the Draw function)
    /// (TODO: make this more dynamic)
    ImVec2 m_listSize;
    
    /// flag to check if the app should return to main view
    bool m_returnToMainView;

private:
    /// Draws all lists of a board
    void DrawAllLists();

    /// Draws all cards of a list
    /// \param iter iterator of a list
    void DrawAllCards(Board::ElementArrayIterator iter);

    /// Draws a single list
    /// \param iter iterator of a list
    void DrawList(Board::ElementArrayIterator iter);

    /// Draws a single card
    /// \param card the card to draw
    /// \param itemIndex index of list and card
    void DrawCard(Card& card, const Board::ItemIndex& itemIndex);


// EVENT HANDLERS
private:
    /// Struct with drag and drop data
    struct DragDropData {
        DragDropPayload source;
        DragDropPayload destination;
    };

    /// Struct for opening both List and Card prompts
    struct OpenPromptData {
        Board::ItemIndex index;

        /// Optional data to be edited (if nullopt then creates a new card/list)
        std::variant<std::optional<ListData>, std::optional<CardData>> promptData;
    };

    /// Struct for deleting items
    struct DeleteItemData {
        Board::ItemIndex index;
        
        explicit DeleteItemData(Board::ItemIndex index)
            :index(index)
        { ; }

    };

// event handlers
private:
    /// Drag and drop event handler
    EventHandler<DragDropData> m_dragdropHandler;

    /// Open prompt event handler (for both lists and cards)
    EventHandler<OpenPromptData> m_openPromptHandler;

    /// Delete item event handler
    EventHandler<DeleteItemData> m_deleteItemHandler;

private:
    /// Set up all callbacks for event handlers
    void SetUpEventHandlers();

    /// Set up all callbacks for prompts
    void SetUpPromptCallbacks();

// DRAG AND DROP STUFF
private:
    /// Calls HandleDragDropSource and draws card-specific tooltip
    /// \param card the card to be moved (also for drawing tooltips)
    /// \param payload drag and drop payload (index of the card)
    void CreateDragDropSource(const Card& card,
            const DragDropPayload& payload);

    /// Calls HandleDragDropSource and draws list-specific tooltip
    /// \param list the list to be moved (also for drawing tooltips)
    /// \param payload drag and drop payload (index of the list)
    void CreateDragDropSource(const List& list,
            const DragDropPayload& payload);
    
    /// Creates ImGui drag and drop source for cards and lists
    /// \param payloadType type of drag and drop payload (list/card)
    /// \param payload index of the element
    /// \param drawTooltip function for drawing tooltips (NOTE: highly recommended to use lambda function)
    void HandleDragDropSource(UI::PayloadType payloadType,
        const DragDropPayload& payload, const std::function<void()>& drawTooltip);

    /// Creates ImGui drag and drop target for cards and lists
    /// \param destination destination index where dragged item will be dropped
    /// \param payloadType drag and drop target type (list/card)
    void CreateDragDropTarget(const DragDropPayload& destination, UI::PayloadType payloadType);
};