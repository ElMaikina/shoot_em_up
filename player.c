#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#include "player.h"

Player *createPlayer(SDL_Renderer* rend, int winw, int winh) {
    // creates the player pointer and allocates memory
    Player *player;
    player = (Player*)malloc(sizeof(Player));

    // creates the surface to be drawn
    SDL_Surface* surface;
    surface = IMG_Load("melody.png");

    // creates a texture to use hardware rendering
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

    // clears the surface
    SDL_FreeSurface(surface);

    // creates destiny geometry
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    
    // centers the geometry to the center of the screen
    dest.w /= 6;
    dest.h /= 6;
    dest.x = (winw - dest.w) / 2;
    dest.y = (winh - dest.h) / 2;

    // assigns player variables
    player->surface = surface;
    player->tex = tex;
    player->dest = dest;
    player->speed = 6;
    return player;
}
void movePlayer(Player *player) {
    // gets pressed keys
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    // uses the arrow keys for movement
    if (keystate[SDL_SCANCODE_UP]) 
        player->dest.y -= player->speed;

    if (keystate[SDL_SCANCODE_DOWN]) 
        player->dest.y += player->speed;

    if (keystate[SDL_SCANCODE_LEFT])
        player->dest.x -= player->speed;

    if (keystate[SDL_SCANCODE_RIGHT])
        player->dest.x += player->speed;
}