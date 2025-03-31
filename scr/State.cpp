#include "SDL.h"
#include "../include/State.h"
#include <filesystem>
#include <iostream>

State::State() : quitRequested(false), bg("../Recursos/img/Background.png"), music("../Recursos/audio/BGM.wav") {
    // Inicialização do estado
	music.Play();
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
    bg.Render(0, 0);
}
