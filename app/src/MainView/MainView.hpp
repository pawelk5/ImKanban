#pragma once
#include "Core/View/ViewBase.hpp"
#include "Core/EventHandler/EventHandler.hpp"
#include "MainView/BoardPrompt/BoardPrompt.hpp"

/// View displaying a board's content
class MainView : public ViewBase {
public:
    /// Constructs main view
    explicit MainView(std::shared_ptr<BoardList> boardList);

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

    /// Returns current view navigation state
    ViewNavigation GetState() override;

private:
    /// View navigation state
    ViewNavigation m_viewNavigation;

    /// List of boards
    std::shared_ptr<BoardList> m_boardList;

    /// Prompt for editing or adding boards
    BoardPrompt m_boardPrompt;
    
private:
    /// Struct containing data for editing and adding new boards
    struct BoardPromptEventData {
        std::optional<BoardData> boardData;
        BoardPromptContext context;
    };

    /// Board add and edit event handler
    EventHandler<BoardPromptEventData> m_boardPromptHandler;

    /// Struct containing data for deleting boards
    struct DeleteBoardData {
        int index;
    };

    /// Board delete event handler
    EventHandler<DeleteBoardData> m_deleteBoardHandler;
private:
    /// Draws a single list
    /// \param iter iterator of a list
    void DrawBoards(int boardsPerRow, float width);
};