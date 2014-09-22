#include <vector>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "pointers.hh"
#include "config.hh"
#include "ProgramObject.hh"

using namespace std;

string base_path, pref_path;

void init() {
    // SDL_INIT_TIMER          timer subsystem
    // SDL_INIT_AUDIO          audio subsystem
    // SDL_INIT_VIDEO          video subsystem
    // SDL_INIT_JOYSTICK       joystick subsystem
    // SDL_INIT_HAPTIC         haptic (force feedback) subsystem
    // SDL_INIT_GAMECONTROLLER controller subsystem
    // SDL_INIT_EVENTS         events subsystem
    // SDL_INIT_EVERYTHING     all of the above subsystems
    // SDL_INIT_NOPARACHUTE    don't catch fatal signals
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);

    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG /*|IMG_INIT_TIF*/;
    if ( (IMG_Init(img_flags) & img_flags) != img_flags ) {
        cerr << "IMG_Init: Failed to init required image support!\n";
        cerr << "IMG_Init: " << IMG_GetError() << endl;
        exit(EXIT_FAILURE);
    }
    atexit(IMG_Quit);

    if(TTF_Init()==-1) {
        cerr << "TTF_Init: " << TTF_GetError() << endl;
        exit(EXIT_FAILURE);
    }
    atexit(TTF_Quit);

    base_path = SDL_GetBasePath();
    pref_path = SDL_GetPrefPath(ORGANIZATION, APPLICATION);
}


int main(int argc, char *argv[]) {
    init();

    vector<string> args(argv, argv+argc);
    for (string& arg: args) {
        cout << "unused parameter: " << arg << endl;
    }

    ProgramObject pg;
    pg.MainLoop();

    return EXIT_SUCCESS;
}
