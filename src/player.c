#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#include "../include/player.h"
#include "../include/config.h"

Player *createPlayer(SDL_Renderer* rend, int winw, int winh) {
    // creates the player pointer and allocates memory
    Player *player;
    player = (Player*)malloc(sizeof(Player));

    // creates the surface to be drawn
    SDL_Surface* surface;
    surface = IMG_Load("./image/player.png");

    // creates a texture to use hardware rendering
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

    // clears the surface
    SDL_FreeSurface(surface);

    // creates destiny geometry
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    
    // centers the geometry to the center of the screen
    // dest.w /= 12;
    // dest.h /= 12;
    dest.x = (winw - dest.w) / 2;
    dest.y = (winh - dest.h) / 2;

    // assigns player variables
    player->surface = surface;
    player->tex = tex;
    player->dest = dest;
    player->shoot = PLAYER_SHOOT_DELAY;
    return player;
}
void movePlayer(Player *player) {
    // gets pressed keys
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    // uses the arrow keys for movement
    if (keystate[SDL_SCANCODE_UP]) 
        player->dest.y -= PLAYER_SPEED;

    if (keystate[SDL_SCANCODE_DOWN]) 
        player->dest.y += PLAYER_SPEED;

    if (keystate[SDL_SCANCODE_LEFT])
        player->dest.x -= PLAYER_SPEED;

    if (keystate[SDL_SCANCODE_RIGHT])
        player->dest.x += PLAYER_SPEED;
}
void limitPlayer(Player *player, int winw, int winh) {
    // limit player to the window limits
    if (player->dest.x < 0)
        player->dest.x = 0;

    if (player->dest.x + player->dest.w > winw)
        player->dest.x = winw - player->dest.w;
    
    if (player->dest.y < 0)
        player->dest.y = 0;
        
    if (player->dest.y + player->dest.h > winh)
        player->dest.y = winh - player->dest.h;
}
bool shootBullet(Player *player) {
    // gets pressed keys
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    // uses the arrow keys for movement
    if (keystate[SDL_SCANCODE_C]) {
        if (player->shoot >= PLAYER_SHOOT_DELAY) {
            player->shoot = 0;
            return true;
        }
    }
    player->shoot++;
    return false;
}