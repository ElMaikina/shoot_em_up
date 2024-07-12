#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#include "player.h"
 
int main(int argc, char *argv[])
{
    int winw = 640;
    int winh = 360;
    int framerate = 120;

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("Platform Game", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       winw, 
                                       winh, 
                                       0);
    // set the window to fullscreen
    //SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // create the main player
    Player *player = createPlayer(rend, winw, winh);

    // controls animation loop
    int close = 0;
 
    // animation loop
    while (!close) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) {
                printf("Exiting game...");
                close = 1;
                return 0;
            }
        }
        // manages player movement
        movePlayer(player);
        
        // clears the screen
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, player->tex, NULL, &player->dest);
 
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);
 
        // limits framerate
        SDL_Delay(1000 / framerate);
    }
 
    // destroy texture
    SDL_DestroyTexture(player->tex);
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}
