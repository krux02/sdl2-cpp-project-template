#include "ProgramObject.hh"
#include <iostream>

using std::cerr;
using std::endl;

void ProgramObject::Quit() {
    state = ProgramState::Quit;
}

bool ProgramObject::ProcessEvent(const SDL_Event &event) {
    switch (event.type) {
    case SDL_QUIT:
        Quit();
        return true;
    case SDL_KEYDOWN:
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            Quit();
            return true;
        } else {
            return false;
        }
    case SDL_MOUSEBUTTONDOWN:
        PlaySound();
    default:
        return false;
    }
}

void ProgramObject::MainLoop() {
    StartMusic();

    while (state != ProgramState::Quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ProcessEvent(event);
        }

        // clear screen
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
        SDL_RenderClear(renderer.get());

        Update();
        Render();

        // make things visible
        SDL_RenderPresent(renderer.get());
    }
}

void ProgramObject::Update() {
    // insert code here
}

void ProgramObject::Render() const {
    // insert code here

    SDL_Renderer* r = renderer.get();
    SDL_SetRenderDrawColor(r, 255,255,255,255);
    SDL_RenderDrawLine(r, 100,100,200,200);
    SDL_RenderDrawLine(r, 200,200,150,250);
    SDL_RenderDrawLine(r, 150,250,100,200);
    SDL_RenderDrawLine(r, 100,200,200,100);
    SDL_RenderDrawLine(r, 200,100,200,200);
    SDL_RenderDrawLine(r, 200,200,100,200);
    SDL_RenderDrawLine(r, 100,200,100,100);
    SDL_RenderDrawLine(r, 100,100,200,100);

    text_renderer.RenderBaked(sample_text_object, glm::ivec2(100,250));
    text_renderer.RenderDirect("direct Hello World!", glm::ivec2(100,282));

}

void ProgramObject::PlaySound() {
    Mix_PlayChannel(0,sample_chunk.get(),0);
}

void ProgramObject::StartMusic() {
    // -1 for infinite loop
    Mix_PlayMusic(sample_music.get(), -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}
