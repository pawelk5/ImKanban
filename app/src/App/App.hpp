#pragma once

class App {
public:
    static App& Get();
    App(App const&) = delete;
    void operator=(App const&) = delete;


    void Run();
private:
    App();
    ~App();

private:
    void InitWindow();

private:
    void EventUpdate();
    void Update();
    void Draw();
    
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
};