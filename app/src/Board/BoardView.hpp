#pragma once
#include "ListPrompt/ListPrompt.hpp"
#include "CardPrompt/CardPrompt.hpp"
#include "Core/View/ViewBase.hpp"
#include "Core/EventHandler/EventHandler.hpp"
#include "Board.hpp"

/// View displaying a board's content
class BoardView : public ViewBase {
private:
    /// Type alias for drag and drop payloads
    using CardDragDropPayload = Board::MoveData;

    /// Type alias for board shared pointer
    using BoardPointer = std::shared_ptr<Board>;

public:
    /// Constructs a new board view with a board
    /// \param pointer board to be displayed
    BoardView(const BoardPointer& pointer);

    /// Draw function to be called every frame
    /// \param target SFML render target
    void Draw(sf::RenderTarget& target) override;

    /// Update function to be called every frame
    /// \param deltaTime time passed since last frame
    void Update(float deltaTime) override;

    /// Event Update function to be called every time a SFML event took place
    /// \param event SFML event
    void EventUpdate(const sf::Event& event) override;

private:
    /// Pointer to current board
    BoardPointer m_board;

    /// Prompt for editing or adding lists
    ListPrompt m_listPrompt;

    /// Prompt for editing or adding cards
    CardPrompt m_cardPrompt;

    /// Size of list window (updated every frame in the beginning of the Draw function)
    /// (TODO: make this more dynamic)
    ImVec2 m_listSize;
    
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
    struct CardDragDropData {
        CardDragDropPayload source;
        CardDragDropPayload destination;
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
    };

// event handlers
private:
    /// Drag and drop event handler
    EventHandler<CardDragDropData> m_dragdropHandler;

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
    /// Creates ImGui drag and drop source for a card
    void CreateCardDragDropSource(const Card& card, const CardDragDropPayload& payload);

    /// Creates ImGui drag and drop target for a card
    void CreateCardDragDropTarget(const CardDragDropPayload& destination); 

};