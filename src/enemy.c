#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#include "../include/enemy.h"
#include "../include/config.h"

Enemy *createEnemy(SDL_Renderer* rend, int x, int y) {
    // creates the enemy pointer and allocates memory
    Enemy *enemy;
    enemy = (Enemy*)malloc(sizeof(Enemy));

    // creates the surface to be drawn
    SDL_Surface* surface;
    surface = IMG_Load("./image/enemy.png");

    // creates a texture to use hardware rendering
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

    // clears the surface
    SDL_FreeSurface(surface);

    // creates destiny geometry
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    
    // centers the geometry to the center of the screen
    //dest.w /= 12;
    //dest.h /= 12;
    dest.x = x + dest.w/2;
    dest.y = y + dest.h/2;

    // assigns enemy variables
    enemy->surface = surface;
    enemy->tex = tex;
    enemy->dest = dest;
    return enemy;
}