#include "SDL.h"
#include "../include/State.h"

State::State() : quitRequested(false) /*, bg() */ {
    // Inicialização do estado
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    // Carregar os assets (bg e music)
}

void State::Update(float dt) {
    // Atualizar o estado com base no tempo delta (dt)
    if (SDL_QuitRequested()) {
		quitRequested = true;
    }
}

void State::Render() {
    // Renderizar o estado (bg e outros elementos)
    // bg.Render(0, 0);
}
