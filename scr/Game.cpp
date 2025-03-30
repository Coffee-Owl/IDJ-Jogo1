#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "../include/Game.h"
//#include "State.h" // Inclua o arquivo de cabeçalho do State

Game* Game::instance = nullptr;

Game::Game(const std::string& title, int width, int height) {
    if (instance != nullptr) {
        std::cerr << "Erro: Jogo já instanciado." << std::endl;
        exit(1);
    }
    instance = this;

    // Iniciando SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Iniciando SDL_image
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        std::cerr << "Erro ao inicializar SDL_image: " << IMG_GetError() << std::endl;
        exit(1);
    }

    // Iniciando SDL_mixer
    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID) == 0) {
        std::cerr << "Erro ao inicializar SDL_mixer: " << Mix_GetError() << std::endl;
        exit(1);
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cerr << "Erro ao abrir áudio: " << Mix_GetError() << std::endl;
        exit(1);
    }
    Mix_AllocateChannels(32);

    // Criando janela
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Criando renderizador
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erro ao criar renderizador: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // state = new State(); // Inicialize o estado conforme necessário
}

Game::~Game() {
    // Deletar o estado
    //delete state;

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
    // Implementação do loop principal do jogo
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

Game& Game::GetInstance(const std::string& title, int width, int height) {
    if (instance == nullptr) {
        instance = new Game(title, width, height);
    }
    return *instance;
}

int main(int argc, char* argv[]) {
    Game& game = Game::GetInstance("Meu Jogo", 800, 600);
    game.Run();
    return 0;
}
