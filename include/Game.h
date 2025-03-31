#pragma once

#include <string>
#include <SDL.h>

class State;

class Game {
public:
    static Game& GetInstance(const std::string& title = "Default Title", int width = 800, int height = 600);
    ~Game();

    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();

private:
    Game(const std::string& title, int width, int height);

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};