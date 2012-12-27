#include <SDL/SDL.h>
#include "randistrs.h"
#include "mtwist.h"

#include "buttons.h"

int main(int args, char *argv[]) {
    // Init
    mt_seed();

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    TTF_Init();
    TTF_Font* f = TTF_OpenFont("courier_noir.ttf", 40);

    SDL_Surface* screen;
    screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("Buttonset by Bob Rubbens", NULL);

    bool quit = false;
    int draw = 0;
    SDL_Event event;

    // cButton b(f, "TEST", 300, 300, B_MOUT, DIR_LEFT, 1000, SDL_MapRGB(screen->format, 0, 0, 0), SDL_MapRGB(screen->format, 128, 128, 128), screen->format);
    cButtonSet b(f, true, B_MIN, 100, 100, 50, 50, 1000, 500, DIR_LEFT, SDL_MapRGB(screen->format, 0, 0, 0), SDL_MapRGB(screen->format, 128, 128, 128), screen->format);

    b.addB("Add Button");
    b.addB("Quit");

    SDL_Rect t;
    t.x = 0;
    t.y = t.x;
    t.w = 10;
    t.h = t.w;

    std::string caption = "Move Out";

    // Game loop
    while (!quit) {
        // Input handling
        while (SDL_PollEvent(&event)) {
            b.handleEvents(&event);

            switch (event.type) {
                case SDL_QUIT: // User x's out
                    quit = true;
                    break;
                case SDL_KEYDOWN: // ESCAPE terminates program
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }
                    break;
            }
        }

        if (b.gPressed() == 1) {
            b.addB(caption);
            caption = "Move In";
        }

        if (b.gPressed() == 2) {
            quit = true;
        }

        if (b.gPressed() == 3) {
            b.moveOut();
        }

        if (b.gReleased() == 4) {
            b.moveIn();
        }

        // Logic
        b.logic();

        // Rendering
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

        b.render(screen);

        SDL_Flip(screen);
    }

    // Exit
    TTF_CloseFont(f);

    TTF_Quit();

    SDL_Quit();

    return 0;
}
