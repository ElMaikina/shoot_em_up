#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#include "bullet.h"
#include "config.h"

Bullet *createBullet(SDL_Renderer* rend, int x, int y) {
    // creates the bullet pointer and allocates memory
    Bullet *bullet;
    bullet = (Bullet*)malloc(sizeof(Bullet));

    // creates the surface to be drawn
    SDL_Surface* surface;
    surface = IMG_Load("bullet.png");

    // creates a texture to use hardware rendering
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

    // clears the surface
    SDL_FreeSurface(surface);

    // creates destiny geometry
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    
    // centers the geometry to the center of the screen
    dest.w /= 12;
    dest.h /= 12;
    dest.x = x + dest.w/2;
    dest.y = y + dest.h/2;

    // assigns bullet variables
    bullet->surface = surface;
    bullet->tex = tex;
    bullet->dest = dest;
    return bullet;
}