#include "../include/Game.h"
#include "../include/State.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

Game* Game::instance = nullptr;

Game::Game(const string& title, int width, int height) {
    if (instance != nullptr) {
        cerr << "Erro: Jogo já instanciado." << endl;
        exit(1);
    }
    instance = this;

    // Iniciando SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        cerr << "Erro ao inicializar SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    // Iniciando SDL_image
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        cerr << "Erro ao inicializar SDL_image: " << IMG_GetError() << endl;
        exit(1);
    }

    // Iniciando SDL_mixer
    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID | MIX_INIT_WAVPACK) == 0) {
        cerr << "Erro ao inicializar SDL_mixer: " << Mix_GetError() << endl;
        exit(1);
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        cerr << "Erro ao abrir áudio: " << Mix_GetError() << endl;
        exit(1);
    }
    Mix_AllocateChannels(32);

    // Criando janela
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        cerr << "Erro ao criar janela: " << SDL_GetError() << endl;
        exit(1);
    }

    // Criando renderizador
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Erro ao criar renderizador: " << SDL_GetError() << endl;
        exit(1);
    }

    state = new State();
}

Game::~Game() {
    // Deletar o estado
    delete state;

    // Destruir o renderizador
    SDL_DestroyRenderer(renderer);

    // Destruir a janela
    SDL_DestroyWindow(window);

    // Fechar áudio
    Mix_CloseAudio();

    // Encerrar SDL_mixer
    Mix_Quit();

    // Encerrar SDL_image
    IMG_Quit();

    // Encerrar SDL
    SDL_Quit();
}

State& Game::GetState() {
    return *state;
}

void Game::Run() {
    while (!state->QuitRequested()) {
        state->Update(0); // Atualizar o estado com base no tempo delta (dt)
        state->Render();  // Renderizar o estado (bg e outros elementos)
        SDL_RenderPresent(renderer); // Atualizar a tela com as últimas renderizações feitas
        SDL_Delay(33); // Atrasar o processamento do próximo frame em 33 milissegundos
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

Game& Game::GetInstance(const string& title, int width, int height) {
    if (instance == nullptr) {
        instance = new Game(title, width, height);
    }
    return *instance;
}
