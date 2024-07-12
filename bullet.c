#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#include "player.h"
#include "bullet.h"

void createBullet(SDL_Renderer* rend, Bullet *bullet, int x, int y) {
    // creates the bullet pointer and allocates memory
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
    dest.w /= 6;
    dest.h /= 6;
    dest.x = x + dest.w/2;
    dest.y = y + dest.h/2;

    // assigns bullet variables
    bullet->surface = surface;
    bullet->tex = tex;
    bullet->dest = dest;
    bullet->next = NULL;
}
void addBullet(SDL_Renderer* rend, Bullet *bullet, Player *player) {
    //// creates a bullet if there arent any
    //if (bullet == NULL) {
    //    printf("First bullet\n");
    //    createBullet(rend, bullet, player->dest.x, player->dest.y);
    //    return;
    //}
    //// adds bullets to the queue
    //Bullet *currBullet = bullet;
    //while (currBullet->next != NULL) {
    //    currBullet = currBullet->next;
    //    printf("Next bullet!\n");
    //}
    //createBullet(rend, bullet->next, player->dest.x, player->dest.y);
    //printf("Last bullet!\n");
    //return;
    if (bullet == NULL) {
        createBullet(rend, bullet, player->dest.x, player->dest.y);
        printf("First bullet\n");
    }
    if (bullet != NULL) {
        printf("Next bullet\n");
    }
}